#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "z_standard\static_array.h"
#include "z_standard\static_vector.h"
#include "z_standard\static_string.h"

#define zero_struct(a) //memset(&a, 0, sizeof(a));


int main(int argc, char* argv[])
{
	z::static_array<int, 2> test;

	//z::test::test_static_array();
	z::test::test_static_vector();

	z::test::test_static_string();

	z::static_string<20> test_str("  ABCDEF");
}