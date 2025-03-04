// test_multiplication.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_multiplication.h"
#ifdef TEST_MULTIPLICATION_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_multiplication_int_int(void)
{
    lexer *lex = initLexer("2 * 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(6, result->value.intValue);
}

void test_multiplication_double_int(void)
{
    lexer *lex = initLexer("1.5 * 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_multiplication_double_float(void)
{
    lexer *lex = initLexer("1.5 * 2.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_multiplication_float_double(void)
{
    lexer *lex = initLexer("1.5f * 2.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_multiplication_int_double(void)
{
    lexer *lex = initLexer("2 * 1.5");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_multiplication_int_float(void)
{
    lexer *lex = initLexer("2 * 1.5f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(3.0, result->value.floatValue);
}

void test_multiplication_float_int(void)
{
    lexer *lex = initLexer("1.5f * 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(3.0, result->value.floatValue);
}

#endif // TEST_MULTIPLICATION_H