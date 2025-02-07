// token.c

#include "token.h"
#include <stdio.h>

// Token types
// EOF (end-of-file) token is used to indicate that
// there is no more input left for lexical analysis

typedef enum TokenType
{
    INTEGER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END_OF_FILE // Forced to use this name because EOF is a macro in C which is set to (-1) through #define
} TokenType;

const char* tokenTypeToString(enum TokenType type)
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

typedef struct token
{
    enum TokenType type;
    int value;
} Token;

Token initToken()
{
    Token token;
    token.type = END_OF_FILE;
    token.value = -1;
    return token;
}

Token initToken(enum TokenType type, int value)
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