// token.c
#include "token.h"
#ifdef TOKEN_H

#include <stdio.h>

const char* tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case INTEGER:
        return "INTEGER";
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
    case INC:
        return "INC";
    case DEC:
        return "DEC";
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

Token initBlankToken()
{
    Token token;
    token.type = END_OF_FILE;
    token.value = -1;
    return token;
}

Token initToken(TokenType type, int value)
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

void printToken(Token* token)
{
    printf("Token@%p: Type: %s, Value: %d\n", (void*)token, tokenTypeToString(token->type), token->value);
}
#endif // TOKEN_H