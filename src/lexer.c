// lexer.c
#include "lexer.h"
#include "stack.h"
#include "LinkedList.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
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
        if (lex->currentChar == '\\')
        {
            advance(lex);
            continue;
        }
        if (isdigit(lex->currentChar))
        {
            lex->currentToken = *interpretNumber(lex);
            return lex->currentToken;
        }

        if (isalpha(lex->currentChar) || lex->currentChar == '_')
        {
            char identifier[100];
            int i = 0;

            while (isalnum(lex->currentChar) || lex->currentChar == '_')
            {
                identifier[i++] = lex->currentChar;
                advance(lex);
            }
            identifier[i] = '\0';

            if (strcmp(identifier, "int") == 0 || strcmp(identifier, "float") == 0 || strcmp(identifier, "double") == 0)
            {
                lex->currentToken = initToken(TYPEASSIGN, (TokenValue){.charValue = '\0'});
            }
            else
            {
                lex->currentToken = initToken(IDENTIFIER, (TokenValue){.charValue = strdup(identifier)});
            }
            return lex->currentToken;
        }

        if (lex->currentChar == '=')
        {
            advance(lex);
            if (lex->currentChar == '=') {
                advance(lex);
                lex->currentToken = initToken(EQ, (TokenValue){0});
            } else {
                lex->currentToken = initToken(ASSIGN, (TokenValue){0});
            }
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

        if (lex->currentChar == ';')
        {
            advance(lex);
            lex->currentToken = initToken(SEMICOLON, (TokenValue){0});
            return lex->currentToken;
        }

        if (lex->currentChar == '>')
        {
            advance(lex);
            if (lex->currentChar == '=')
            {
                advance(lex);
                lex->currentToken = initToken(GTE, (TokenValue){0});
            }
            else
            {
                lex->currentToken = initToken(GT, (TokenValue){0});
            }
            return lex->currentToken;
        }

        if (lex->currentChar == '<')
        {
            advance(lex);
            if (lex->currentChar == '=')
            {
                advance(lex);
                lex->currentToken = initToken(LTE, (TokenValue){0});
            }
            else
            {
                lex->currentToken = initToken(LT, (TokenValue){0});
            }
            return lex->currentToken;
        }

        if (lex->currentChar == '{') {
            advance(lex);
            lex->currentToken = initToken(BLOCKSTART, (TokenValue){0});
            return lex->currentToken;
        }

        if (lex->currentChar == '}') {
            advance(lex);
            lex->currentToken = initToken(BLOCKEND, (TokenValue){0});
            return lex->currentToken;
        }

        printf("Unrecognized Token: -->%c<--", lex->currentChar);
        errorLex();
    }
    lex->currentToken = initBlankToken();
    return lex->currentToken;
}

int unaryOp(Token op) {
    int unary = 0;
    unary = (op.type == POSTINC || op.type == POSTDEC);
    return unary;
}

void *expr(lexer *lex) {
    int len = strlen(lex->text);
    if (len == 0) {
        return NULL;
    }

    Stack *values = createStack(len); // Stack for values
    Stack *ops = createStack(len);    // Stack for operators

    while (lex->currentChar != '\0') {
        if (isspace(lex->currentChar)) {
            skipWhitespace(lex);
            continue;
        }
        if (lex->currentChar == '\\') {
            advance(lex);
            continue;
        }
        if (isdigit(lex->currentChar) || lex->currentChar == '.') {
            Token *value = malloc(sizeof(Token));
            value = interpretNumber(lex);
            push(values, *value);
        } else if (lex->currentChar == '(') {
            Token lparen = initToken(LPAREN, (TokenValue){0});
            push(ops, lparen);
            advance(lex);
        } else if (lex->currentChar == ')') {
            while (!isEmpty(ops) && peek(ops).type != LPAREN) {
                Token op = pop(ops);
                Token right = pop(values);
                Token left = pop(values);
                Token result = performOp(left, op, right);
                push(values, result);
            }
            pop(ops); // Remove the left parenthesis
            advance(lex);
        } else if (isOperator(charToTokenType(lex->currentChar))) {
            Token op = getNextToken(lex);
            if (unaryOp(op)) {
                Token left = pop(values);
                Token right = (Token){.type = INTEGER, .value = (TokenValue){1}};
                Token result = performOp(left, op, right);
                push(values, result);
                continue;
            }
            printf("yippee im here\n");
            while (!isEmpty(ops) && precedence(peek(ops).type) >= precedence(op.type)) {
                Token topOp = pop(ops);
                Token right = pop(values);
                Token left = pop(values);
                Token result = performOp(left, topOp, right);
                push(values, result);
            }
            push(ops, op);
        } else {
            printf("Unrecognized Char: -->%c<--", lex->currentChar);
            errorLex();
        }
    }

    while (!isEmpty(ops)) {
        Token op = pop(ops);
        Token right = pop(values);
        Token left = pop(values);
        Token result = performOp(left, op, right);
        push(values, result);
    }

    Token *resultToken = malloc(sizeof(Token));
    *resultToken = pop(values);

    free(values->data);
    free(values);
    free(ops->data);
    free(ops);

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

Token *interpretNumber(lexer *lex)
{
    char result[100];
    for (int k = 0; k < 100; k++) {
        result[k] = '\0';
    }
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
            isDouble = 0;
            advance(lex); // Move past the 'f' character
            i++;
            break;
        }
        printf("Adding %c to the result arr\n", lex->currentChar);
        result[i] = lex->currentChar;
        advance(lex);
        i++;
    }
    // remove all values in result arr from 0 to i if they aren't isdigit
    do
    {
        result[i] = '\0';
        i--;
    } while (i > 0 && !isdigit(result[i]));

    char cleanResult[100];
    for (int k = 0; k < 100; k++) {
        cleanResult[k] = '\0';
    }
    int j = 0;
    while (j <= i) {
        cleanResult[j] = result[j];
        j++;
    }
    Token *token = malloc(sizeof(Token));
    *token = initBlankToken();
    printf("Final result array: %s\n", cleanResult);

    if (isFloat)
    {
        token->type = FLOAT;
        token->value.floatValue = atof(cleanResult);
    }
    else if (isDouble)
    {
        token->type = DOUBLE;
        token->value.doubleValue = atof(cleanResult);
    }
    else
    {
        token->type = INTEGER;
        token->value.intValue = atoi(cleanResult);
    }

    printToken(token);
    return token;
}

