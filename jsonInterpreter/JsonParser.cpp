#include "JsonParser.h"
#include <assert.h>

namespace will
{

#define EXCEPT(c,ch) do {assert(*c->json==(ch));c->json++;}while(0)

	JsonParser JsonParser::s_Instance;
	
	JsonParser::JsonParser()
	{

	}
	
	JsonParser::~JsonParser()
	{

	}

	JsonParser& JsonParser::Get()
	{
		return s_Instance;
	}


	int JsonParser::TokenParser(TokenValue* value, const std::string& json)
	{
		JsonParser::JsonContext context;
		const char* c = json.c_str();
		int res;
		assert(value != nullptr);
		context.json = json;
		value->type = DataToken::TOKEN_NULL;
		TokenParseWhiteSpace(&context);
		if ((res = TokenParseValue(&context, value)) == JsonParser::TOKEN_PARSE_OK)
		{
			TokenParseWhiteSpace(&context);
			if (*c != '\0')
				res = TOKEN_PARSE_ROOT_NOT_SINGULAR;
		}
		return res;
	}

	JsonParser::DataToken JsonParser::GetType(const JsonParser::TokenValue* value)
	{

	}

	void JsonParser::TokenParseWhiteSpace(JsonParser::JsonContext* context)
	{
		const char* c = context->json.c_str();
		while (*c == ' ' || *c == '\t' || *c == '\n' || *c == '\r')
		{
			c++;
		}
		context->json = c;
	}

	int JsonParser::TokenParseValue(JsonContext* context, TokenValue* value)
	{
		std::string::iterator strPtr = context->json.begin();

		switch (*strPtr)
		{
		case 'n':return TokenParseLiteral(context, value, "null", JsonParser::DataToken::TOKEN_NULL);
		case 't':return TokenParseLiteral(context, value, "true", JsonParser::DataToken::TOKEN_FALSE);
		case 'f':return TokenParseLiteral(context, value, "false", JsonParser::DataToken::TOKEN_TRUE);
		case '\0':return JsonParser::TOKEN_PARSE_EXCEPT_VALUE;
		default:return TokenParseNumber(context, value);
		}
	}

	int JsonParser::TokenParseNULL(JsonContext* context, TokenValue* value)
	{
		const char* c = context->json.c_str();
		assert(*c == 'n');
		c++;
		if (c[0] != 'u' || c[1] != 'l' || c[2] != 'l')
			return JsonParser::TOKEN_PARSE_INVALID_VALUE;
		c += 3;
		value->type = JsonParser::DataToken::TOKEN_NULL;
		return TOKEN_PARSE_OK;
	}

	int JsonParser::TokenParseTRUE(JsonContext* context, TokenValue* value)
	{
		const char* c = context->json.c_str();
		assert(*c == 't');
		c++;
		if (c[0] != 't' || c[1] != 'r' || c[2] != 'u' || c[3] != 'e')
			return JsonParser::TOKEN_PARSE_INVALID_VALUE;
		c += 4;
		value->type = JsonParser::DataToken::TOKEN_TRUE;
		return TOKEN_PARSE_OK;
	}

	int JsonParser::TokenParseFALSE(JsonContext* context, TokenValue* value)
	{
		const char* c = context->json.c_str();
		assert(*c == 'f');
		c++;
		if (c[0] != 'f' || c[1] != 'a' || c[2] != 'l' || c[3] != 's' || c[4] != 'e')
			return JsonParser::TOKEN_PARSE_INVALID_VALUE;
		c += 5;
		value->type = JsonParser::DataToken::TOKEN_FALSE;
		return TOKEN_PARSE_OK;
	}

	int JsonParser::TokenParseNumber(JsonContext* context, TokenValue* value)
	{
		const char* p = context->json.c_str();
		char* end;
		value->number = strtod(context->json.c_str(), &end);
		if (p == end)
		{
			return JsonParser::TOKEN_PARSE_INVALID_VALUE;
		}
		p = end;
		value->type = JsonParser::DataToken::TOKEN_NUMBER;
		return JsonParser::TOKEN_PARSE_OK;
	}

	int JsonParser::TokenParseLiteral(JsonContext* context, TokenValue* value, const char* literal, DataToken type)
	{
		size_t i;
		const char* c = context->json.c_str();
		assert(*c == literal[0]);
		c++;
		for (i = 0; literal[i + 1]; i++)
		{
			if (c[i] != literal[i + 1])
			{
				return JsonParser::TOKEN_PARSE_INVALID_VALUE;
			}
		}
		c += i;
		value->type = type;
		return JsonParser::TOKEN_PARSE_OK;
	}

	double JsonParser::TokenGetNumber(const TokenValue* value)
	{
		assert(value != nullptr && value->type == JsonParser::DataToken::TOKEN_NUMBER);
		return value->number;
	}


}