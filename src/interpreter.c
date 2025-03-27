// interpreter.c
#include "interpreter.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Variable variables[100]; // Array to store variables
int variableCount = 0;

// Function to find a variable by name
Variable *findVariable(char *name) {
    for (int i = 0; i < variableCount; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

// Function to add or update a variable
void setVariable(char *name, Token value) {
    Variable *var = findVariable(name);
    if (var) {
        var->value = value; // Update existing variable
    } else {
        variables[variableCount].name = strdup(name);
        variables[variableCount].value = value;
        variableCount++;
    }
}

// Function to print all stored variables
void printVariables() {
    printf("Stored Variables:\n");
    for (int i = 0; i < variableCount; i++) {
        printf("%s = ", variables[i].name);
        switch (variables[i].value.type) {
            case INTEGER:
                printf("%d\n", variables[i].value.value.intValue);
                break;
            case FLOAT:
                printf("%f\n", variables[i].value.value.floatValue);
                break;
            case DOUBLE:
                printf("%lf\n", variables[i].value.value.doubleValue);
                break;
            default:
                printf("Unknown Type\n");
        }
    }
}

Token *lookupVariable(char *name)
{
    int i = 0;
    Variable *current = malloc(sizeof(variables[i]));
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return &(current->value);
        }
        i++;
        current = &variables[i];
    }
    return NULL;
}

interpreter *initInterpreter(LinkedList *tokenList) {
    interpreter *interp = malloc(sizeof(interpreter));
    interp->tokenList = tokenList;
    interp->curNode = tokenList->head;
    return interp;
}

void advanceInterp(interpreter *interp) {
    if (interp->curNode) {
        interp->curNode = interp->curNode->next;
    }
}

Token *eval(LinkedList *list) {
    interpreter *interp = initInterpreter(list);
    Token *result = malloc(sizeof(Token));
    result->type = BLANK;
    result->value.intValue = 0;

    if (!interp->curNode) {
        return result;
    }

    Token *token = interp->curNode->token;

    if (token->type == INTEGER || token->type == FLOAT || token->type == DOUBLE) {
        result = token;
        advanceInterp(interp);
    } else if (token->type == IDENTIFIER) {
        char *varName = token->value.charValue;
        Variable *var = findVariable(varName);
        if (var) {
            result = &var->value;
            advanceInterp(interp);
        } else {
            printf("Error: Undefined variable %s.\n", varName);
            exit(1);
        }
    } else if (token->type == LPAREN) {
        advanceInterp(interp);
        result = eval(list);
        if (interp->curNode->token->type == RPAREN) {
            advanceInterp(interp);
        } else {
            printf("Error: Missing closing parenthesis.\n");
            exit(1);
        }
    } else {
        printf("Error: Unexpected token %s.\n", tokenTypeToString(token->type));
        exit(1);
    }

    return result;
}

void parseExpr(interpreter *interp) {
    if (!interp->curNode) {
        printf("Error: Unexpected end of tokens.\n");
        exit(1);
    }

    Token *token = interp->curNode->token;

    if (token->type == TYPEASSIGN) {
        // Handle variable declaration with type assignment
        advanceInterp(interp); // Move to the next token (should be the variable name)

        if (!interp->curNode || interp->curNode->token->type != IDENTIFIER) {
            printf("Error: Expected variable name after type declaration.\n");
            exit(1);
        }

        char *varName = interp->curNode->token->value.charValue; // Store the variable name
        advanceInterp(interp); // Move to the next token (should be '=')

        if (!interp->curNode || interp->curNode->token->type != ASSIGN) {
            printf("Error: Expected '=' after variable name.\n");
            printf("Current token: %s\n", tokenTypeToString(interp->curNode->token->type));
            exit(1);
        }

        advanceInterp(interp); // Move to the next token (should be the value)

        // Read from the '=' sign to the ';'
        LinkedList *assignText = createLinkedList();
        while (interp->curNode && interp->curNode->token->type != SEMICOLON) {
            addToken(assignText, interp->curNode->token);
            advanceInterp(interp);
        }

        Token *assignVal = eval(assignText);
        if (assignVal->type == INTEGER || assignVal->type == FLOAT || assignVal->type == DOUBLE) {
            setVariable(varName, *assignVal);

            if (interp->curNode && interp->curNode->token->type == SEMICOLON) {
                advanceInterp(interp); // Move past the semicolon
            } else {
                printf("Error: Missing semicolon after assignment.\n");
                exit(1);
            }
        } else {
            printf("Error: Invalid value in assignment.\n");
            exit(1);
        }
    } else if (token->type == IDENTIFIER) {
        // Handle variable assignment
        char *varName = token->value.charValue;
        advanceInterp(interp);

        if (interp->curNode && interp->curNode->token->type == ASSIGN) {
            advanceInterp(interp);

            // Read from the '=' sign to the ';'
            LinkedList *assignText = createLinkedList();
            while (interp->curNode && interp->curNode->token->type != SEMICOLON) {
                addToken(assignText, interp->curNode->token);
                advanceInterp(interp);
            }

            Token *assignVal = eval(assignText);
            if (assignVal->type == INTEGER || assignVal->type == FLOAT || assignVal->type == DOUBLE) {
                setVariable(varName, *assignVal);

                if (interp->curNode && interp->curNode->token->type == SEMICOLON) {
                    advanceInterp(interp); // Move past the semicolon
                } else {
                    printf("Error: Missing semicolon after assignment.\n");
                    exit(1);
                }
            } else {
                printf("Error: Invalid value in assignment.\n");
                exit(1);
            }
        } else {
            printf("Current token: %s\n", tokenTypeToString(interp->curNode->token->type));
            printf("Error: Expected '=' after identifier.\n");
            exit(1);
        }
    } else {
        printf("Error: Unexpected token %s.\n", tokenTypeToString(token->type));
        exit(1);
    }
}

void parseBlock(interpreter *interp) {
    while (interp->curNode && interp->curNode->token->type != BLOCKEND) {
        parseExpr(interp);
    }

    if (interp->curNode && interp->curNode->token->type == BLOCKEND) {
        advanceInterp(interp); // Move past the block end
    } else {
        printf("Error: Missing block end.\n");
        exit(1);
    }
}

void interpret(interpreter *interp) {
    while (interp->curNode) {
        parseExpr(interp);
    }
}