#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "nostl\static_array.h"
#include "nostl\static_vector.h"
#include "nostl\static_string.h"

#define zero_struct(a) //memset(&a, 0, sizeof(a));


int main(int argc, char* argv[])
{
	nostl::static_array<int, 2> test;

	//z::test::test_static_array();
	nostl::test::test_static_vector();

	nostl::test::test_static_string();

	nostl::static_string<20> test_str("  ABCDEF");
}