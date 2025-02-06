// lexer.c

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "lexer.h"
#include "token.h"
#include "token.c"


struct lexer
{
    char* text;
    int pos;
    struct Token currentToken;
    char currentChar;
};

lexer initLexer(char* text)
{
    lexer* lex = malloc(sizeof(struct lexer));
    lex->text = text;
    lex->pos = 0;
    lexer->currentChar = text[lexer->pos];
}