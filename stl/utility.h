#pragma once

namespace will::tinySTL
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

	


	

}