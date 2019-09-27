#pragma once
#include <iostream>


namespace tinystl {

	class String {
	private:
		char* m_Buffer;
		size_t m_Size;
	public:
		String();
		String(const char* other);
		String(const String& other);
		String(String&& other) noexcept;

		String& operator=(const String& other);
		String& operator=(String&& other) noexcept;
		String& operator=(const char* other);

		char& operator[](unsigned int index);

		inline char* getBuffer()const { return m_Buffer; }
		~String();
	};


	String::String()
		:m_Buffer(NULL), m_Size(0)
	{}

	String::~String() {
		delete[] m_Buffer;
	}

	String::String(const char* other) {
		m_Buffer = nullptr;
		m_Size = 0;
		m_Size = strlen(other);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other, m_Size + 1);
	}

	String::String(const String& other) {
		delete[] m_Buffer;
		m_Size = 0;
		m_Size = other.m_Size;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	String::String(String&& other) noexcept
		:m_Buffer(other.m_Buffer), m_Size(other.m_Size)
	{
		other.m_Size = 0;
		other.m_Buffer = nullptr;
	}

	String& String::operator=(const String& other) {
		delete[] m_Buffer;
		m_Size = 0;
		m_Size = other.m_Size;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		return *this;
	}

	String& String::operator=(String&& other) noexcept {
		m_Size = other.m_Size;
		other.m_Size = 0;
		m_Buffer = other.m_Buffer;
		other.m_Buffer = nullptr;
		return *this;
	}

	String& String::operator=(const char* other) {
		delete[] m_Buffer;
		m_Size = 0;
		m_Size = strlen(other);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other, m_Size + 1);
		return *this;
	}

	char& String::operator[](unsigned int index) {
		return m_Buffer[index];
	}

}

