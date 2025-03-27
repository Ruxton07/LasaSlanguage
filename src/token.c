// token.c
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *tokenTypeToString(TokenType type)
{
    switch (type)
    {
    // DATA TYPES
    case INTEGER:
        return "INTEGER";
    case FLOAT:
        return "FLOAT";
    case DOUBLE:
        return "DOUBLE";
    case CHAR:
        return "CHAR";
    case STRING:
        return "STRING";
    // EXPRESSIONS
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case EXP:
        return "EXP";
    case MOD:
        return "MOD";
    case POSTINC:
        return "INC";
    case POSTDEC:
        return "DEC";
    case PREINC:
        return "PREINC";
    case PREDEC:
        return "PREDEC";
    case LPAREN:
        return "LPAREN";
    case RPAREN:
        return "RPAREN";
    case END_OF_FILE:
        return "EOF";
    // INSTRUCTIONS
    case IF:
        return "IF";
    case ELSE:
        return "ELSE";
    case ELIF:
        return "ELIF";
    case WHILE:
        return "WHILE";
    case FOR:
        return "FOR";
    case RETURN:
        return "RETURN";
    case BREAK:
        return "BREAK";
    case CONTINUE:
        return "CONTINUE";
    // INSTANTIATION
    case TYPEASSIGN:
        return "TYPEASSIGN";
    case IDENTIFIER:
        return "IDENTIFIER";
    case ASSIGN:
        return "ASSIGN";
    // COMPARISON
    case EQ:
        return "EQ";
    case NEQ:
        return "NEQ";
    case GT:
        return "GT";
    case LT:
        return "LT";
    case GTE:
        return "GTE";
    case LTE:
        return "LTE";
    // LOGICAL
    case AND:
        return "AND";
    case OR:
        return "OR";
    case NOT:
        return "NOT";
    case XOR:
        return "XOR";
    // BITWISE
    case BAND:
        return "BAND";
    case BOR:
        return "BOR";
    case BNOT:
        return "BNOT";
    case BXOR:
        return "BXOR";
    // POSITIONING CONTROL
    case COMMA:
        return "COMMA";
    case SEMICOLON:
        return "SEMICOLON";
    case COLON:
        return "COLON";
    case BLOCKSTART:
        return "BLOCKSTART";
    case BLOCKEND:
        return "BLOCKEND";
    // MISC
    case BLANK:
        return "BLANK";
    default:
        return "UNKNOWN";
    }
}

TokenType dataTypetoTokenType(char *str)
{
    if (strcmp(str, "int") == 0)
    {
        return INTEGER;
    }
    if (strcmp(str, "float") == 0)
    {
        return FLOAT;
    }
    if (strcmp(str, "double") == 0)
    {
        return DOUBLE;
    }
    printf("Could not classify data type: %s\n", str);
    return END_OF_FILE;
}

TokenType charToTokenType(char c)
{
    switch (c)
    {
    case '+':
        return PLUS;
    case '-':
        return MINUS;
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '^':
        return EXP;
    case '%':
        return MOD;
    case '(':
        return LPAREN;
    case ')':
        return RPAREN;
    default:
        return END_OF_FILE;
    }
}

Token initBlankToken()
{
    Token token;
    token.type = END_OF_FILE;
    token.value = (TokenValue){-1};
    return token;
}

Token initToken(TokenType type, TokenValue value)
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

void printToken(Token *token)
{
    printf("Token@%p: Type: %s,\nValues:\n%d\n%f\n%f\n%c\n", (void *)token, tokenTypeToString(token->type),
           token->value.intValue, token->value.floatValue, token->value.doubleValue, token->value.charValue);
}

char* numericVal(Token *token) {
    char *val = malloc(20);
    switch (token->type) {
        case INTEGER:
            sprintf(val, "%d", token->value.intValue);
            break;
        case FLOAT:
            sprintf(val, "%f", token->value.floatValue);
            break;
        case DOUBLE:
            sprintf(val, "%f", token->value.doubleValue);
            break;
        default:
            sprintf(val, "Can't resolve NumVal for type: %s", tokenTypeToString(token->type));
            break;
    }
    return val;
}
