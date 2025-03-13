// test_modulus.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_modulus.h"
#ifdef TEST_MODULUS_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_modulus_int_int(void)
{
    lexer *lex = initLexer("6 \% 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(0, result->value.intValue);
}

void test_modulus_double_int(void)
{
    lexer *lex = initLexer("5.5 \% 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, result->value.doubleValue);
}

void test_modulus_double_float(void)
{
    lexer *lex = initLexer("5.5 \% 2.0f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, result->value.doubleValue);
}

void test_modulus_float_double(void)
{
    lexer *lex = initLexer("5.5f \% 2.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, result->value.doubleValue);
}

void test_modulus_int_double(void)
{
    lexer *lex = initLexer("5 \% 2.5");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, result->value.doubleValue);
}

void test_modulus_int_float(void)
{
    lexer *lex = initLexer("5 \% 2.5f");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(0.0, result->value.floatValue);
}

void test_modulus_float_int(void)
{
    lexer *lex = initLexer("5.5f \% 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(1.5, result->value.floatValue);
}

#endif // TEST_MODULUS_H