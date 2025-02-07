// interpreter.h

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <token.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct lexer
{
    char* text;
    size_t pos;
    Token currentToken;
    char currentChar;
} lexer;

lexer* initLexer();
lexer* initLexer(char* text);

Token getNextToken(lexer* lex);
void eat(lexer* lex, enum TokenType type);
void* expr(lexer* lex);
void advance(lexer* lex);
void skipWhitespace(lexer* lex);
bool isInteger(char c);
bool isInteger(char* s);
void error(lexer* lex);
void error(lexer* lex, char* msg);

#endif // INTERPRETER_H