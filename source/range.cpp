/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#include "range.h"

namespace z
{
	void test_range_find()
	{
		char data[12] = "hello world";
		range<char> test = make_range(data, 12);

		test.find_first_of("lo");
		test.find_last_of("lo");
	}
}