#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "nostl\static_array.h"
#include "nostl\static_vector.h"
#include "nostl\static_string.h"
#include "nostl\static_map.h"
#include "static_map_perf_test.h"

#define zero_struct(a) //memset(&a, 0, sizeof(a));


int main(int argc, char* argv[])
{
	std::cout << "beginning test" << std::endl;

	//nostl::test::test_static_array();
	//nostl::test::test_static_vector();
	//nostl::test::test_static_string();
	//nostl::test::test_static_map();

	run_tests();
	
	char i[128];
	std::cin >> i;
}