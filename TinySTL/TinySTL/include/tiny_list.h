#pragma once
#include "tiny_allocator.h"
#include "tiny_iterator.h"

namespace tinystl
{
	template<class T>
	class Node
	{
	public:
		T m_Data;
		Node* m_NextPtr;
		Node* m_PrevPtr;
		Node(const T& data, Node* next, Node* prev)
			:m_Data(data),m_NextPtr(next),m_PrevPtr(prev)
		{ }
		bool operator==(const Node& n)
		{
			return m_Data == n.m_Data && m_NextPtr == n.m_NextPtr && m_PrevPtr == n.m_PrevPtr;
		}
	};


	template<class T, typename allocate=Allocator<T>>
	class List
	{
	public:

		using iterator = DefaultIterator<Node<T>>;
		using const_iterator = DefaultIterator<const Node<T>>;

		List();
		~List();

		void push_back(const Node* node);

		iterator begin();
		iterator end();
		const_iterator cbegin()const;
		const_iterator cend()const;

	private:
		Node* m_Head;
		Node* m_Tail;
		size_t m_Size;
		allocate m_Alloc;
	};

	template<class T,typename allocate>
	List<T, allocate>::List()
		:m_Head(nullptr), m_Tail(nullptr), m_Size(0)
	{
	}

	template<class T,typename allocate>
	List<T, allocate>::~List()
	{
	}

	template<class T,typename allocate>
	void List<T, allocate>::push_back(const Node<T>* node)
	{
		if (m_Head == nullptr)
		{
			m_Tail = m_Head = node;
		}
		else
		{
			m_Tail->m_NextPtr = node;
			m_Tail = node;
		}
	}


}