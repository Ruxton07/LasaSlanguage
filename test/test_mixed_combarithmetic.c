// test_mixed_combarithmetic.c
#include "lexer.h"
#include "token.h"
#include "stack.h"

#include "unity.h"
#include "test_mixed_combarithmetic.h"
#ifdef TEST_MIXED_COMBARITHMETIC_H

void setUp(void)
{
}

void tearDown(void)
{
}

void test_mixed_expr1(void)
{
    lexer *lex = initLexer("1.0f * 3.0 / (1 + (2.0 - 2.0f)) - 4");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(-1.0, result->value.doubleValue);
}

void test_mixed_subexpr1(void)
{
    lexer *lex = initLexer("(1 + (2.0 - 2.0f))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, result->value.doubleValue);
}

void test_mixed_subexpr2(void)
{
    lexer *lex = initLexer("3.0 / (1 + (2.0 - 2.0f))");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_mixed_subexpr3(void)
{
    lexer *lex = initLexer("1.0f * 3.0 / (1 + (2.0 - 2.0f)) ");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_mixed_subexpr4(void)
{
    lexer *lex = initLexer("1.0f * 3.0f / (1 + (2.0 - 2.0f))- 4");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(-1.0, result->value.doubleValue);
}

void test_mixed_expr2(void)
{
    lexer *lex = initLexer("(1 + 2.0) * (3.0f - 1.0) / 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

void test_mixed_expr3(void)
{
    lexer *lex = initLexer("5.0 + 3 * (2.0f - 1) / 4.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(5.75, result->value.doubleValue);
}

void test_mixed_expr4(void)
{
    lexer *lex = initLexer("10 / 2.0f + 3.0 * (4 - 1.0)");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(14.0, result->value.doubleValue);
}

void test_mixed_expr5(void)
{
    lexer *lex = initLexer("((2.0 + 3.0f) * 4 - 5) / 2.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(7.5, result->value.doubleValue);
}

void test_mixed_expr6(void)
{
    lexer *lex = initLexer("3.0f + 4 * (2.0 - 1.0f) / 2 - 5");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, result->value.doubleValue);
}

void test_mixed_expr7(void)
{
    lexer *lex = initLexer("6.0f / 2 * (1 + 2.0f) - 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_FLOAT(6.0, result->value.floatValue);
}

void test_mixed_expr8(void)
{
    lexer *lex = initLexer("2.0f * (3 + 4.0) / (1.0 - 0.5f)");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(28.0, result->value.doubleValue);
}

void test_mixed_expr9(void)
{
    lexer *lex = initLexer("5.0 + 3.0f * (2 - 1.0) / 4");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(5.75, result->value.doubleValue);
}

void test_mixed_expr10(void)
{
    lexer *lex = initLexer("8.0 / (2.0f + 2) * 3 - 1");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(5.0, result->value.doubleValue);
}

void test_mixed_expr11(void)
{
    lexer *lex = initLexer("7.0f + 2 * (3.0 - 1) / 2.0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(9.0, result->value.doubleValue);
}

void test_mixed_expr12(void)
{
    lexer *lex = initLexer("9 / 3 + (4) * (2 - 1) * 0");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL(3, result->value.intValue);
}

void test_mixed_expr13(void)
{
    lexer *lex = initLexer("10.0f - 3 * (2.0 + 1) / 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(7.0, result->value.doubleValue);
}

void test_mixed_expr14(void)
{
    lexer *lex = initLexer("4.0 + 5.0f * (3 - 2.0) / 2");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(6.5, result->value.doubleValue);
}

void test_mixed_expr15(void)
{
    lexer *lex = initLexer("12.0 / (3.0f + 1) * 2 - 3");
    Token *result = expr(lex);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, result->value.doubleValue);
}

#endif // TEST_MIXED_COMBARITHMETIC_H