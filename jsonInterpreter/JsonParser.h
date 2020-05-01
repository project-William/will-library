#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace will
{
	typedef enum
	{
		LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
	}tokenType;

	struct TokenValue
	{
		double n;
		tokenType type;
	};




	enum {
		LEPT_PARSE_OK = 0,
		LEPT_PARSE_EXPECT_VALUE,
		LEPT_PARSE_INVALID_VALUE,
		LEPT_PARSE_ROOT_NOT_SINGULAR
	};

	int tokenParse(TokenValue* v, const char* json);
	tokenType tokenGetType(const TokenValue* v);
	double tokenGetNumber(const TokenValue* v);

}