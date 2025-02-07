// token.h

#ifndef TOKEN_H
#define TOKEN_H

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

typedef struct token
{
    TokenType type;
    int value;

} Token;

Token initToken();
Token initToken(TokenType* type, int value);

void printToken(Token* token);

#endif // TOKEN_H