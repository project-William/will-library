#include <iostream>
#include "include/tiny_string.h"
#include "include/tiny_unique_ptr.h"

#include <utility>

using namespace tinystl;


struct H
{
	int a, b;
};


#include <string>

int main()
{
	
	String string("helloword");
	
	for (auto iter : string)
	{
		std::cout << iter << std::endl;
	}


	std::cout << string << std::endl;

	return 0;
}