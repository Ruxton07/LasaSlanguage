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
    TEST_MESSAGE("===== start test_interpret_1 =====");
    char *sourceCode = "a = 5; b = a + 10; if (b > 10) { a = a + 10; }";
    interpreter *interp = initInterpreter(tokenizeSourceCode(sourceCode));

    interpret(interp);
    printVariables();
    free(interp);
    TEST_PASS_MESSAGE("test_interpret_1 did not error. Please check that any output is as expected.");
    TEST_MESSAGE("===== end test_interpret_1 =====");
}

void test_interpret_2(void) {
    TEST_IGNORE_MESSAGE("Implement test_interpret_2");
}

void test_interpret_3(void) {
    TEST_IGNORE_MESSAGE("Implement test_interpret_3");
}

void test_interpret_4(void) {
    TEST_IGNORE_MESSAGE("Implement test_interpret_4");
}

void test_interpret_5(void) {
    TEST_IGNORE_MESSAGE("Implement test_interpret_5");
}

#endif // TEST_INTERPRET_H