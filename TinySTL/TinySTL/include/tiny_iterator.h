#pragma once


namespace tinystl
{
	template<class T>
	class DefaultIterator
	{
	public:
		DefaultIterator(T* ptemp = nullptr)noexcept
			:m_Iterator(ptemp)
		{
		}

		DefaultIterator(const DefaultIterator& other) 
			:m_Iterator(other.m_Iterator)
		{
		}

		DefaultIterator& operator=(const DefaultIterator& other)
		{
			m_Iterator = other.m_Iterator;
			return *this;
		}

		DefaultIterator& operator++();
		DefaultIterator& operator+(size_t pos);
		DefaultIterator& operator--();
		DefaultIterator& operator-(size_t pos);

		bool operator==(const DefaultIterator& other)const
		{
			return m_Iterator == other.m_Iterator;
		}
		bool operator!=(const DefaultIterator& other)const
		{
			return m_Iterator != other.m_Iterator;
		}

		T& operator*() const
		{
			return *m_Iterator;
		}

		T* operator->()const
		{
			return &*m_Iterator;
		}

		~DefaultIterator() noexcept {};

	private:
		T* m_Iterator;
	};

	template<class T>
	DefaultIterator<T>& DefaultIterator<T>::operator++()
	{
		m_Iterator++;
		return *this;
	}

	template<class T>
	DefaultIterator<T>& DefaultIterator<T>::operator+(size_t pos)
	{
		m_Iterator += pos;
		return *this;
	}

	template<class T>
	DefaultIterator<T>& DefaultIterator<T>::operator--()
	{
		m_Iterator--;
		return *this;
	}

	template<class T>
	DefaultIterator<T>& DefaultIterator<T>::operator-(size_t pos)
	{
		m_Iterator -= pos;
		return *this;
	}


}