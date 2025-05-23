// interpreter.c
#include "interpreter.h"
#include "stack.h"

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
    // Create a temporary interpreter for the given list
    interpreter *tempInterp = initInterpreter(list);
    Stack *values = createStack(100); // Stack for values
    Stack *operators = createStack(100); // Stack for operators

    while (tempInterp->curNode) {
        Token *token = tempInterp->curNode->token;

        if (token->type == INTEGER || token->type == FLOAT || token->type == DOUBLE) {
            // Push numeric values onto the value stack
            push(values, *token);
            advanceInterp(tempInterp);
        } else if (token->type == IDENTIFIER) {
            // Handle variables
            Variable *var = findVariable(token->value.charValue);
            if (var) {
                push(values, var->value);
            } else {
                printf("Error: Undefined variable %s.\n", token->value.charValue);
                exit(1);
            }
            advanceInterp(tempInterp);
        } else if (token->type == LPAREN) {
            // Handle nested parentheses
            LinkedList *subExpr = createLinkedList();

            int parenCount = 0; // Track nested parentheses
            
            do {
                if (tempInterp->curNode->token->type == LPAREN) {
                    parenCount++;
                } else if (tempInterp->curNode->token->type == RPAREN) {
                    parenCount--;
                } else {
                    addToken(subExpr, tempInterp->curNode->token);
                }
                advanceInterp(tempInterp);
            } while (tempInterp->curNode && parenCount > 0);
            if (parenCount != 0) {
                printf("Error: Mismatched parentheses in expression.\n");
                exit(1);
            }
            Token *subResult = eval(subExpr); // Recursively evaluate the sub-expression
            push(values, *subResult);
            free(subExpr);
        } else if (token->type == RPAREN) {
            // This should not occur here; parentheses are handled in LPAREN
            printf("Error: Unexpected ')' in expression.\n");
            exit(1);
        } else if (isOperator(token->type)) {
            // Process operators based on precedence
            while (!isEmpty(operators) && precedence(peek(operators).type) >= precedence(token->type)) {
                Token op = pop(operators);
                Token right = pop(values);
                Token left = pop(values);
                Token result = performOp(left, op, right);
                push(values, result);
            }
            push(operators, *token);
            advanceInterp(tempInterp);
        } else if (token->type == SEMICOLON) {
            // Stop processing at the semicolon
            break;
        } else {
            printf("Error in eval: Unexpected token %s.\n", tokenTypeToString(token->type));
            exit(1);
        }
    }

    // Process remaining operators
    while (!isEmpty(operators)) {
        Token op = pop(operators);
        Token right = pop(values);
        Token left = pop(values);
        Token result = performOp(left, op, right);
        push(values, result);
    }

    // The final result should be the only value left on the stack
    Token *result = malloc(sizeof(Token));
    *result = pop(values);

    // Free stacks and temporary interpreter
    free(values->data);
    free(values);
    free(operators->data);
    free(operators);
    free(tempInterp);

    return result;
}

