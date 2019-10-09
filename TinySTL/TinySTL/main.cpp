#include <iostream>
#include "include/tiny_string.h"
#include "include/tiny_unique_ptr.h"

#include <utility>

using namespace tinystl;


struct H
{
	int a, b;
};

int main()
{
	
	String string("helloword");
	
	std::cout << string << std::endl;

	return 0;
}