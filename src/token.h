// token.h

#ifndef TOKEN_H
#define TOKEN_H

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
    END_OF_FILE
} TokenType;

char* tokenTypeToString(TokenType* type);

typedef struct Token
{
    TokenType type;
    int value;

} token;

void printToken(token* tk);
void setTokenVal(token* tk, int val);

token initToken();
token initToken(TokenType* type, int value);

#endif // TOKEN_H