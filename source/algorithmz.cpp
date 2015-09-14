/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#include "algorithmz.h"

namespace nostl
{

	void test()
	{
		int data[5] = {0, 1, 2, 3, 4};
		int search_array[2] = {0, 4};
		const int const_search_array[2] = {0, 4};

		range<int> data_range(data, 5);
		range<const int> const_data_range= data_range;

		range<int> search_range(data, 2);
		range<const int> const_search_range(data, 2);
		
		find_first_of(data_range, 2);
		find_first_of(data_range, search_range);
		find_first_of(data_range, const_search_range);
		find_first_of(data_range, search_array);
		find_first_of(data_range, const_search_array);

		find_first_of(const_data_range, 2);
		find_first_of(const_data_range, search_range);
		find_first_of(const_data_range, const_search_range);
		find_first_of(const_data_range, search_array);
		find_first_of(const_data_range, const_search_array);


		find_last_of(data_range, 2);
		find_last_of(data_range, search_range);
		find_last_of(data_range, const_search_range);
		find_last_of(data_range, search_array);
		find_last_of(data_range, const_search_array);

		find_last_of(const_data_range, 2);
		find_last_of(const_data_range, search_range);
		find_last_of(const_data_range, const_search_range);
		find_last_of(const_data_range, search_array);
		find_last_of(const_data_range, const_search_array);

		
		// range algorithms
		
	}
}