// test_postinc.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_postinc.h"
#ifdef TEST_POSTINC_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_postincrement_int(void)
{
    lexer *lex = initLexer("2++");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(3, result->value.intValue);
}

void test_postincrement_float(void)
{
    lexer *lex = initLexer("2.5f++");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(3.5, result->value.floatValue);
}

void test_postincrement_double(void)
{
    lexer *lex = initLexer("2.5++");
    printf("ok are u dumb or dumb\n");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.5, result->value.doubleValue);
}

#endif // TEST_POSTINC_H