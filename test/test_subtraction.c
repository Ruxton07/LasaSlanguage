// test_subtraction.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_subtraction.h"
#ifdef TEST_SUBTRACTION_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_subtraction_int_int(void)
{
    lexer *lex = initLexer("1 - 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(-1, result->value.intValue);
}

void test_subtraction_double_int(void)
{
    lexer *lex = initLexer("1.5 - 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(-0.5, result->value.doubleValue);
}

void test_subtraction_double_float(void)
{
    lexer *lex = initLexer("1.5 - 2.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(-0.5, result->value.doubleValue);
}

void test_subtraction_float_double(void)
{
    lexer *lex = initLexer("1.5f - 2.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(-0.5, result->value.doubleValue);
}

void test_subtraction_int_double(void)
{
    lexer *lex = initLexer("1 - 2.5");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(-1.5, result->value.doubleValue);
}

void test_subtraction_int_float(void)
{
    lexer *lex = initLexer("1 - 2.5f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(-1.5, result->value.floatValue);
}

void test_subtraction_float_int(void)
{
    lexer *lex = initLexer("1.5f - 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(-0.5, result->value.floatValue);
}

#endif // TEST_SUBTRACTION_H