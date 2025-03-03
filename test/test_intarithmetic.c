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
    TEST_ASSERT_EQUAL(3, result->value.intValue);
}
void test_subtraction(void) {
    lexer* lex = initLexer("1 - 2");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(-1, result->value.intValue);
}
void test_multiplication(void) {
    lexer* lex = initLexer("2 * 3");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(6, result->value.intValue);
}
void test_division(void) {
    lexer* lex = initLexer("6 / 3");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(2, result->value.intValue);
}

void test_modulus(void)
{
    lexer* lex = initLexer("6 % 3");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(0, result->value.intValue);
}

void test_increment(void)
{
    lexer* lex = initLexer("2++");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(3, result->value.intValue);
}

void test_decrement(void)
{
    lexer* lex = initLexer("2--");
    Token* result = expr(lex);
    TEST_ASSERT_EQUAL(1, result->value.intValue);
}

void test_exponentiation(void)
{
    lexer* lex = initLexer("2 ^ 3");
    Token* result = expr(lex);
    printf("%d\n", result->value.intValue);
    printf("%d\n", result->value.doubleValue);
    printf("%f\n", result->value.floatValue);
    TEST_ASSERT_EQUAL(8, result->value.intValue);
}