// lexer.c
#include "lexer.h"
#ifdef LEXER_H

#include "token.c"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    lex->currentToken = initToken(INTEGER, (TokenValue){0});
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
            lex->currentToken = interpretNumber(lex);
            return lex->currentToken;
        }

        if (lex->currentChar == '+')
        {
            advance(lex);
            if (lex->currentChar == '+')
            {
                advance(lex);
                lex->currentToken = initToken(POSTINC, (TokenValue){0});
            }
            else
            {
                lex->currentToken = initToken(PLUS, (TokenValue){0});
            }
            return lex->currentToken;
        }

        if (lex->currentChar == '-')
        {
            advance(lex);
            if (lex->currentChar == '-')
            {
                advance(lex);
                lex->currentToken = initToken(POSTDEC, (TokenValue){0});
            }
            else
            {
                lex->currentToken = initToken(MINUS, (TokenValue){0});
            }
            return lex->currentToken;
        }

        // MUL, DIV, EXP, and MOD are set to 1 in the rare case that there is an issue while lexing:
        // in the case that they are included in some arithmetic computation this should
        // minimize the chance of possible discrepancies in the resulting value
        if (lex->currentChar == '*')
        {
            advance(lex);
            lex->currentToken = initToken(MUL, (TokenValue){1});
            return lex->currentToken;
        }

        if (lex->currentChar == '/')
        {
            advance(lex);
            lex->currentToken = initToken(DIV, (TokenValue){1});
            return lex->currentToken;
        }

        if (lex->currentChar == '^')
        {
            advance(lex);
            lex->currentToken = initToken(EXP, (TokenValue){1});
            return lex->currentToken;
        }

        if (lex->currentChar == '%')
        {
            advance(lex);
            lex->currentToken = initToken(MOD, (TokenValue){1});
            return lex->currentToken;
        }

        if (lex->currentChar == '(')
        {
            advance(lex);
            lex->currentToken = initToken(LPAREN, (TokenValue){0});
            return lex->currentToken;
        }

        if (lex->currentChar == ')')
        {
            advance(lex);
            lex->currentToken = initToken(RPAREN, (TokenValue){0});
            return lex->currentToken;
        }
        printf("Unrecognized Token: %s", lex->currentChar);
        errorWMsg(lex);
    }
    lex->currentToken = initBlankToken();
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
        printf("Expected token type: %s, but got: %s", tokenTypeToString(type), tokenTypeToString(lex->currentToken.type));
        errorWMsg(lex);
    }
}

void *expr(lexer *lex)
{
    int terminate = 0;
    lex->currentToken = getNextToken(lex);
    Token left = lex->currentToken;
    eat(lex, left.type);
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
        terminate = 1;
        break;
    case POSTDEC:
        eat(lex, POSTDEC);
        terminate = 1;
        break;
    default:
        printf("Unknown operator: %s", tokenTypeToString(op.type));
        errorWMsg(lex);
    }
    Token right = initToken(INTEGER, (TokenValue){0});
    if (!terminate)
    {
        right = lex->currentToken;
        eat(lex, right.type);
    }
    Token *resultToken = malloc(sizeof(Token));
    *resultToken = performOp(lex, left, op, right);
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

