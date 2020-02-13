#pragma once
#include "allocator.h"

namespace will
{
	
	template<class T>
	class ListNode
	{
	public:
		T m_Data;
		ListNode<T>* m_NextPtr;
		ListNode<T>* m_PrevPtr;
		ListNode(const T& data, ListNode<T>* next, ListNode<T>* prev)
			:m_Data(data), m_NextPtr(next), m_PrevPtr(prev)
		{ }
		bool operator==(const ListNode<T>& n)
		{
			return m_Data == n.m_Data && m_NextPtr == n.m_NextPtr && m_PrevPtr == n.m_PrevPtr;
		}
	};


	template<class T>
	class ListIterator
	{
	public:
		using Iterator= ListIterator<T>;

		ListIterator() :Ptr(nullptr) {}
		ListIterator(ListNode<T>* x) :Ptr(x) {}
		Iterator& operator++() {
			Ptr = Ptr->m_NextPtr;
			return *this;
		}
		Iterator operator++(int) {
			Iterator tmp = *this;
			++*this;
			return tmp;
		}
		Iterator& operator--() {
			Ptr = Ptr->m_PrevPtr;
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			--* this;
			return tmp;
		}
		Iterator& operator=(const Iterator& x) {
			Ptr = x.Ptr;
			return *this;
		}
		T operator*() {
			return Ptr->m_Data;
		}
		bool operator==(const Iterator& x) {
			return (Ptr == x.Ptr);
		}
		bool operator!=(const Iterator& x) {
			return (Ptr != x.Ptr);
		}
		ListNode<T>* Ptr;
	};


	template<class T, typename allocate = Allocator<ListNode<T>>>
	class List
	{
	public:

		using iterator = ListIterator<T>;
		using const_iterator = ListIterator<const T>;

		List();
		~List();

		void push_back(T elem);
		void push_front(T elem);
		void pop_back();
		void pop_front();


		iterator begin() { return m_Head; }
		iterator end() { return nullptr; }
		const_iterator cbegin()const { return m_Head; }
		const_iterator cend()const { return m_Tail->m_NextPtr; }

	

	private:
		ListNode<T>* m_Head;
		ListNode<T>* m_Tail;
		size_t m_Size;
		allocate m_Alloc;
	};

	template<class T, typename allocate>
	List<T, allocate>::List()
		:m_Head(nullptr), m_Tail(nullptr), m_Size(0)
	{
	}

	template<class T, typename allocate>
	List<T, allocate>::~List()
	{
	}

	template<class T, typename allocate>
	void List<T, allocate>::push_back(T elem)
	{

		if (m_Head == nullptr)
		{
			m_Head = m_Alloc.allocate(1);
			m_Head->m_Data = elem;
			m_Head->m_NextPtr = m_Head->m_PrevPtr =nullptr;
			m_Tail = m_Head;
		}
		else
		{
			ListNode<T>* newListNode = m_Alloc.allocate(1);
			m_Tail->m_NextPtr = newListNode;
			newListNode->m_Data = elem;
			newListNode->m_PrevPtr = m_Tail;
			m_Tail = newListNode;
			m_Tail->m_NextPtr = nullptr;
			m_Head->m_PrevPtr = nullptr;
		}
	}

	template<class T, typename allocate>
	void List<T, allocate>::push_front(T elem)
	{
		ListNode<T>* newListNode = m_Alloc.allocate(1);
		if (!m_Head)
		{
			newListNode->m_Data = elem;
			m_Head = newListNode;
			m_Tail = m_Head;
			m_Head->m_NextPtr = m_Tail->m_NextPtr = nullptr;
		}
		else
		{
			newListNode->m_Data = elem;
			newListNode->m_NextPtr = m_Head;
			m_Head->m_PrevPtr = newListNode;
			newListNode->m_PrevPtr = nullptr;
			m_Head = newListNode;
		}
	}

	template<class T, typename allocate>
	void List<T, allocate>::pop_back()
	{

	}
	template<class T, typename allocate>
	void List<T, allocate>::pop_front()
	{

	}


}