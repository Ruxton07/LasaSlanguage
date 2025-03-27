// interpreter.h
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lexer.h"
#include "LinkedList.h"

#include <stddef.h>
#include <stdio.h>

typedef struct interpreter
{
    LinkedList *tokenList;
    Node *curNode;
} interpreter;

// Structure to store variables
typedef struct Variable {
    char *name;
    Token value;
} Variable;

// Function declarations
void setVariable(char *name, Token value);
Variable *findVariable(char *name);
void printVariables();
void interpret();

interpreter *initInterpreter(LinkedList *tokenList);
void advanceInterp(interpreter *interp);
Token *eval(LinkedList *list);
void parseExpr(interpreter *interp);
void parseBlock(interpreter *interp);
void error(interpreter *interp, const char *message);

#endif // INTERPRETER_H