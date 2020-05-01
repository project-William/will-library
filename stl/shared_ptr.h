#pragma once
#include "allocator.h"

namespace will::tinySTL
{
	template<class T,typename allocator=Allocator<T>>
	class Shared_ptr
	{
	public:
		using pointer = T*;
		using reference = T&;
		using type_value = T;
		Shared_ptr():m_Ptr(nullptr),m_RefCount(nullptr) {}
		Shared_ptr(pointer ptr):m_Ptr(ptr),m_RefCount(new int(1)) {}
		Shared_ptr(Shared_ptr& other);
		Shared_ptr& operator=(Shared_ptr& other);
		
		pointer operator*();
		type_value operator->();
		
		void reset(Shared_ptr<T, allocator>::pointer ptr);
		size_t useCount()const { return *m_RefCount; }
	private:
		pointer m_Ptr;
		size_t* m_RefCount;
		allocator m_Alloc;
	};

	template<class T,typename allocator>
	Shared_ptr<T,allocator>::Shared_ptr(Shared_ptr<T,allocator>& other)
		:m_Ptr(other.m_Ptr),m_RefCount(--*other.m_RefCount)
	{

	}

	template<class T,typename allocator>
	Shared_ptr<T, allocator>& Shared_ptr<T, allocator>::operator=(Shared_ptr<T, allocator>& other)
	{
		if (&other == this)
			return *this;
		++* other.m_RefCount;
		if (*m_RefCount == 0)
		{
			m_Alloc.deallocate(m_Ptr);
			m_Alloc.deallocate(m_RefCount);
		}

		m_RefCount = other.m_RefCount;
		m_Ptr = other.m_Ptr;
		return *this;
	}

	template<class T,typename allocator>
	Shared_ptr<T, allocator>::pointer Shared_ptr<T, allocator>::operator*()
	{
		if (*m_RefCount == 0)
			return pointer(0);
		else return *m_Ptr;
	}

	template<class T,typename allocator>
	Shared_ptr<T, allocator>::type_value Shared_ptr<T, allocator>::operator->()
	{
		if (*m_RefCount == 0)
			return 0;
		return m_Ptr;
	}

	template<class T,typename allocator>
	void Shared_ptr<T, allocator>::reset(Shared_ptr<T,allocator>::pointer ptr)
	{
		if (m_Ptr)
		{
			m_Alloc.deallocate(m_Ptr);
			m_Alloc.deallocate(m_RefCount);
		}
		m_Ptr = ptr;
		*m_RefCount = new int(0);
	}


}