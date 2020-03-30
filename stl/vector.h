#pragma once
#include "allocator.h"

namespace will
{
	template<class T, typename allocate = Allocator<T>>
	class Vector
	{
	public:
		using reference = T&;
		using pointer = T*;
		using value_type = T;
		using iterator = pointer;
		using const_iterator = const pointer;
		Vector() :m_Size(0), m_Capacity(1) { m_ValPtr = m_Alloc.allocate(1); }
		Vector(size_t n, value_type value);
		~Vector()noexcept;

		Vector(const Vector& other);
		Vector& operator=(const Vector& other);

		//get item from vector by index 
		reference operator[](size_t index);

		//get item from n position
		reference at(size_t position);

		//get first item reference from vector
		reference front();

		//get last item reference from vector
		reference back();

		//get size of the vector
		size_t size()const { return m_Size; }

		//get capacity of vector
		size_t capacity()const { return m_Capacity; }

		//add item from back
		void push_back(const value_type& value);

		//pop item from back
		void pop_back();

		//clear all items in vector but still hold same memory
		void clear();

		//assign new contents to vector at specific position 
		void assign(size_t position, const value_type& value); //single

		//allocate memory which can hold n items 
		void reserve(size_t n);

		//shrink capacity to fit the size
		void shrink_to_fit();

		//is vector empty or not
		bool empty()const { return m_Size == 0; }

		//get the pointer of the first item of vector
		iterator begin() { return m_ValPtr; }

		//get the pointer after the last item
		iterator end() { return &m_ValPtr[m_Size]; }

		//get the pointer of the first item of vector and cannot change the value
		const_iterator cbegin()const { return m_ValPtr; }

		//get the pointer after last item and cannot change the value
		const_iterator cend() const { return &m_ValPtr[m_Size]; }

		//get last item value
		value_type getLastValue()const { return m_ValPtr[m_Size - 1]; }

	private:
		//pointer of the first item
		pointer m_ValPtr;
		//record the size of vector
		size_t m_Size;
		//record the capacity of vector
		size_t m_Capacity;
		//allocator of vector
		allocate m_Alloc;
	};

	template<class T, typename allocate>
	Vector<T, allocate>::Vector(size_t n, Vector::value_type value)
		:m_Size(n), m_Capacity(n), m_ValPtr(m_Alloc.allocate(0))
	{
		//allocate memory which can hold n-size of items
		m_ValPtr = m_Alloc.allocate(m_Size);
		//assign the same value to all
		for (size_t i = 0; i < m_Size; i++)
		{
			m_ValPtr[i] = value;
		}
	}

	template<class T, typename allocate>
	Vector<T, allocate>::~Vector()
	{
		//free memory allocated by allocator
		m_Alloc.deallocate(m_ValPtr);
	}

	template<class T, typename allocate>
	Vector<T, allocate>::Vector(const Vector& other)
	{
		//free memory of allocator then reallocate new memory to hold items from another vector
		m_Alloc.deallocate(m_ValPtr);
		m_Size = other.size();
		m_Capacity = other.capacity();
		m_ValPtr = m_Alloc.allocate(m_Capacity);
		//copy items' value from another vector
		for (size_t i = 0; i < m_Size; i++)
		{
			m_ValPtr[i] = other.m_ValPtr[i];
		}
	}

	template<class T, typename allocate>
	Vector<T, allocate>& Vector<T, allocate>::operator=(const Vector& other)
	{
		//same operation like vector(other)
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

	template<class T, typename allocate>
	Vector<T, allocate>::reference Vector<T, allocate>::operator[](size_t index)
	{
		assert(index < m_Size);
		return m_ValPtr[index];
	}

	template<class T, typename allocate>
	T& Vector<T, allocate>::at(size_t position)
	{
		assert(position < m_Size);
		return m_ValPtr[position];
	}


	template<class T, typename allocate>
	void Vector<T, allocate>::push_back(const Vector::value_type& value)
	{
		//if capacity is smaller or same as m_size
		//allocate double size memory compared to pre-memory 
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

	template<class T, typename allocate>
	void Vector<T, allocate>::pop_back()
	{
		//set last value as null,size decreased by 1
		m_ValPtr[m_Size - 1] = NULL;
		m_Size--;
	}

	template<class T, typename allocate>
	void Vector<T, allocate>::clear()
	{
		//reset all item addresses to null but still have memory
		m_Alloc.deallcoate(m_ValPtr);
		m_ValPtr = m_Alloc.allocate(capacity);
		m_Size = 0;
	}

	template<class T, typename allocate>
	void Vector<T, allocate>::assign(size_t position, const Vector::value_type& value)
	{
		assert(position >= m_Capacity);
		m_ValPtr[position - 1] = value;
		if (position >= m_Size && position <= m_Capacity)
		{
			m_Size++;
		}
	}

	template<class T, typename allocate>
	Vector<T, allocate>::reference Vector<T, allocate>::front()
	{
		assert(m_Size == 0);
		return m_ValPtr[0];
	}

	template<class T, typename allocate>
	Vector<T, allocate>::reference Vector<T, allocate>::back()
	{
		assert(m_Size == 0);
		return m_ValPtr[m_Size - 1];


		template<class T, typename allocate>
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

		template<class T, typename allocate>
		void Vector<T, allocate>::shrink_to_fit()
		{
			//make capacity to fit size
			m_Capacity = m_Size;
		}

	}
}
