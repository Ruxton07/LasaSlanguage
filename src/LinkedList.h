// LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "token.h"

typedef struct Node {
    Token *token;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

LinkedList *createLinkedList();
void addToken(LinkedList *list, Token *token);
Token *removeToken(LinkedList *list);
void printLinkedList(LinkedList *list);
void freeLinkedList(LinkedList *list);

#endif // LINKEDLIST_H