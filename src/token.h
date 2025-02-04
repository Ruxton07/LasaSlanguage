// token.h

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

enum class TokenType
{
    INTEGER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END_OF_FILE
};

std::string tokenTypeToString(TokenType type);

class Token
{
public:
    TokenType type;
    int value;

    Token(TokenType type, int value);
    friend std::ostream &operator<<(std::ostream &out, const Token &token);
};

#endif // TOKEN_H