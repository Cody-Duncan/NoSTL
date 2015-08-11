#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "z_standard\static_array.h"

#define zero_struct(a) //memset(&a, 0, sizeof(a));

int main(int argc, char* argv[])
{
	z::test::test_static_array();
}