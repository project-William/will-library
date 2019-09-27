#pragma once

namespace tinystl
{
	template<class T>
	struct PtrDeleter
	{
		void operator()(T* ptr)
		{
			if (ptr)
			{
				delete ptr;
				ptr = nullptr;
			}
		}
	};


	template<class T, typename Deleter=PtrDeleter<T>>
	class Unique_ptr
	{
	public:
		Unique_ptr(T* ptr);
		~Unique_ptr();
	private:
		Unique_ptr(const Unique_ptr<T>&) = delete;
		Unique_ptr& operator=(const Unique_ptr<T>&) = delete;

	private:
		T* m_Ptr;
		Deleter m_Deleter;
		void Delete();
	public:
		void Reset(T* ptr);
		T* GetPtr();
		T& operator*();
		T* operator->();
	};


	template<class T,typename Deleter>
	Unique_ptr<T, Deleter>::Unique_ptr(T* ptr)
		:m_Ptr(ptr)
	{
	}

	template<class T,typename Deleter>
	Unique_ptr<T, Deleter>::~Unique_ptr()
	{
		Delete();
	}

	template<class T, typename Deleter>
	void Unique_ptr<T, Deleter>::Delete()
	{
		m_Deleter(m_Ptr);
		m_Ptr = nullptr;
	}


	template<class T,typename Deleter>
	T* Unique_ptr<T, Deleter>::GetPtr()
	{
		return m_Ptr;
	}

	template<class T,typename Deleter>
	void Unique_ptr<T, Deleter>::Reset(T* ptr)
	{
		Delete();
		m_Ptr = ptr;
	}

	template<class T,typename Deleter>
	T* Unique_ptr<T, Deleter>::operator->()
	{
		return m_Ptr;
	}

	template<class T,typename Deleter>
	T& Unique_ptr<T, Deleter>::operator*()
	{
		assert(*this);
		return *m_Ptr;
	}


}