Token interpretNumber(lexer *lex)
{
    char result[100];
    int i = 0;
    int isFloat = 0;
    int isDouble = 0;

    while (lex->currentChar != '\0' && (isdigit(lex->currentChar) || lex->currentChar == '.' || lex->currentChar == 'f'))
    {
        if (lex->currentChar == '.')
        {
            isDouble = 1;
        }
        else if (lex->currentChar == 'f')
        {
            isFloat = 1;
            advance(lex); // Move past the 'f' character
            break;
        }
        result[i] = lex->currentChar;
        advance(lex);
        i++;
    }
    result[i] = '\0';

    Token token;
    if (isFloat)
    {
        token.type = FLOAT;
        token.value.floatValue = atof(result);
    }
    else if (isDouble)
    {
        token.type = DOUBLE;
        token.value.doubleValue = atof(result);
    }
    else
    {
        token.type = INTEGER;
        token.value.intValue = atoi(result);
    }

    return token;
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
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : left.value.intValue) +
                                       (right.type == DOUBLE ? right.value.doubleValue : right.value.intValue);
        }
        else if (left.type == FLOAT || right.type == FLOAT)
        {
            result.type = FLOAT;
            result.value.floatValue = (left.type == FLOAT ? left.value.floatValue : left.value.intValue) +
                                      (right.type == FLOAT ? right.value.floatValue : right.value.intValue);
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
        else if (left.type == FLOAT || right.type == FLOAT)
        {
            result.type = FLOAT;
            result.value.floatValue = (left.type == FLOAT ? left.value.floatValue : left.value.intValue) -
                                      (right.type == FLOAT ? right.value.floatValue : right.value.intValue);
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
        else if (left.type == FLOAT || right.type == FLOAT)
        {
            result.type = FLOAT;
            result.value.floatValue = (left.type == FLOAT ? left.value.floatValue : left.value.intValue) *
                                      (right.type == FLOAT ? right.value.floatValue : right.value.intValue);
        }
        else
        {
            result.type = INTEGER;
            result.value.intValue = left.value.intValue * right.value.intValue;
        }
        break;
    case DIV:
        if (left.type == DOUBLE || right.type == DOUBLE)
        {
            result.type = DOUBLE;
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : left.value.intValue) /
                                       (right.type == DOUBLE ? right.value.doubleValue : right.value.intValue);
        }
        else if (left.type == FLOAT || right.type == FLOAT)
        {
            result.type = FLOAT;
            result.value.floatValue = (left.type == FLOAT ? left.value.floatValue : left.value.intValue) /
                                      (right.type == FLOAT ? right.value.floatValue : right.value.intValue);
        }
        else
        {
            result.type = INTEGER;
            result.value.intValue = left.value.intValue / right.value.intValue;
        }
        break;
    case EXP:
        result.type = left.type == DOUBLE || right.type == DOUBLE ? DOUBLE : (left.type == FLOAT || right.type == FLOAT ? FLOAT : INTEGER);
        if (result.type == DOUBLE)
        {
            result.value.doubleValue = pow((left.type == DOUBLE ? left.value.doubleValue : (left.type == FLOAT ? left.value.floatValue : left.value.intValue)),
                                           (right.type == DOUBLE ? right.value.doubleValue : (right.type == FLOAT ? right.value.floatValue : right.value.intValue)));
        }
        else if (result.type == FLOAT)
        {
            result.value.floatValue = pow((left.type == FLOAT ? left.value.floatValue : left.value.intValue),
                                          (right.type == FLOAT ? right.value.floatValue : right.value.intValue));
        }
        else
        {
            result.value.intValue = pow(left.value.intValue, right.value.intValue);
        }
        break;
    case MOD:
        result.type = left.type == DOUBLE || right.type == DOUBLE ? DOUBLE : (left.type == FLOAT || right.type == FLOAT ? FLOAT : INTEGER);
        if (result.type == DOUBLE)
        {
            result.value.doubleValue = fmod((left.type == DOUBLE ? left.value.doubleValue : (left.type == FLOAT ? left.value.floatValue : left.value.intValue)),
                                            (right.type == DOUBLE ? right.value.doubleValue : (right.type == FLOAT ? right.value.floatValue : right.value.intValue)));
        }
        else if (result.type == FLOAT)
        {
            result.value.floatValue = fmod((left.type == FLOAT ? left.value.floatValue : left.value.intValue),
                                           (right.type == FLOAT ? right.value.floatValue : right.value.intValue));
        }
        else
        {
            result.value.intValue = left.value.intValue % right.value.intValue;
        }
        break;
    case POSTINC:
        result.type = left.type;
        if (left.type == DOUBLE)
        {
            result.value.doubleValue = left.value.doubleValue + 1;
        }
        else if (left.type == FLOAT)
        {
            result.value.floatValue = left.value.floatValue + 1;
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
        else if (left.type == FLOAT)
        {
            result.value.floatValue = left.value.floatValue - 1;
        }
        else
        {
            result.value.intValue = left.value.intValue - 1;
        }
        break;
    default:
        printf("Unknown operator: %d", tokenTypeToString(op.type));
        errorWMsg(lex);
    }
    return result;
}

void errorWOMsg(lexer *lex)
{
    printf("\nERROR PARSING INPUT: UNKNOWN ERROR\n");
    exit(1);
}

void errorWMsg(lexer *lex)
{
    printf("\nERROR PARSING INPUT\n");
    exit(1);
}
#endif // LEXER_H