#include "JsonParser.h"
#include <assert.h>

namespace will
{
#define EXPECT(c,ch) do {assert(*c->json==(ch));c->json++;} while(0)

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
		EXPECT(c, 'n');
		if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
		{
			return LEPT_PARSE_INVALID_VALUE;
		}
		c->json += 3;
		v->type = LEPT_NULL;
		return LEPT_PARSE_OK;
	}

	int tokenParseTrue(TokenContext* c, TokenValue* v)
	{
		EXPECT(c, 't');
		if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
		{
			return LEPT_PARSE_INVALID_VALUE;
		}
		c->json += 3;
		v->type = LEPT_TRUE;
		return LEPT_PARSE_OK;
	}

	int tokenParseFalse(TokenContext* c, TokenValue* v)
	{
		EXPECT(c, 'f');
		if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
		{
			return LEPT_PARSE_INVALID_VALUE;
		}
		c->json += 4;
		v->type = LEPT_FALSE;
		return LEPT_PARSE_OK;
	}

	int tokenParseValue(TokenContext* c, TokenValue* v)
	{
		switch (*c->json)
		{
		case 'n': return tokenParseNull(c, v);
		case 't':return tokenParseTrue(c, v);
		case 'f':return tokenParseFalse(c, v);
		case '\0': return LEPT_PARSE_EXPECT_VALUE;
		default:   return LEPT_PARSE_INVALID_VALUE;
		}
	}


	int tokenParse(TokenValue* v, const char* json)
	{
		int ret;
		TokenContext c;
		c.json = json;
		v->type = LEPT_NULL;
		tokenParseWhiteSpace(&c);
		if ((ret = tokenParseValue(&c, v)) == LEPT_PARSE_OK)
		{
			tokenParseWhiteSpace(&c);
			if (*c.json != '\0')
			{
				ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
			}
		}
		return ret;
	}

	tokenType tokenGetType(const TokenValue* v)
	{
		assert(v != nullptr);
		return v->type;
	}


}