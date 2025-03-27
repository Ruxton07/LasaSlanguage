// LinkedList.c
#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize a new LinkedList
LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Add a Token to the LinkedList
void addToken(LinkedList *list, Token *token) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->token = token;
    newNode->next = NULL;

    if (list->tail) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
    list->size++;
}

// Remove the first Token from the LinkedList
Token *removeToken(LinkedList *list) {
    if (!list->head) return NULL;

    Node *temp = list->head;
    Token *token = temp->token;
    list->head = list->head->next;

    if (!list->head) {
        list->tail = NULL;
    }

    free(temp);
    list->size--;
    return token;
}

// Traverse and print the LinkedList
void printLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        printf("Token(Type: %s, Value: %s)\n", current->token->type, current->token->value);
        current = current->next;
    }
}

// Free the LinkedList and its contents
void freeLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}
