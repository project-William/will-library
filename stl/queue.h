#pragma once
#include "deque.h"

namespace will
{
	template<class T, class Sequence=Deque<T>>
	class Queue
	{
	public:

		void push(const T& ele) { return m_Container.push_back(ele); }
		void pop(const T& ele) { return m_Container.pop_front(ele); }

		bool empty()const { return m_Container.empty(); }

		size_t size()const { return m_Container.size(); }


	private:
		Sequence m_Container;
	};
}