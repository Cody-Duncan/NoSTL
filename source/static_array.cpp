/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/


#include "static_array.h"
#include <vector>

namespace z
{
	void test()
	{
		static_array<int, 20> arr;
		z::range<int> r = arr.get_range();

		std::vector<int> v;
		z::range<int, std::vector<int>::iterator> r2= make_range<int>(v.begin(), v.size());
	}
}