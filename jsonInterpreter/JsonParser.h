#pragma once
#include <iostream>


namespace will
{
	class JsonParser
	{
	public:
		enum class DataToken
		{
			TOKEN_NULL,
			TOKEN_FALSE,
			TOKEN_TRUE,
			TOKEN_NUMBER,
			TOKEN_STRING,
			TOKEN_ARRAY,
			TOKEN_OBJECT
		};

		struct TokenValue
		{
			double number;
			DataToken type;
		};

		struct JsonContext
		{
			std::string json;
		};

		enum
		{
			TOKEN_PARSE_OK = 0,
			TOKEN_PARSE_EXCEPT_VALUE,
			TOKEN_PARSE_INVALID_VALUE,
			TOKEN_PARSE_ROOT_NOT_SINGULAR
		};
		
		~JsonParser();

		int TokenParser(TokenValue* value, const std::string& json);
		DataToken GetType(const TokenValue* value);
		void TokenParseWhiteSpace(JsonContext* context);
		int TokenParseValue(JsonContext* context, TokenValue* value);
		int TokenParseNULL(JsonContext* context, TokenValue* value);
		int TokenParseTRUE(JsonContext* context, TokenValue* value);
		int TokenParseFALSE(JsonContext* context, TokenValue* value);
		int TokenParseNumber(JsonContext* context, TokenValue* value);
		int TokenParseLiteral(JsonContext* context, TokenValue* value, const char* literal, DataToken type);
		
		double TokenGetNumber(const TokenValue* value);



		static JsonParser s_Instance;
		static JsonParser& Get();
	private:
		TokenValue m_DataToken;
		JsonParser();
	};
}