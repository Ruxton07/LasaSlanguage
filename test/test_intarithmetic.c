#include "test_intarithmetic.h"
#ifdef TEST_INTARITHMETIC_H

#include "unity.h"

#include "lexer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_addition(void) {
    lexer* lex = initLexer("1 + 2");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(3, result->value);
}
void test_subtraction(void) {
    lexer* lex = initLexer("1 - 2");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(-1, result->value);
}
void test_multiplication(void) {
    lexer* lex = initLexer("2 * 3");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(6, result->value);
}
void test_division(void) {
    lexer* lex = initLexer("6 / 3");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(2, result->value);
}

void test_modulus(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement integer modulus");
}

void test_increment(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement integer increment");
}

void test_decrement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement integer decrement");
}

void test_exponentiation(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement integer exponentiation");
}

#endif // TEST_INTARITHMETIC_H
