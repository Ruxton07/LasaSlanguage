// lexer.c
#include "lexer.h"
#ifdef LEXER_H

#include "token.c"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

lexer* initBlankLexer()
{
    lexer* lex = malloc(sizeof(lexer));
    lex->text = "";
    lex->pos = 0;
    lex->currentChar = lex->text[lex->pos];
}

lexer* initLexer(char* text)
{
    lexer* lex = malloc(sizeof(lexer));
    lex->text = text;
    lex->pos = 0;
    lex->currentChar = text[lex->pos];
}

Token getNextToken(lexer* lex) {
    while (lex->currentChar != '\0') {
        if (lex->currentChar == ' ') {
            skipWhitespace(lex);
            continue;
        }

        if (isdigit(lex->currentChar)) {
            return initToken(INTEGER, integer(lex));
        }

        if (lex->currentChar == '+') {
            advance(lex);
            return initToken(PLUS, 0);
        }

        if (lex->currentChar == '-') {
            advance(lex);
            return initToken(MINUS, 0);
        }

        if (lex->currentChar == '*') {
            advance(lex);
            return initToken(MUL, 0);
        }

        if (lex->currentChar == '/') {
            advance(lex);
            return initToken(DIV, 0);
        }

        if (lex->currentChar == '(') {
            advance(lex);
            return initToken(LPAREN, 0);
        }

        if (lex->currentChar == ')') {
            advance(lex);
            return initToken(RPAREN, 0);
        }

        errorWOMsg(lex);
    }
}

void eat(lexer* lex, TokenType type) {
    if (lex->currentToken.type == type) {
        lex->currentToken = getNextToken(lex);
    } else {
        errorWOMsg(lex);
    }
}
void* expr(lexer* lex) {
    printf("1");
    // expr --> INTEGER <INTEGER-CO> INTEGER
    lex->currentToken = getNextToken(lex);
    printf("2");
    Token* left = &(lex->currentToken);
    printf("3");
    eat(lex, INTEGER);
    printf("4");
    // check if the current token is an <INTEGER-CO> token
    Token* op = &(lex->currentToken);
    printf("5");
    if (op->type == PLUS) {
        eat(lex, PLUS);
    } else if (op->type == MINUS) {
        eat(lex, MINUS);
    } else if (op->type == MUL) {
        eat(lex, MUL);
    } else if (op->type == DIV) {
        eat(lex, DIV);
    } else {
        errorWOMsg(lex);
    }

    Token* right = &(lex->currentToken);
    eat(lex, INTEGER);

    // at this point INTEGER <INTEGER-CO> INTEGER sequence of tokens has been
    // successfully found and the method can just return the result of
    // performing such operation on two integers
    int result;
    if (op->type == PLUS) {
        result = left->value + right->value;
    } else if (op->type == MINUS) {
        result = left->value - right->value;
    } else if (op->type == MUL) {
        result = left->value * right->value;
    } else if (op->type == DIV) {
        result = (int) (left->value / right->value);
    }
    return result;
}

void advance(lexer* lex) {
    lex->pos++;
    if (lex->pos > strlen(lex->text) - 1) {
        lex->currentChar = '\0';  // indicates end of input
    } else {
        lex->currentChar = lex->text[lex->pos];
    }
}

void skipWhitespace(lexer* lex) {
    while (lex->currentChar != '\0' && isspace(lex->currentChar)) {
        advance(lex);
    }
}

int integer(lexer* lex) {
    char result[100];
    int i = 0;
    while (lex->currentChar != '\0' && isdigit(lex->currentChar)) {
        result[i] = lex->currentChar;
        advance(lex);
        i++;
    }
    result[i] = '\0';
    return atoi(result);
}

void errorWOMsg(lexer* lex) {
    printf("Error parsing input:\nUnknown error");
    exit(1);
}

void errorWMsg(lexer* lex, char* msg) {
    printf("Error parsing input: %s\n", msg);
    exit(1);
}
#endif // LEXER_H