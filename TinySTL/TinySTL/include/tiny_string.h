#pragma once
#include <iostream>
#include "tiny_allocator.h"
#include "tiny_iterator.h"

namespace tinystl {


	class String {
	private:
		Allocator<char> m_Allocator;
		char* m_Buffer;
		size_t m_Size;
		
	public:
		using iterator = DefaultIterator<char>;
		using const_iterator = DefaultIterator<const char>;

		String();
		String(const char* other);
		String(const String& other);
		String(String&& other) noexcept;

		String& operator=(const String& other);
		String& operator=(const char* other);
		String& operator=(String&& other) noexcept;
		
		char& operator[](unsigned int index);

		inline char* getBuffer()const { return m_Buffer; }
		inline size_t size()const { return m_Size; }

		iterator begin()
		{
			return m_Buffer;
		}

		iterator end()
		{
			return &m_Buffer[m_Size];
		}

		const_iterator cbegin() const
		{
			return m_Buffer;
		}

		const_iterator cend() const
		{
			return &m_Buffer[0];
		}

		~String();

		friend std::ostream& operator<<(std::ostream& os, const String& other);
		
	};


	String::String()
		:m_Buffer(m_Allocator.allocate(0)), m_Size(0)
	{
	}

	String::~String() {
		m_Allocator.deallocate(m_Buffer);
	}

	String::String(const char* other) 
	{
		m_Size = strlen(other);
		m_Buffer = m_Allocator.allocate(m_Size + 1);
		memcpy(m_Buffer, other, m_Size + 1);
	}

	String::String(const String& other) {
		m_Allocator.deallocate(m_Buffer);
		m_Size = other.m_Size;
		m_Buffer = m_Allocator.allocate(m_Size + 1);
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	String::String(String&& other) noexcept
	{
		m_Buffer = other.getBuffer();
	}

	String& String::operator=(const String& other) {
		m_Allocator.deallocate(m_Buffer);
		m_Size = other.m_Size;
		m_Buffer = m_Allocator.allocate(m_Size + 1);
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		return *this;
	}

	String& String::operator=(const char* other) {
		m_Allocator.deallocate(m_Buffer);
		m_Size = strlen(other);
		m_Buffer = m_Allocator.allocate(m_Size + 1);
		memcpy(m_Buffer, other, m_Size + 1);
		return *this;
	}

	String& String::operator=(String&& other) noexcept
	{
		m_Buffer = other.getBuffer();
		return *this;
	}

	char& String::operator[](unsigned int index) {
		return m_Buffer[index];
	}

	std::ostream& operator<<(std::ostream& os, const String& other)
	{
		os << other.getBuffer();
		return os;
	}
}

