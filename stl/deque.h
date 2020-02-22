#pragma once
#include "allocator.h"
#include "vector.h"

namespace will
{

	template<class T>
	struct dequeIterator
	{
		using map_pointer = T**;
		T* cur;
		T* first;
		T* last;
		map_pointer node;
		
	};



	template<class T, typename valAlloc=Allocator<T>, typename ptrAlloc=Allocator<T*>>
	class Deque
	{
	public:
		Deque();
		~Deque();

		void push_back(const T& ele);
		void push_front(const T& ele);
		void pop_back();
		void pop_front();

		bool empty();

		using iterator = dequeIterator<T>;
		using const_iterator = dequeIterator<const T>;


		void mapSize()const { return m_MapSize; }
		size_t size()const { ; }
	private:

		T** m_Map;
		
		size_t m_MapSize;
		size_t m_BufferSize;
	};

	template<class T,typename valAlloc,typename ptrAlloc>
	Deque<T, valAlloc, ptrAlloc>::Deque()
		:m_Map(nullptr),m_MapSize(0),m_BufferSize(0)
	{

	}
	
	template<class T,typename valAlloc,typename ptrAlloc>
	Deque<T, valAlloc, ptrAlloc>::~Deque()
	{

	}

	template<class T, typename valAlloc, typename ptrAlloc>
	void Deque<T, valAlloc, ptrAlloc>::push_back(const T& ele)
	{
		if (m_BufferSize == 0)
		{
			m_Map = ptrAlloc.allocate(1);
		}
	}

	template<class T, typename valAlloc, typename ptrAlloc>
	void Deque<T, valAlloc, ptrAlloc>::push_front(const T& ele)
	{

	}

	template<class T, typename valAlloc, typename ptrAlloc>
	void Deque<T, valAlloc, ptrAlloc>::pop_back()
	{

	}

	template<class T, typename valAlloc, typename ptrAlloc>
	void Deque<T, valAlloc, ptrAlloc>::pop_front()
	{

	}

	template<class T, typename valAlloc, typename ptrAlloc>
	bool Deque<T, valAlloc, ptrAlloc>::empty()
	{
		return m_BufferSize == 0;
	}


}