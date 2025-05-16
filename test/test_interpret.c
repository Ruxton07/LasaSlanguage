// test_interpret.c
#include "interpreter.h"
#include "LinkedList.h"
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include <stdlib.h>

#include "unity.h"
#include "test_interpret.h"
#ifdef TEST_INTERPRET_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_interpret_1(void) {
    printf("\n\n");
    printf("===== start test_interpret_1 =====");
    char *sourceCode = "motion a = 3+5; motion b = a + 10; midterm (b > 6) { a = b + 3; }";
    interpreter *interp = initInterpreter(tokenizeSourceCode(sourceCode));

    interpret(interp);
    printVariables();
    deinit(interp);
    printf("===== end test_interpret_1 =====");
    printf("\n");
    TEST_PASS_MESSAGE("test_interpret_1 did not error. Please check that any output is as expected.");
}

void test_interpret_2(void) {
    printf("\n\n");
    printf("===== start test_interpret_2 =====");
    char *sourceCode = " \
    motion x = 10; \
    motion y = 20; \
    midterm (x < y) { \
    x = x + 5; \
    } \
    quiz (x == y) { \
    x = x - 5; \
    } nonchalant { \
    x = x * 2; \
    }";
    interpreter *interp = initInterpreter(tokenizeSourceCode(sourceCode));

    interpret(interp);
    printVariables();
    printf("gng what");
    deinit(interp);
    printf("===== end test_interpret_2 =====");
    printf("\n");
    TEST_PASS_MESSAGE("test_interpret_2 did not error. Please check that any output is as expected.");
}

void test_interpret_3(void) {
    printf("\n\n");
    printf("===== start test_interpret_3 =====");
    char *sourceCode = " \
    motion a = 5; \
    motion b = 10; \
    midterm (a > b) { \
        a = a + b; \
    } quiz (a < b) { \
        b = b - a; \
    } nonchalant { \
        a = a * b; \
    }";
    interpreter *interp = initInterpreter(tokenizeSourceCode(sourceCode));

    interpret(interp);
    printVariables();
    deinit(interp);
    printf("===== end test_interpret_3 =====");
    printf("\n");
    TEST_PASS_MESSAGE("test_interpret_3 did not error. Please check that any output is as expected.");
}

void test_interpret_4(void) {
    printf("\n\n");
    printf("===== start test_interpret_4 =====");
    char *sourceCode = " \
    motion a = 3; \
    motion b = 9; \
    midterm (a < b and b > 5) { \
        a = a + b; \
    } quiz (a == b or b < 15) { \
        b = b - a; \
    } nonchalant { \
        a = a * b; \
    }";
    interpreter *interp = initInterpreter(tokenizeSourceCode(sourceCode));

    interpret(interp);
    printVariables();
    deinit(interp);
    printf("===== end test_interpret_4 =====");
    printf("\n");
    TEST_PASS_MESSAGE("test_interpret_4 did not error. Please check that any output is as expected.");
}

void test_interpret_5(void) {
    printf("\n\n");
    printf("===== start test_interpret_5 =====");
    char *sourceCode = " \
    motion a = (1 + 4 + 0); \
    motion b = 10; \
    midterm (a <= b) { \
        a = a + b; \
    } quiz (a stacia b) { \
        b = b - a; \
    } nonchalant { \
        a = a * b; \
    }";
    interpreter *interp = initInterpreter(tokenizeSourceCode(sourceCode));

    interpret(interp);
    printVariables();
    deinit(interp);
    printf("===== end test_interpret_5 =====");
    printf("\n");
    TEST_PASS_MESSAGE("test_interpret_5 did not error. Please check that any output is as expected.");
}

#endif // TEST_INTERPRET_H