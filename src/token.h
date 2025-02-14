// token.h

#ifndef TOKEN_H
#define TOKEN_H

typedef enum tokentype
{
    INTEGER,
    DOUBLE,
    PLUS,
    MINUS,
    MUL,
    DIV,
    EXP,
    MOD,
    POSTINC,
    POSTDEC,
    PREINC,
    PREDEC,
    LPAREN,
    RPAREN,
    END_OF_FILE
} TokenType;

const char* tokenTypeToString(TokenType type);

typedef union tokenvalue {
    int intValue;
    double doubleValue;
    char charValue;
} TokenValue;

typedef struct token
{
    TokenType type;
    TokenValue value;

} Token;

Token initBlankToken();
Token initToken(TokenType type, TokenValue value);

void printToken(Token* token);

#endif // TOKEN_H