#pragma once

namespace will::tinySTL
{
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
}