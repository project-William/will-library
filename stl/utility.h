#pragma once

namespace will
{
	/*swap*/
	template<typename T>
	void swap(T& first, T& second)
	{
		T temp = first;
		first = second;
		second = temp;
	}


	/*pair structure*/
	template<typename T, typename U>
	struct Pair
	{
		Pair();
		template<typename T1,typename U1>
		Pair(const Pair<T1, U1>& pair);
		Pair<T,U>& operator=(const Pair& pr);
		Pair(const T& fir, const U& seco);
		~Pair();

		T first;
		U second;
		
		//operator functions
		template<typename T, typename U>
		friend bool operator==(const Pair<T, U>& p1, const Pair<T, U>& p2);

		template<typename T,typename U>
		friend bool operator!=(const Pair<T, U>& p1, const Pair<T, U>& p2);

		template<typename T,typename U>
		friend bool operator<(const Pair<T, U>& p1, const Pair<T, U>& p2);
		
		template<typename T,typename U>
		friend bool operator<=(const Pair<T, U>& p1, const Pair<T, U>& p2);

		template<typename T,typename U>
		friend bool operator>(const Pair<T, U>& p1, const Pair<T, U>& p2);

		template<typename T,typename U>
		friend bool operator>=(const Pair<T, U>& p1, const Pair<T, U>& p2);

		template<typename T,typename U>
		friend void swap(Pair<T, U>& p1, Pair<T, U>& p2);


	};


	template<typename T, typename U>
	Pair<T, U>::Pair()
	{
	}

	template<typename T, typename U>
	Pair<T, U>::Pair(const T& fir, const U& sec)
		:first(fir),second(sec)
	{
	}

	template<typename T, typename U>
	template<typename T1,typename U1>
	Pair<T, U>::Pair(const Pair<T1, U1>& pair)
		:first(pair.first),second(pair.second)
	{
	}

	template<typename T,typename U>
	Pair<T, U>& Pair<T, U>::operator=(const Pair<T, U>& pr)
	{
		if (this != &pr)
		{
			first = pr.first;
			second = pr.second;
		}
		return *this;
	}

	template<typename T, typename U>
	Pair<T, U>::~Pair()
	{
	}

	template<typename T, typename U>
	bool operator==(const Pair<T, U>& p1, const Pair<T, U>& p2)
	{
		return p1 == p2;
	}

	template<typename T, typename U>
	bool operator!=(const Pair<T, U>& p1, const Pair<T, U>& p2)
	{
		return p1 != p2;
	}

	template<typename T, typename U>
	bool operator<(const Pair<T, U>& p1, const Pair<T, U>& p2)
	{
		return p1 < p2;
	}

	template<typename T, typename U>
	bool operator<=(const Pair<T, U>& p1, const Pair<T, U>& p2)
	{
		return p1 <= p2;
	}

	template<typename T, typename U>
	bool operator>(const Pair<T, U>& p1, const Pair<T, U>& p2)
	{
		return p1 > p2;
	}

	template<typename T, typename U>
	bool operator>=(const Pair<T, U>& p1, const Pair<T, U>& p2)
	{
		return p1 >= p2;
	}

	template<typename T, typename U>
	void swap(Pair<T, U>& p1, Pair<T, U>& p2)
	{
		will::swap(p1, p2);
	}


	template<typename T, typename U>
	Pair<T, U> make_pair(const T& first, const U& second)
	{
		return Pair<T, U>(first, second);
	}

	//binary functions less() equal_to()
	template<class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_arg_type;
		typedef Arg2 second_arg_type;
		typedef Result result_type;
	};

	template<class T>
	struct less :public binary_function<T, T, bool>
	{
		result_type operator()(const first_arg_type& first, const second_arg_type& second)
		{
			return first < second;
		}
	};

	template<class T>
	struct equal_to :public binary_function<T, T, bool>
	{
		result_type operator()(const first_arg_type& first, const second_arg_type& second)
		{
			return first == second;
		}
	};


	//hash function
	//for general
	template<class Key>
	struct Hash {};

	//template partial specialization for pointer
	template<class T>
	struct Hash<T*>
	{
		size_t operator()(T* ptr) const noexcept
		{
			return reinterpret_cast<size_t>(ptr);
		}
	};

#define HASH_FUN(type) \
template<>			   \
struct Hash<type>      \
{                      \
	size_t operator()(type value) const noexcept\
	{                  \
        return static_cast<size_t>(value);\
	}                  \
};                     \
	 

HASH_FUN(bool)

HASH_FUN(char)

HASH_FUN(signed char)

HASH_FUN(unsigned char)

HASH_FUN(short)

HASH_FUN(unsigned short)

HASH_FUN(float)

HASH_FUN(int)

HASH_FUN(unsigned int)

HASH_FUN(long)

HASH_FUN(unsigned long)

HASH_FUN(long long)	

HASH_FUN(unsigned long long)

}