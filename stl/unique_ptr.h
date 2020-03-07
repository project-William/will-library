#pragma once
#include "allocator.h"


namespace will 
{
	template<class T, typename allocator=Allocator<T>>
	class Unique_ptr
	{
	public:
		Unique_ptr() {}
		Unique_ptr(T* ptr);
		Unique_ptr(const Unique_ptr<T>&) = delete;
		Unique_ptr& operator=(const Unique_ptr<T>&) = delete;
		~Unique_ptr();

		T& operator*();
		T* operator->();

		T* get();
		void reset(T* ptr);

	private:
		T* m_Data;
		allocator m_Alloc;
	};

	template<class T, typename allocator>
	Unique_ptr<T, allocator>::Unique_ptr(T* ptr)
		:m_Data(ptr)
	{

	}

	template<class T, typename allocator>
	Unique_ptr<T, allocator>::~Unique_ptr()
	{
		if(this)
			m_Alloc.deallocate(m_Data);
		m_Data = nullptr;
	}

	template<class T,typename allocator>
	T& Unique_ptr<T, allocator>::operator*()
	{
		if (m_Data)
		{
			return *m_Data;
		}
		else throw std::exception("null pointer");
	}


	template<class T,typename allocator>
	T* Unique_ptr<T, allocator>::operator->()
	{
		return &*(*this);
	}

	template<class T,typename allocator>
	T* Unique_ptr<T, allocator>::get()
	{
		return m_Data;
	}

	template<class T,typename allocator>
	void Unique_ptr<T, allocator>::reset(T* ptr)
	{
		if(m_Data)
			m_Alloc.deallocate(ptr);
		m_Data = ptr;
	}


}