Token performOp(Token left, Token op, Token right)
{
    printf("Performing operation: %s %s %s\n", numericVal(&left), tokenTypeToString(op.type), numericVal(&right));
    printf("of format %s %s %s\n", tokenTypeToString(left.type), tokenTypeToString(op.type), tokenTypeToString(right.type));
    printf("At this moment, tokens are the following:\n");
    printToken(&left);
    printToken(&op);
    if (unaryOp(op)) {
        printToken(&right);
    }
    Token result;
    switch (op.type)
    {
    case PLUS:
        if (left.type == DOUBLE || right.type == DOUBLE)
        {
            result.type = DOUBLE;
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : (left.type == FLOAT ? left.value.floatValue : left.value.intValue)) +
                                       (right.type == DOUBLE ? right.value.doubleValue : (right.type == FLOAT ? right.value.floatValue : right.value.intValue));
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
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : (left.type == FLOAT ? left.value.floatValue : left.value.intValue)) -
                                       (right.type == DOUBLE ? right.value.doubleValue : (right.type == FLOAT ? right.value.floatValue : right.value.intValue));
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
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : (left.type == FLOAT ? left.value.floatValue : left.value.intValue)) *
                                       (right.type == DOUBLE ? right.value.doubleValue : (right.type == FLOAT ? right.value.floatValue : right.value.intValue));
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
        if (right.type == INTEGER ? right.value.intValue == 0 : (right.type == FLOAT ? right.value.floatValue == 0 : right.value.doubleValue == 0))
        {
            printf("Division by zero error\n");
            errorLex();
        }
        if (left.type == DOUBLE || right.type == DOUBLE)
        {
            result.type = DOUBLE;
            result.value.doubleValue = (left.type == DOUBLE ? left.value.doubleValue : (left.type == FLOAT ? left.value.floatValue : left.value.intValue)) /
                                       (right.type == DOUBLE ? right.value.doubleValue : (right.type == FLOAT ? right.value.floatValue : right.value.intValue));
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
        if (right.type == INTEGER ? right.value.intValue == 0 : (right.type == FLOAT ? right.value.floatValue == 0 : right.value.doubleValue == 0))
        {
            printf("Modulus by zero error\n");
            errorLex();
        }
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
        printf("left: %d\n", left.value.intValue);
        printf("left type: %d\n", left.type);
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
        printf("Unknown operator: %s", tokenTypeToString(op.type));
    }
    return result;
}

void errorLex()
{
    printf("\nERROR PARSING INPUT\n");
    exit(1);
}

LinkedList *tokenizeSourceCode(char *sourceCode) {
    lexer *lex = initLexer(sourceCode);
    LinkedList *tokenList = createLinkedList();

    while (lex->currentChar != '\0') {
        Token token = getNextToken(lex);
        if (token.type != BLANK) { // Skip blank tokens
            Token *tokenCopy = malloc(sizeof(Token));
            *tokenCopy = token;
            addToken(tokenList, tokenCopy);
        }
    }

    free(lex); // Free the lexer
    return tokenList;
}
