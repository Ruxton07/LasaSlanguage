// test_exponentiation.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_exponentiation.h"
#ifdef TEST_EXPONENTIATION_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_exponentiation_int_int(void)
{
    lexer *lex = initLexer("2 ^ 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(8, result->value.intValue);
}

void test_exponentiation_float_int(void)
{
    lexer *lex = initLexer("2.0f ^ 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(8.0, result->value.floatValue);
}

void test_exponentiation_double_int(void)
{
    lexer *lex = initLexer("2.0 ^ 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(8.0, result->value.doubleValue);
}

void test_exponentiation_int_float(void)
{
    lexer *lex = initLexer("2 ^ 3.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(8.0, result->value.floatValue);
}

void test_exponentiation_int_double(void)
{
    lexer *lex = initLexer("2 ^ 3.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(8.0, result->value.doubleValue);
}

void test_exponentiation_float_double(void)
{
    lexer *lex = initLexer("2.0f ^ 3.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(8.0, result->value.doubleValue);
}

#endif // TEST_EXPONENTIATION_H