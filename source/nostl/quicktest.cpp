/*
Author: Cody Duncan
Date: November 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

// ---------- includes ---------

#include "nostl/range.h"
#include <vector>

#include <iostream>

namespace nostl
{
	void test_test_my_stuff()
	{
		std::vector<int> vec;
		nostl::range<std::vector<int>::iterator> vi(vec.begin(), vec.end());
		vi.front();
		vi.back();
		int a = vi[1];
		(void)(a);
		
		std::cout << vi << std::endl;

		const nostl::range<std::vector<int>::iterator> vic(vec.begin(), vec.end());
		vic.front();
		vic.back();
		int b = vic[1];
		(void)(b);
		std::cout << vic << std::endl;
	}
}