#pragma once

namespace will::tinySTL
{
	template<class T,size_t N>
	class Array
	{
	public:

		using iterator = T*;
		using const_iterator = const T*;

		iterator begin() const { return iterator(&m_Buffer[0]; }
		const_iterator cbegin() const { return const_iterator(&m_Buffer[0]); }

		iterator end() const { return iterator(&m_Buffer[N -1]; }
		const_iterator cend() const { return const_iterator(&m_Buffer[N -1]; }

		T& operator[](size_t index)const { return *&m_Buffer[N - 1]; }

	private:
		T m_Buffer[N ? N : 1];
	};




}