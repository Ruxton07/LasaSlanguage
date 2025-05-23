/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
/* injected defines for unity settings, etc */
#ifndef UNITY_INCLUDE_DOUBLE
#define UNITY_INCLUDE_DOUBLE
#endif /* UNITY_INCLUDE_DOUBLE */
#ifndef UNITY_INCLUDE_FLOAT
#define UNITY_INCLUDE_FLOAT
#endif /* UNITY_INCLUDE_FLOAT */
#ifndef UNITY_DOUBLE_PRECISION
#define UNITY_DOUBLE_PRECISION=1e-12
#endif /* UNITY_DOUBLE_PRECISION */
#ifndef UNITY_FLOAT_PRECISION
#define UNITY_FLOAT_PRECISION=1e-6
#endif /* UNITY_FLOAT_PRECISION */
#include "lexer.h"
#include "token.h"
#include "stack.h"
#include "test_postdec.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_postdecrement_int(void);
extern void test_postdecrement_float(void);
extern void test_postdecrement_double(void);


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
      UnityPrint("test_postdec.");
      UNITY_PRINT_EOL();
      UnityPrint("  test_postdecrement_int");
      UNITY_PRINT_EOL();
      UnityPrint("  test_postdecrement_float");
      UNITY_PRINT_EOL();
      UnityPrint("  test_postdecrement_double");
      UNITY_PRINT_EOL();
      return 0;
    }
    return parse_status;
  }
#endif
  UnityBegin("test_postdec.c");
  run_test(test_postdecrement_int, "test_postdecrement_int", 18);
  run_test(test_postdecrement_float, "test_postdecrement_float", 25);
  run_test(test_postdecrement_double, "test_postdecrement_double", 32);

  return UNITY_END();
}
