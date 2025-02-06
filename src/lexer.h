// interpreter.h

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <token.h>

typedef struct lexer
{
    char* text;
    unsigned int pos;
    token currentToken;
    char currentChar;
} lexer;

void amalgamate();
int expr();
void advance();
void skipWhitespace();
int integer();
void error(lexer* lex);
token getNextToken(lexer* lex);
token getNextTokenInternal(lexer* lex);

lexer initLexer();
lexer initLexer(char* text);

#endif // INTERPRETER_H