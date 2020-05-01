#include <iostream>
#include "stl/vector.h"	
#include <memory>
#include <forward_list>
#include "jsonInterpreter/JsonTester.h"
using namespace will::tinySTL;
using namespace will;
#include <vector>



int main()
{
	testParse();
	
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
	return main_ret;

}