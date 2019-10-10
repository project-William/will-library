#pragma once
#include "tiny_allocator.h"
#include "tiny_iterator.h"

namespace tinystl
{
	template<class T,typename allocate = Allocator<T>>
	class Vector
	{
	public:
		using iterator = DefaultIterator<T>;
		using const_iterator = DefaultIterator<const T>;
		Vector():m_Size(0),m_Capacity(0),m_ValPtr(nullptr) {}
		Vector(size_t n, T value);
		~Vector()noexcept;

		Vector(const Vector& other);
		Vector& operator=(const Vector& other);
		T& operator[](size_t index);
		
		size_t size()const { return m_Size; }
		size_t capacity()const { return m_Capacity; }

		void push_back(T value);
		void pop_back();
		void reserve(size_t n);

		iterator begin() { return m_ValPtr; }
		iterator end() { return &m_ValPtr[m_Size]; }
		const_iterator cbegin()const { return m_ValPtr; }
		const_iterator cend() const { return &m_ValPtr[m_Size]; }

	private:
		T* m_ValPtr;
		size_t m_Size;
		size_t m_Capacity;
		allocate m_Alloc;
	};

	template<class T,typename allocate>
	Vector<T, allocate>::Vector(size_t n, T value)
		:m_Size(n),m_Capacity(n),m_ValPtr(m_Alloc.allocate(0))
	{
		m_ValPtr = m_Alloc.allocate(m_Size);
		for (size_t i = 0; i < m_Size; i++)
		{
			m_ValPtr[i] = value;
		}
	}

	template<class T,typename allocate>
	Vector<T, allocate>::~Vector()
	{
		m_Alloc.deallocate(m_ValPtr);
	}
	
	template<class T,typename allocate>
	Vector<T, allocate>::Vector(const Vector& other)
	{
		m_Alloc.deallocate(m_ValPtr);
		m_Size = other.size();
		m_Capacity = other.capacity();
		m_ValPtr = m_Alloc.allocate(m_Capacity);
		for (size_t i = 0; i < m_Size; i++)
		{
			m_ValPtr[i] = other.m_ValPtr[i];
		}
	}

	template<class T,typename allocate>
	Vector<T, allocate>& Vector<T, allocate>::operator=(const Vector& other)
	{
		m_Alloc.deallocate(m_ValPtr);
		m_Size = other.size();
		m_Capacity = other.capacity();
		m_ValPtr = m_Alloc.allocate(m_Capacity);
		for (size_t i = 0; i < m_Size; i++)
		{
			m_ValPtr[i] = other.m_ValPtr[i];
		}
		return *this;
	}

	template<class T,typename allocate>
	T& Vector<T, allocate>::operator[](size_t index)
	{
		assert(index < m_Size);
		return m_ValPtr[index];
	}


	template<class T, typename allocate>
	void Vector<T, allocate>::push_back(T value)
	{
		if (m_Size >= m_Capacity)
		{
			m_Capacity *= 2;
			T* ptemp = m_ValPtr;
			m_ValPtr = m_Alloc.allocate(m_Capacity);
			for (size_t i = 0; i < m_Size; i++)
			{
				m_ValPtr[i] = ptemp[i];
			}
			m_ValPtr[m_Size] = value;
			m_Alloc.deallocate(ptemp);
			m_Size++;
		}
		else
		{
			m_ValPtr[m_Size] = value;
			m_Size++;
		}
	}

	template<class T,typename allocate>
	void Vector<T, allocate>::pop_back()
	{
		m_ValPtr[m_Size] = NULL;
		m_Size--;
	}

	template<class T,typename allocate>
	void Vector<T, allocate>::reserve(size_t newcapacity)
	{
		assert(newcapacity >= m_Size);
		T* ptemp = m_ValPtr;
		m_ValPtr = m_Alloc.allocate(newcapacity);
		for (size_t i = 0; i < m_Size; i++)
		{
			m_ValPtr[i] = ptemp[i];
		}
		m_Alloc.deallocate(ptemp);
		m_Capacity = newcapacity;
	}

}