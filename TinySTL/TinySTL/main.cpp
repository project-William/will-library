#include <iostream>
#include "include/tiny_string.h"
#include "include/tiny_unique_ptr.h"

#include <utility>

using namespace tinystl;
std::ostream& operator<<(std::ostream& os, const String& ins) {
	os << ins.getBuffer();
	return os;
}


struct H
{
	int a, b;
};

int main()
{
	Unique_ptr<H> number(new H());
	number->a = 11;
	number->b = 12;
	return 0;
}