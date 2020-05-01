#pragma once

#include "JsonParser.h"

namespace will
{
    static int main_ret = 0;
    static int test_pass = 0;
    static int test_count = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect,actual) EXPECT_EQ_BASE((expect)==(actual),expect,actual,"%d")

#define TEST_ERROR(expectRes, expectType, json)\
    do{\
        TokenValue v;\
        v.type=LEPT_FALSE;\
        EXPECT_EQ_INT(expectRes,tokenParse(&v,json));\
        EXPECT_EQ_INT(expectType,tokenGetType(&v));\
    } while (0)\


#define TEST_NUMBER(expect,json)\
    do{\
        TokenValue v;\
        EXPECT_EQ_INT(LEPT_PARSE_OK, tokenParse(&v,json));\
        EXPECT_EQ_INT(LEPT_NUMBER,tokenGetType(&v));\
        EXPECT_EQ_DOUBLE(expect, tokenGetNumber(&v));\
    }while(0)\


    void testParseNumber()
    {
        TEST_NUMBER(0.0, "0");
        TEST_NUMBER(0.0, "-0");
        TEST_NUMBER(0.0, "-0.0");
        TEST_NUMBER(1.0, "1");
        TEST_NUMBER(-1.0, "-1");
        TEST_NUMBER(1.5, "1.5");
        TEST_NUMBER(-1.5, "-1.5");
        TEST_NUMBER(3.1416, "3.1416");
        TEST_NUMBER(1E10, "1E10");
        TEST_NUMBER(1e10, "1e10");
        TEST_NUMBER(1E+10, "1E+10");
        TEST_NUMBER(1E-10, "1E-10");
        TEST_NUMBER(-1E10, "-1E10");
        TEST_NUMBER(-1e10, "-1e10");
        TEST_NUMBER(-1E+10, "-1E+10");
        TEST_NUMBER(-1E-10, "-1E-10");
        TEST_NUMBER(1.234E+10, "1.234E+10");
        TEST_NUMBER(1.234E-10, "1.234E-10");
        TEST_NUMBER(0.0, "1e-10000");
    }

	void testNull()
	{
        TEST_ERROR(LEPT_PARSE_OK, LEPT_NULL, "null");
   	}

    void testTrue()
    {
        TEST_ERROR(LEPT_PARSE_OK, LEPT_TRUE, "true");
    }

    void testFalse()
    {
        TEST_ERROR(LEPT_PARSE_OK, LEPT_FALSE, "false");
    }

    void testParseExpectValue()
    {
        TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, LEPT_NULL, "");
        TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, LEPT_NULL, " ");
    }


    void testParseInvalidValue() {
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "nul");
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "?");

        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "+0");
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "+1");
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, ".123"); /* at least one digit before '.' */
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "1.");   /* at least one digit after '.' */
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "INF");
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "inf");
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "NAN");
        TEST_ERROR(LEPT_PARSE_INVALID_VALUE, LEPT_NULL, "nan");
    }

    void testParseRootNotSingular() {
        TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, LEPT_NULL, "null x");
    }

    void testParse() {
        testParseNumber();
        testNull();
        testFalse();
        testTrue();
        testParseExpectValue();
        testParseExpectValue();
        testParseRootNotSingular();
    }

}





