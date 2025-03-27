// token.h
#ifndef TOKEN_H
#define TOKEN_H

typedef enum tokentype
{
    // DATA TYPES
    INTEGER,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
    // EXPRESSIONS
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
    END_OF_FILE,
    // INSTRUCTIONS
    IF,
    ELSE,
    ELIF,
    WHILE,
    FOR,
    RETURN,
    BREAK,
    CONTINUE,
    // INSTANTIATION
    TYPEASSIGN,
    IDENTIFIER,
    ASSIGN,
    // COMPARISON
    EQ,
    NEQ,
    GT,
    LT,
    GTE,
    LTE,
    // LOGICAL
    AND,
    OR,
    NOT,
    XOR,
    // BITWISE
    BAND,
    BOR,
    BNOT,
    BXOR,
    // POSITIONING CONTROL
    COMMA,
    SEMICOLON,
    COLON,
    BLOCKSTART,
    BLOCKEND,
    // MISC
    BLANK
} TokenType;

char *tokenTypeToString(TokenType type);
TokenType dataTypetoTokenType(char* str);
TokenType charToTokenType(char c);

typedef union tokenvalue
{
    int intValue;
    double doubleValue;
    float floatValue;
    char* charValue;
} TokenValue;

typedef struct token
{
    TokenType type;
    TokenValue value;

} Token;

Token initBlankToken();
Token initToken(TokenType type, TokenValue value);

void printToken(Token *token);
char* numericVal(Token *token);

#endif // TOKEN_H