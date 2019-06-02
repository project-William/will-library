#include <iostream>
#include "include/tiny_string.h"

#include <utility>

using namespace tinystl;
std::ostream& operator<<(std::ostream& os, const string& ins) {
	os << ins.getBuffer();
	return os;
}

int main()
{
	string ss = "sdfsdf";
	string s(std::move(ss));

	std::cout << s << std::endl;
	return 0;
}