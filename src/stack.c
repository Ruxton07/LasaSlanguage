// stack.c
#include "stack.h"

#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


Stack *createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (Token *)malloc(stack->capacity * sizeof(Token));
    return stack;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, Token item) {
    if (isFull(stack))
        return;
    stack->data[++stack->top] = item;
    printf("NOW..TOP IS %d\n", stack->top);
}

Token pop(Stack *stack) {
    if (isEmpty(stack))
        exit(EXIT_FAILURE);
    return stack->data[stack->top--];
}

Token peek(Stack *stack) {
    if (isEmpty(stack))
        exit(EXIT_FAILURE);
    return stack->data[stack->top];
}

int precedence(TokenType op) {
    switch (op) {
        case PLUS:
        case MINUS:
            return 1;
        case MUL:
        case DIV:
            return 2;
        case EXP:
            return 3;
        default:
            return 0;
    }
}

int isOperator(TokenType type) {
    return type == PLUS || type == MINUS || type == MUL || type == DIV || type == EXP || type == MOD || type == POSTINC || type == POSTDEC;
}