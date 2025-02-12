// interpreter.h

#ifndef LEXER_H
#define LEXER_H

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
bool isIntegerFromChar(s);
bool isIntegerFromString(s);
void errorWithoutMsg(lexer* lex);
void errorWithMsg(lexer* lex, char* msg);

#endif // LEXER_H