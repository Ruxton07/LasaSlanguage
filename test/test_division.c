// test_division.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_division.h"
#ifdef TEST_DIVISION_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_division_int_int(void)
{
    lexer *lex = initLexer("6 / 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(2, result->value.intValue);
}

void test_division_double_int(void)
{
    lexer *lex = initLexer("6.0 / 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, result->value.doubleValue);
}

void test_division_double_float(void)
{
    lexer *lex = initLexer("6.0 / 3.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, result->value.doubleValue);
}

void test_division_float_double(void)
{
    lexer *lex = initLexer("6.0f / 3.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, result->value.doubleValue);
}

void test_division_int_double(void)
{
    lexer *lex = initLexer("6 / 3.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, result->value.doubleValue);
}

void test_division_int_float(void)
{
    lexer *lex = initLexer("6 / 3.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(2.0, result->value.floatValue);
}

void test_division_float_int(void)
{
    lexer *lex = initLexer("6.0f / 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(2.0, result->value.floatValue);
}

#endif // TEST_DIVISION_H