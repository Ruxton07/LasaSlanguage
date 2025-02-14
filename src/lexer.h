// interpreter.h

#ifndef LEXER_H
#define LEXER_H

#include <token.h>
#include <stddef.h>

typedef struct lexer
{
    char* text;
    size_t pos;
    Token currentToken;
    char currentChar;
} lexer;

lexer* initBlankLexer();
lexer* initLexer(char* text);

Token getNextToken(lexer* lex);
void eat(lexer* lex, TokenType type);
void* expr(lexer* lex);
void advance(lexer* lex);
void skipWhitespace(lexer* lex);
int integer(lexer* lex);
Token performOp(lexer* lex, Token left, Token op, Token right);
void errorWOMsg(lexer* lex);
void errorWMsg(lexer* lex, char* msg);


#endif // LEXER_H