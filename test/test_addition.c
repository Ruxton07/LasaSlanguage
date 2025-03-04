// test_addition.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_addition.h"
#ifdef TEST_ADDITION_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_addition_int_int(void)
{
    lexer *lex = initLexer("1 + 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(3, result->value.intValue);
}

void test_addition_double_int(void)
{
    lexer *lex = initLexer("1.5 + 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_addition_double_float(void)
{
    lexer *lex = initLexer("1.5 + 2.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_addition_float_double(void)
{
    lexer *lex = initLexer("1.5f + 2.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_addition_int_double(void)
{
    lexer *lex = initLexer("1 + 2.5");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

void test_addition_int_float(void)
{
    lexer *lex = initLexer("1 + 2.5f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(3.5, result->value.floatValue);
}

void test_addition_float_int(void)
{
    lexer *lex = initLexer("1.5f + 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(3.5, result->value.floatValue);
}

#endif // TEST_ADDITION_H