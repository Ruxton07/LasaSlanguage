// stack.h
#ifndef STACK_H
#define STACK_H

#include "token.h"

typedef struct stack {
    Token *data;
    int top;
    int capacity;
} Stack;

Stack *createStack(int capacity);
int isFull(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, Token item);
Token pop(Stack *stack);
Token peek(Stack *stack);
int precedence(TokenType op);
int isOperator(TokenType type);

void stackToString(Stack *stack);

#endif // STACK_H