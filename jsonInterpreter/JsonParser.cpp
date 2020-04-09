#include "JsonParser.h"
#include <assert.h>

namespace will
{
#define EXCEPT(c,ch) do {assert(*c->json==(ch));c->json++;} while(0)

	struct TokenContext
	{
		const char* json;
	};

	void tokenParseWhiteSpace(TokenContext* c)
	{
		const char* ptr = c->json;
		while (*ptr ==' ' ||*ptr=='\n' || *ptr == '\r'|| * ptr == '\t')
		{
			ptr++;
		}
		c->json = ptr;
	}

	int tokenParseNull(TokenContext* c, TokenValue* v)
	{
		EXCEPT(c, 'n');
		if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
		{
			return LEPT_PARSE_INVALID_VALUE;
		}
		c->json += 3;
		v->type = LEPT_NULL;
		return LEPT_PARSE_OK;
	}

	int tokenParseValue(TokenContext* c, TokenValue* v)
	{
		switch (*c->json)
		{
		case 'n': return tokenParseNull(c, v);
		case '\0': return LEPT_PARSE_EXPECT_VALUE;
		default:   return LEPT_PARSE_INVALID_VALUE;
		}
	}


	int tokenParse(TokenValue* v, const char* json)
	{
		TokenContext c;
		c.json = json;
		v->type = LEPT_NULL;
		tokenParseWhiteSpace(&c);
		return tokenParseValue(&c, v);
	}

	tokenType tokenGetType(const TokenValue* v)
	{
		assert(v != nullptr);
		return v->type;
	}


}