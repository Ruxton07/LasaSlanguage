// token.c
#include "token.h"

#include <stdio.h>

char *tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case INTEGER:
        return "INTEGER";
    case FLOAT:
        return "FLOAT";
    case DOUBLE:
        return "DOUBLE";
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case EXP:
        return "EXP";
    case MOD:
        return "MOD";
    case POSTINC:
        return "INC";
    case POSTDEC:
        return "DEC";
    case PREINC:
        return "PREINC";
    case PREDEC:
        return "PREDEC";
    case LPAREN:
        return "LPAREN";
    case RPAREN:
        return "RPAREN";
    case END_OF_FILE:
        return "EOF";
    default:
        return "UNKNOWN";
    }
}

TokenType charToTokenType(char c)
{
    switch (c)
    {
    case '+':
        return PLUS;
    case '-':
        return MINUS;
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '^':
        return EXP;
    case '%':
        return MOD;
    case '(':
        return LPAREN;
    case ')':
        return RPAREN;
    default:
        return END_OF_FILE;
    }
}

Token initBlankToken()
{
    Token token;
    token.type = END_OF_FILE;
    token.value = (TokenValue){-1};
    return token;
}

Token initToken(TokenType type, TokenValue value)
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

void printToken(Token *token)
{
    printf("Token@%p: Type: %s,\nValues:\n%d\n%d\n%d\n%c", (void *)token, tokenTypeToString(token->type),
           token->value.intValue, token->value.floatValue, token->value.doubleValue, token->value.charValue);
}