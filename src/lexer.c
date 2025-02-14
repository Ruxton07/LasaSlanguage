// lexer.c
#include "lexer.h"
#ifdef LEXER_H

#include "token.c"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

lexer *initBlankLexer()
{
    lexer *lex = malloc(sizeof(lexer));
    lex->text = "";
    lex->pos = 0;
    lex->currentChar = lex->text[lex->pos];
    lex->currentToken = initBlankToken();
    return lex;
}

lexer *initLexer(char *text)
{
    lexer *lex = malloc(sizeof(lexer));
    lex->text = text;
    lex->pos = 0;
    lex->currentChar = text[lex->pos];
    lex->currentToken = initBlankToken();
    return lex;
}

Token getNextToken(lexer *lex)
{
    while (lex->currentChar != '\0')
    {
        if (isspace(lex->currentChar))
        {
            skipWhitespace(lex);
            continue;
        }

        if (isdigit(lex->currentChar))
        {
            lex->currentToken = initToken(INTEGER, integer(lex));
            return lex->currentToken;
        }

        if (lex->currentChar == '+')
        {
            advance(lex);
            lex->currentToken = initToken(PLUS, 0);
            return lex->currentToken;
        }

        if (lex->currentChar == '-')
        {
            advance(lex);
            lex->currentToken = initToken(MINUS, 0);
            return lex->currentToken;
        }

        if (lex->currentChar == '*')
        {
            advance(lex);
            lex->currentToken = initToken(MUL, 0);
            return lex->currentToken;
        }

        if (lex->currentChar == '/')
        {
            advance(lex);
            lex->currentToken = initToken(DIV, 0);
            return lex->currentToken;
        }

        if (lex->currentChar == '(')
        {
            advance(lex);
            lex->currentToken = initToken(LPAREN, 0);
            return lex->currentToken;
        }

        if (lex->currentChar == ')')
        {
            advance(lex);
            lex->currentToken = initToken(RPAREN, 0);
            return lex->currentToken;
        }

        errorWOMsg(lex);
    }
    lex->currentToken = initToken(END_OF_FILE, 0);
    return lex->currentToken;
}

void eat(lexer *lex, TokenType type)
{
    if (lex->currentToken.type == type)
    {
        lex->currentToken = getNextToken(lex);
    }
    else
    {
        errorWOMsg(lex);
    }
}
void *expr(lexer *lex)
{
    // expr --> INTEGER <INTEGER-CO> INTEGER
    lex->currentToken = getNextToken(lex);
    Token left = lex->currentToken;
    eat(lex, INTEGER);
    // check if the current token is an <INTEGER-CO> token
    Token op = lex->currentToken;
    switch (op.type)
    {
    case PLUS:
        eat(lex, PLUS);
        break;
    case MINUS:
        eat(lex, MINUS);
        break;
    case MUL:
        eat(lex, MUL);
        break;
    case DIV:
        eat(lex, DIV);
        break;
    case EXP:
        eat(lex, EXP);
        break;
    case MOD:
        eat(lex, MOD);
        break;
    case POSTINC:
        eat(lex, POSTINC);
        break;
    case POSTDEC:
        eat(lex, POSTDEC);
        break;
    default:
        errorWMsg(lex, ("Unknown operator: %d", tokenTypeToString(op.type)));
    }
    Token right = lex->currentToken;
    eat(lex, INTEGER);

    // at this point INTEGER <INTEGER-CO> INTEGER sequence of tokens has been
    // successfully found and the method can just return the result of
    // performing such operation on two integers
    TokenType resultType = INTEGER;
    Token *resultToken = malloc(sizeof(Token));
    *resultToken = initToken(resultType, performOp(lex, left, op, right));
    return resultToken;
}

void advance(lexer *lex)
{
    lex->pos++;
    if (lex->pos > strlen(lex->text) - 1)
    {
        lex->currentChar = '\0'; // indicates end of input
    }
    else
    {
        lex->currentChar = lex->text[lex->pos];
    }
}

void skipWhitespace(lexer *lex)
{
    while (lex->currentChar != '\0' && isspace(lex->currentChar))
    {
        advance(lex);
    }
}

int integer(lexer *lex)
{
    char result[100];
    int i = 0;
    while (lex->currentChar != '\0' && isdigit(lex->currentChar))
    {
        result[i] = lex->currentChar;
        advance(lex);
        i++;
    }
    result[i] = '\0';
    return atoi(result);
}

Token performOp(lexer *lex, Token left, Token op, Token right)
{
    Token result;
    switch (op.type)
    {
    case PLUS:
        if (left.type == DOUBLE || right.type == DOUBLE)
        {
            result.type = DOUBLE;
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : left.value.value.intValue) +
                                       (right.type == DOUBLE ? right.value.doubleValue : right.value.value.intValue);
        }
        else
        {
            result.type = INTEGER;
            result.value.intValue = left.value.intValue + right.value.intValue;
        }
        break;
    case MINUS:
        if (left.type == DOUBLE || right.type == DOUBLE)
        {
            result.type = DOUBLE;
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : left.value.intValue) -
                                       (right.type == DOUBLE ? right.value.doubleValue : right.value.intValue);
        }
        else
        {
            result.type = INTEGER;
            result.value.intValue = left.value.intValue - right.value.intValue;
        }
        break;
    case MUL:
        if (left.type == DOUBLE || right.type == DOUBLE)
        {
            result.type = DOUBLE;
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : left.value.intValue) *
                                       (right.type == DOUBLE ? right.value.doubleValue : right.value.intValue);
        }
        else
        {
            result.type = INTEGER;
            result.value.intValue = left.value.intValue * right.value.intValue;
        }
        break;
    case DIV:
        result.type = DOUBLE;
        result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : left.value.intValue) /
                                   (right.type == DOUBLE ? right.value.doubleValue : right.value.intValue);
        break;
    case EXP:
        result.type = DOUBLE;
        result.value.doubleValue = pow((left.type == DOUBLE ? left.value.doubleValue : left.value.intValue),
                                       (right.type == DOUBLE ? right.value.doubleValue : right.value.intValue));
        break;
    case MOD:
        result.type = INTEGER;
        result.value.intValue = left.value.intValue % right.value.intValue;
        break;
    case POSTINC:
        result.type = left.type;
        if (left.type == DOUBLE)
        {
            result.value.doubleValue = left.value.doubleValue + 1;
        }
        else
        {
            result.value.intValue = left.value.intValue + 1;
        }
        break;
    case POSTDEC:
        result.type = left.type;
        if (left.type == DOUBLE)
        {
            result.value.doubleValue = left.value.doubleValue - 1;
        }
        else
        {
            result.value.intValue = left.value.intValue - 1;
        }
        break;
    default:
        errorWMsg(lex, ("Unknown operator: %d", tokenTypeToString(op.type)));
    }
    return result;
}

void errorWOMsg(lexer *lex)
{
    printf("Error parsing input:\nUnknown error");
    exit(1);
}

void errorWMsg(lexer *lex, char *msg)
{
    printf("Error parsing input: %s\n", msg);
    exit(1);
}
#endif // LEXER_H