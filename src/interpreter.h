// interpreter.h

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <token.h>

class Interpreter
{
public:
    Interpreter();
    Token getNextToken();
    int expr();

private:
    std::string text;
    size_t pos;
    Token currentToken;
    char currentChar;

    void advance();
    void skipWhitespace();
    int integer();
    Token getNextTokenInternal();
    void error();
};

#endif // INTERPRETER_H