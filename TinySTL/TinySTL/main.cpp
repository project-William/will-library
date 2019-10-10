#include <iostream>
#include "include/tiny_string.h"
#include "include/tiny_unique_ptr.h"
#include "include/tiny_vector.h"
#include <utility>

using namespace tinystl;


struct H
{
	int a, b;
};


#include <string>

int main()
{
	

	std::string ss = "sdfsdf";

	Vector<int> vec(5, 2);
	for (auto iter : vec)
	{
		std::cout << iter << std::endl;
	}

	vec.reserve(31);
	
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;


	return 0;
}