void parseExpr(interpreter *interp) {
    if (!interp->curNode) {
        printf("Error: Unexpected end of tokens.\n");
        exit(1);
    }

    Token *token = interp->curNode->token;

    if (token->type == IF) {
        // Handle if statement
        advanceInterp(interp); // Move to the condition

        if (!interp->curNode || interp->curNode->token->type != LPAREN) {
            printf("Error: Expected '(' after 'if'.\n");
            exit(1);
        }

        // advanceInterp(interp); // Move past '('
        LinkedList *conditionTokens = createLinkedList();

        // Collect condition tokens until ')'
        while (interp->curNode && interp->curNode->token->type != RPAREN) {
            addToken(conditionTokens, interp->curNode->token);
            advanceInterp(interp);
        }

        if (!interp->curNode || interp->curNode->token->type != RPAREN) {
            printf("Error: Missing closing parenthesis in 'if' condition.\n");
            exit(1);
        }

        addToken(conditionTokens, interp->curNode->token);
        advanceInterp(interp);
        Token *conditionResult = eval(conditionTokens);
        if (conditionResult->type != INTEGER || conditionResult->value.intValue == 0) {
            // Skip the block if the condition is false
            while (interp->curNode && interp->curNode->token->type != BLOCKEND) {
                advanceInterp(interp);
            }
            advanceInterp(interp);
        } else {
            // Parse the block if the condition is true
            if (interp->curNode && interp->curNode->token->type == BLOCKSTART) {
                advanceInterp(interp); // Move past '{'
                parseBlock(interp);
                while (interp->curNode && (interp->curNode->token->type == ELIF || interp->curNode->token->type == ELSE)) {
                    while (interp->curNode->token->type != BLOCKEND) {
                        advanceInterp(interp);
                    }
                    advanceInterp(interp);
                }
            } else {
                printf("Error: Missing block start '{' after 'if' condition.\n");
                exit(1);
            }
        }

        // Handle elif and else blocks
        while (interp->curNode && (interp->curNode->token->type == ELIF || interp->curNode->token->type == ELSE)) {
            Token *nextToken = interp->curNode->token;

            if (nextToken->type == ELIF) {
                advanceInterp(interp); // Move to the condition

                if (!interp->curNode || interp->curNode->token->type != LPAREN) {
                    printf("Error: Expected '(' after 'elif'.\n");
                    exit(1);
                }

                advanceInterp(interp); // Move past '('
                LinkedList *elifConditionTokens = createLinkedList();

                // Collect condition tokens until ')'
                while (interp->curNode && interp->curNode->token->type != RPAREN) {
                    addToken(elifConditionTokens, interp->curNode->token);
                    advanceInterp(interp);
                }

                if (!interp->curNode || interp->curNode->token->type != RPAREN) {
                    printf("Error: Missing closing parenthesis in 'elif' condition.\n");
                    exit(1);
                }

                advanceInterp(interp); // Move past ')'

                Token *elifConditionResult = eval(elifConditionTokens);
                if (elifConditionResult->type != INTEGER || elifConditionResult->value.intValue == 0) {
                    // Skip the block if the condition is false
                    while (interp->curNode && interp->curNode->token->type != BLOCKEND) {
                        advanceInterp(interp);
                    }
                    advanceInterp(interp);
                } else {
                    // Parse the block if the condition is true
                    if (interp->curNode && interp->curNode->token->type == BLOCKSTART) {
                        advanceInterp(interp); // Move past '{'
                        parseBlock(interp);
                        // After one block, make the interpreter advanceInterp past all subsequent
                        // elif and else blocks until it reachs a non-elif/non-else token
                        while (interp->curNode && (interp->curNode->token->type == ELIF ||
                            interp->curNode->token->type == ELSE)) {
                            while (interp->curNode->token->type != BLOCKEND) {
                                advanceInterp(interp);
                            }
                            advanceInterp(interp);
                        }
                    } else {
                        printf("Error: Missing block start '{' after 'elif' condition.\n");
                        exit(1);
                    }
                    break; // Exit after executing one block
                }
            } else if (nextToken->type == ELSE) {
                advanceInterp(interp); // Move past 'else'

                if (interp->curNode && interp->curNode->token->type == BLOCKSTART) {
                    advanceInterp(interp); // Move past '{'
                    parseBlock(interp);
                } else {
                    printf("Error: Missing block start '{' after 'else'.\n");
                    exit(1);
                }
                break; // Exit after executing the else block
            }
        }
    } else if (token->type == TYPEASSIGN) {
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
            // printf("Current token: %s\n", tokenTypeToString(interp->curNode->token->type));
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
            // printf("Current token: %s\n", tokenTypeToString(interp->curNode->token->type));
            printf("Error: Expected '=' after identifier '%s'\n", varName);
            exit(1);
        }
    } else {
        printf("Error in parseExpr: Unexpected token %s.\n", tokenTypeToString(token->type));
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

void deinit(interpreter *interp) {
    // clear variables array
    for (int i = 0; i < variableCount; i++) {
        free(variables[i].name); // Free the memory allocated for the variable name
        variables[i].name = NULL; // Set the pointer to NULL for safety
    }
    variableCount = 0; // Reset the variable count
    free(interp);
}