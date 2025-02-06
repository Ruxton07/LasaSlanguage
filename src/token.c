// token.c

#include "token.h"

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
};

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

// Token struct

struct Token
{
    enum TokenType type;
    int value;
};

void printToken(struct Token token)
{
    printf("Token@%p: Type: %d, Value: %d\n", (void*)&token, token.type, token.value);
}