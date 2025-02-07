// lexer.c

#include "lexer.h"
#include "token.c"
#include <stdbool.h>

typedef struct lexer
{
    char* text;
    int pos;
    Token currentToken;
    char currentChar;
} lexer;

lexer* initLexer()
{
    lexer* lex = malloc(sizeof(struct lexer));
    lex->text = "";
    lex->pos = 0;
    lex->currentChar = lex->text[lex->pos];
}

lexer* initLexer(char* text)
{
    lexer* lex = malloc(sizeof(struct lexer));
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

        error(lex);
    }
}

void eat(lexer* lex, enum TokenType type) {
    if (lex->currentToken.type == type) {
        lex->currentToken = getNextToken(lex);
    } else {
        error(lex);
    }
}
void* expr(lexer* lex) {
    // expr --> INTEGER <INTEGER-CO> INTEGER
    lex->currentToken = getNextToken(lex);

    Token* left = &(lex->currentToken);
    eat(lex, INTEGER);

    // check if the current token is an <INTEGER-CO> token
    Token* op = &(lex->currentToken);
    if (op->type == PLUS) {
        eat(lex, PLUS);
    } else if (op->type == MINUS) {
        eat(lex, MINUS);
    } else if (op->type == MUL) {
        eat(lex, MUL);
    } else if (op->type == DIV) {
        eat(lex, DIV);
    } else {
        error(lex);
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

bool isInteger(char c) {
    return c >= '0' && c <= '9';
}

bool isInteger(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        if (!isInteger(s[i])) {
            return false;
        }
    }
    return true;
}

void error(lexer* lex) {
    printf("Error parsing input:\nUnknown error");
    exit(1);
}

void error(lexer* lex, char* msg) {
    printf("Error parsing input: %s\n", msg);
    exit(1);
}