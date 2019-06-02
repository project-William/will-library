#pragma once
#include <iostream>


namespace tinystl {

	class string {
	private:
		char* m_Buffer;
		unsigned int m_Size;
	public:
		string();
		string(const char* other);
		string(const string& other);
		string(string&& other) noexcept;

		string& operator=(const string& other);
		string& operator=(string&& other) noexcept;
		string& operator=(const char* other);

		char& operator[](unsigned int index);

		inline char* getBuffer()const { return m_Buffer; }
		~string();
	};


	string::string()
		:m_Buffer(NULL), m_Size(0)
	{}

	string::~string() {
		delete[] m_Buffer;
	}

	string::string(const char* other) {
		m_Buffer = nullptr;
		m_Size = 0;
		m_Size = strlen(other);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other, m_Size + 1);
	}

	string::string(const string& other) {
		delete[] m_Buffer;
		m_Size = 0;
		m_Size = other.m_Size;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	string::string(string&& other) noexcept
		:m_Buffer(other.m_Buffer), m_Size(other.m_Size)
	{
		other.m_Size = 0;
		other.m_Buffer = nullptr;
	}

	string& string::operator=(const string& other) {
		delete[] m_Buffer;
		m_Size = 0;
		m_Size = other.m_Size;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		return *this;
	}

	string& string::operator=(string&& other) noexcept {
		m_Size = other.m_Size;
		other.m_Size = 0;
		m_Buffer = other.m_Buffer;
		other.m_Buffer = nullptr;
		return *this;
	}

	string& string::operator=(const char* other) {
		delete[] m_Buffer;
		m_Size = 0;
		m_Size = strlen(other);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other, m_Size + 1);
		return *this;
	}

	char& string::operator[](unsigned int index) {
		return m_Buffer[index];
	}

}

