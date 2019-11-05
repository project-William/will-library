#pragma once
#include "tiny_allocator.h"		
#include "tiny_iterator.h"

namespace tinystl {

	template<class T, size_t N, typename allocate = Allocator<T>>
	class Array
	{
	public:
		using iterator = DefaultIterator<T>;
		using const_iterator = DefaultIterator<const T>;
		Array() noexcept;
		~Array() noexcept;
		
		Array(const Array& other);
		Array& operator=(const Array& other);
		T& operator[](size_t index);


		iterator begin() { return m_Buffer; }
		iterator end() { return &m_Buffer[m_Size]; }
		
		const_iterator cbegin()const { return m_Buffer; }
		const_iterator cend()const { return &m_Buffer[m_Size]; }


	private:
		T* m_Buffer;
		size_t m_Size;
		allocate m_Alloc;
	};

	template<class T, size_t N, typename allocate>
	Array<T, N, allocate>::Array() noexcept
		:m_Buffer(m_Alloc.allocate(N)),m_Size(N)
	{
		for (size_t i = 0; i < N; i++)
		{
			m_Buffer[i] = NULL;
		}
	}

	template<class T,size_t N,typename allocate>
	Array<T, N, allocate>::~Array()noexcept
	{
		m_Alloc.deallocate(m_Buffer);
	}


	template<class T,size_t N,typename allocate>
	Array<T, N, allocate>::Array(const Array& other)
	{
		m_Alloc.deallocate(m_Buffer);
		m_Size = other.m_Size;
		m_Buffer = allocate.allocate(m_Size);
		memcpy(m_Buffer, other.m_Buffer, m_Size);
	}

	template<class T,size_t N,typename allocate>
	Array<T, N, allocate>& Array<T, N, allocate>::operator=(const Array& other)
	{
		m_Alloc.deallocate(m_Buffer);
		m_Size = other.m_Size;
		m_Buffer = allocate.allocate(m_Size);
		memcpy(m_Buffer, other.m_Buffer, m_Size);
	}

	template<class T,size_t N,typename allocate>
	T& Array<T, N, allocate>::operator[](size_t index)
	{
		assert(index <= m_Size);
		return m_Buffer[index];
	}



}