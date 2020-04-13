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


	void testNull()
	{
		TokenValue v;
		v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_OK, tokenParse(&v, "null"));
        EXPECT_EQ_INT(LEPT_NULL, tokenGetType(&v));
	}

    void testTrue()
    {
        TokenValue v;
        v.type = LEPT_TRUE;
        EXPECT_EQ_INT(LEPT_PARSE_OK, tokenParse(&v, "true"));
        EXPECT_EQ_INT(LEPT_TRUE, tokenGetType(&v));
    }

    void testFalse()
    {
        TokenValue v;
        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_OK, tokenParse(&v, "false"));
        EXPECT_EQ_INT(LEPT_FALSE, tokenGetType(&v));
    }

    void testParseExpectValue()
    {
        TokenValue v;
        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, tokenParse(&v, ""));
        EXPECT_EQ_INT(LEPT_NULL, tokenGetType(&v));


        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, tokenParse(&v, " "));
        EXPECT_EQ_INT(LEPT_NULL, tokenGetType(&v));
    }


    void testParseInvalidValue() {
        TokenValue v;
        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, tokenParse(&v, "nul"));
        EXPECT_EQ_INT(LEPT_NULL, tokenGetType(&v));

        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, tokenParse(&v, "?"));
        EXPECT_EQ_INT(LEPT_NULL, tokenGetType(&v));
    }

    void testParseRootNotSingular() {
        TokenValue v;
        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_ROOT_NOT_SINGULAR, tokenParse(&v, "null x"));
        EXPECT_EQ_INT(LEPT_NULL, tokenGetType(&v));
    }

    void testParse() {
        testNull();
        testFalse();
        testTrue();
        testParseExpectValue();
        testParseExpectValue();
        testParseRootNotSingular();
    }

}





