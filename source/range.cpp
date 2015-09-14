/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#include "range.h"
#include "range_algorithms.h"

namespace nostl
{
	void test_range_find()
	{
		char data[12] = "hello world";
		const char const_data[12] = "hello world";
		range<char> test = make_range(data, 12);
		range<const char> const_test = make_range(data, 12);

		range<char> search_range(&data[2], 2);
		range<const char> const_search_range(&data[2], 2);

		// non-const

		range<char> result0 = test.find_first_of('l');
		range<char> result1 =test.find_last_of('l');

		range<char> result2 =test.find_first_of(search_range);
		range<char> result3 =test.find_last_of(const_search_range);

		range<char> result4 =test.find_first_of("lo");
		range<char> result5 =test.find_last_of("lo");


		// const
		range<const char> const_result0 =const_test.find_first_of('l');
		range<const char> const_result1 =const_test.find_last_of('l');

		range<const char> const_result2 =const_test.find_first_of(search_range);
		range<const char> const_result3 =const_test.find_last_of(const_search_range);

		range<const char> const_result4 =const_test.find_first_of("lo");
		range<const char> const_result5 =const_test.find_last_of("lo");

	}
}