// test_postdec.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_postdec.h"
#ifdef TEST_POSTDEC_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_postdecrement_int(void)
{
    lexer *lex = initLexer("2--");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(1, result->value.intValue);
}

void test_postdecrement_float(void)
{
    lexer *lex = initLexer("2.5f--");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(1.5, result->value.floatValue);
}

void test_postdecrement_double(void)
{
    lexer *lex = initLexer("2.5--");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.5, result->value.doubleValue);
}

#endif // TEST_POSTDEC_H