// test_isoarithmetic.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_mixed_isoarithmetic.h"
#ifdef TEST_MIXED_ISOARITHMETIC_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_mixed_addition_1(void)
{
    lexer *lex = initLexer("(1+2.5)+3 + 4.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_mixed_addition_2(void)
{
    lexer *lex = initLexer("2.0f + (3 + 4.0f) + 5.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_mixed_addition_3(void)
{
    lexer *lex = initLexer("1 + (2 + (3 + 4))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(10, result->value.intValue);
}

void test_mixed_subtraction_1(void)
{
    lexer *lex = initLexer("(1-2.5)-3 - 4.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(-8.5, result->value.doubleValue);
}

void test_mixed_subtraction_2(void)
{
    lexer *lex = initLexer("2.0f - (3 - 4.0f) - 5.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_mixed_subtraction_3(void)
{
    lexer *lex = initLexer("1 - (2 - (3 - 4))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(2, result->value.intValue);
}

void test_mixed_multiplication_1(void)
{
    lexer *lex = initLexer("(1*2.5)*3 * 4.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(30.0, result->value.doubleValue);
}

void test_mixed_multiplication_2(void)
{
    lexer *lex = initLexer("2.0f * (3 * 4.0f) * 5.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(120.0, result->value.doubleValue);
}

void test_mixed_multiplication_3(void)
{
    lexer *lex = initLexer("1 * (2 * (3 * 4))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(24, result->value.intValue);
}

void test_mixed_division_1(void)
{
    lexer *lex = initLexer("(1/2.5)/3 / 4.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(0.08, result->value.doubleValue);
}

void test_mixed_division_2(void)
{
    lexer *lex = initLexer("2.0f / (3 / 4.0f) / 5.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(2.6666666666666665, result->value.doubleValue);
}

void test_mixed_division_3(void)
{
    lexer *lex = initLexer("1 / (2 / (3 / 4))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(6, result->value.intValue);
}

void test_mixed_exponentiation_1(void)
{
    lexer *lex = initLexer("(1^2.5)^3 ^ 4.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, result->value.doubleValue);
}

void test_mixed_exponentiation_2(void)
{
    lexer *lex = initLexer("1.5f ^ (3 ^ 2.0f) ^ 1.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(38.443359375, result->value.doubleValue);
}

void test_mixed_exponentiation_3(void)
{
    lexer *lex = initLexer("2 ^ (3 ^ (1 ^ 4))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(8, result->value.intValue);
}

void test_mixed_modulus_1(void)
{
    lexer *lex = initLexer("(1\%2.5)\%3 \% 4.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(0.5, result->value.doubleValue);
}

void test_mixed_modulus_2(void)
{
    lexer *lex = initLexer("2.0f \% (3 \% 4.0f) \% 5.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, result->value.doubleValue);
}

void test_mixed_modulus_3(void)
{
    lexer *lex = initLexer("1 \% (2 \% (3 \% 4))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(1, result->value.intValue);
}

void test_mixed_post_increment_1(void)
{
    lexer *lex = initLexer("1++");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(1, result->value.intValue);
}

void test_mixed_post_increment_2(void)
{
    lexer *lex = initLexer("1.5f++");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(1.5, result->value.floatValue);
}

void test_mixed_post_increment_3(void)
{
    lexer *lex = initLexer("1.5++");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, result->value.doubleValue);
}

void test_mixed_post_decrement_1(void)
{
    lexer *lex = initLexer("(1--)--");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(1, result->value.intValue);
}

void test_mixed_post_decrement_2(void)
{
    lexer *lex = initLexer("1.5f--");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(1.5, result->value.floatValue);
}

void test_mixed_post_decrement_3(void)
{
    lexer *lex = initLexer("1.5--");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, result->value.doubleValue);
}

#endif // TEST_MIXED_ISOARITHMETIC_H