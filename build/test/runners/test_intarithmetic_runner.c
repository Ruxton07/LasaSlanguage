/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
/* injected defines for unity settings, etc */
#ifndef UNITY_EXCLUDE_FLOAT
#define UNITY_EXCLUDE_FLOAT
#endif /* UNITY_EXCLUDE_FLOAT */
#include "test_intarithmetic.h"
#include "lexer.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_addition(void);
extern void test_subtraction(void);
extern void test_multiplication(void);
extern void test_division(void);
extern void test_modulus(void);
extern void test_increment(void);
extern void test_decrement(void);
extern void test_exponentiation(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = (UNITY_UINT) line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
 int main(int argc, char** argv)
{
#ifdef UNITY_USE_COMMAND_LINE_ARGS
  int parse_status = UnityParseOptions(argc, argv);
  if (parse_status != 0)
  {
    if (parse_status < 0)
    {
      UnityPrint("test_intarithmetic.");
      UNITY_PRINT_EOL();
      UnityPrint("  test_addition");
      UNITY_PRINT_EOL();
      UnityPrint("  test_subtraction");
      UNITY_PRINT_EOL();
      UnityPrint("  test_multiplication");
      UNITY_PRINT_EOL();
      UnityPrint("  test_division");
      UNITY_PRINT_EOL();
      UnityPrint("  test_modulus");
      UNITY_PRINT_EOL();
      UnityPrint("  test_increment");
      UNITY_PRINT_EOL();
      UnityPrint("  test_decrement");
      UNITY_PRINT_EOL();
      UnityPrint("  test_exponentiation");
      UNITY_PRINT_EOL();
      return 0;
    }
    return parse_status;
  }
#endif
  UnityBegin("test_intarithmetic.c");
  run_test(test_addition, "test_addition", 16);
  run_test(test_subtraction, "test_subtraction", 21);
  run_test(test_multiplication, "test_multiplication", 26);
  run_test(test_division, "test_division", 31);
  run_test(test_modulus, "test_modulus", 37);
  run_test(test_increment, "test_increment", 42);
  run_test(test_decrement, "test_decrement", 47);
  run_test(test_exponentiation, "test_exponentiation", 52);

  return UNITY_END();
}
