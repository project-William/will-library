#include <iostream>
#include "include/tiny_string.h"
#include "include/tiny_unique_ptr.h"
#include "include/tiny_vector.h"
#include "include/tiny_array.h"
#include <utility>
#include <list>

using namespace tinystl;


struct H
{
	int a, b;
};


#include <string>
#include <array>


int main()
{
	std::list<H> list;
	H h = { 1,2 };
	H h1 = { 3,2 };
	H h2 = { 4,2 };
	H h3 = { 5,2 };
	list.push_back(h);
	list.push_back(h1);
	list.push_back(h2);
	list.push_back(h3);

	auto e = list.begin();
	e++;
	std::cout << e->a << std::endl;

	return 0;
}