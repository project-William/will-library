#pragma once
#include "allocator.h"


namespace will::tinySTL
{
	template<class T, typename allocator=Allocator<T>>
	class Unique_ptr
	{
	public:
		using reference = T&;
		using pointer = T*;
		using type_value = T;
		Unique_ptr() {}
		Unique_ptr(pointer ptr);
		Unique_ptr(const Unique_ptr<T>&) = delete;
		Unique_ptr& operator=(const Unique_ptr<T>&) = delete;
		~Unique_ptr();

		reference operator*();
		pointer operator->();

		pointer get();
		void reset(pointer ptr);

	private:
		pointer m_Data;
		allocator m_Alloc;
	};

	template<class T, typename allocator>
	Unique_ptr<T, allocator>::Unique_ptr(Unique_ptr::pointer ptr)
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
	Unique_ptr<T,allocator>::reference Unique_ptr<T, allocator>::operator*()
	{
		if (m_Data)
		{
			return *m_Data;
		}
		else throw std::exception("null pointer");
	}


	template<class T,typename allocator>
	Unique_ptr<T, allocator>::pointer Unique_ptr<T, allocator>::operator->()
	{
		return &*(*this);
	}

	template<class T,typename allocator>
	Unique_ptr<T, allocator>::pointer Unique_ptr<T, allocator>::get()
	{
		return m_Data;
	}

	template<class T,typename allocator>
	void Unique_ptr<T, allocator>::reset(Unique_ptr::pointer ptr)
	{
		if(m_Data)
			m_Alloc.deallocate(ptr);
		m_Data = ptr;
	}


}