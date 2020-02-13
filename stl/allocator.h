#pragma once
#include <stdlib.h>
#include <assert.h>
#include <new>	
#include <memory>

namespace will
{
	template<class T>
	struct Allocator
	{
		typedef T value_type;
		typedef T* pointer;

		Allocator() noexcept = default;
		~Allocator() noexcept = default;

		template<class U>
		Allocator(const Allocator<U>&) noexcept {};

		template<class U>
		bool operator==(const Allocator<U>&) noexcept
		{
			return true;
		}

		template<class U>
		bool operator!=(const Allocator<U>&) noexcept
		{
			return false;
		}

		T* allocate(const size_t n) const;
		void deallocate(T* const p)const noexcept;

	};

	template<class T>
	T* Allocator<T>::allocate(const size_t n)const
	{
		if (n == 0)
		{
			return nullptr;
		}
		if (n > static_cast<size_t>(-1) / sizeof(T))
		{
			throw std::bad_array_new_length();
		}
		void* ptr = malloc(n * sizeof(T));
		if (!ptr)
		{
			throw std::bad_alloc();
		}

		return static_cast<T*>(ptr);
	}

	template<class T>
	void Allocator<T>::deallocate(T* p)const noexcept
	{
		free(p);
	}
}

