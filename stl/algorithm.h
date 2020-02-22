#pragma once

namespace will
{
	template<class T>
	inline const T& min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<class T>
	inline const T& max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<class T,class Compare>
	inline const T& min(const T& a, const T& b, Compare comp)
	{
		return comp(a, b) ? a : b;
	}

	template<class T,class Compare>
	inline const T& max(const T& a, const T& b, Compare comp)
	{
		return comp(a, b) ? a : b;
	}

}