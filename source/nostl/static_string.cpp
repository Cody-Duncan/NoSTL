/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#include "nostl/static_string.h"
#include "nostl/unused.h"

namespace nostl
{
	namespace test_static_string
	{
		void test_constructor_destructor()
		{
			static const int data_size = 20;
			static_string<data_size> arr;
			breakpoint_nop();
		}

		void test_copy_constructor()
		{
			char helloarr[6] = "Hello";
			char* hellostr = helloarr;

			static_string<20> arr0("Hello");
			static_string<20> arr1("Hello", 6);
			static_string<20> arr2(hellostr);
			static_string<20> arr3(arr0);

			static_string<10> test("Goodbye");
			static_string<20> arr4(test);

			breakpoint_nop();
		}

		void test_size()
		{
			static_string<20> arr;
			breakpoint_nop();

			static_string<20> arr1("WHAT");
			breakpoint_nop();

			static_string<20> arr2("0123456789123456789");
			breakpoint_nop();
		}

		void test_deep_copy()
		{
			static const int data_size = 20;
			char data[20] = "Can you do it. no?!";

			static_string<20> arr(data);
			static_string<20> result;
			result.deep_copy(arr);
			breakpoint_nop();

			////////////////////////////
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = 'a';
			}
			data[19] = '\0';

			result.deep_copy(data, 19);
			breakpoint_nop();

			////////////////////////////
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = 'z' - i;
			}
			data[19] = '\0';

			result.deep_copy(data);
			breakpoint_nop();
		}

		void test_clear()
		{
			static const int data_size = 20;
			char data[20] = "Can you do it. no?";

			static_string<20> arr(data, data_size-1);
			arr.clear();
			breakpoint_nop();

			static_string<20> arr2(data, data_size-1);
			arr2.clear_zero();
			breakpoint_nop();
		}

		void test_get()
		{
			static const int data_size = 20;
			char data[20] = "Can you do it. no?!";

			static_string<data_size> arr(data);
			char val = -1;
			for(int i = 0; i < data_size-1; ++i)
			{
				val = arr.get(i);
				breakpoint_nop();
			}
		}

		void test_begin_end()
		{
			char data[20] = "Can you do it. no?!";

			static_string<20> arr(data);
			char* first = arr.begin();
			char* last = arr.end();
			unused(first);
			unused(last);
			breakpoint_nop();
		}

		void test_get_range()
		{
			static const int data_size = 20;
			char data[20] = "Can you do it. no?!";

			static_string<20> arr(data);

			range<char*> test_range_base = arr.get_range();
			range<char*> test_range_index = arr.get_range(data_size / 2);
			range<char*> test_range_two_index = arr.get_range(1, data_size - 1);
			unused(test_range_base);
			unused(test_range_index);
			unused(test_range_two_index);
			breakpoint_nop();
		}

		void test_internal_array()
		{
			char data[20] = "Can you do it. no?!";

			static_string<20> arr(data);
			char* ptr = arr.internal_array();
			unused(ptr);
			breakpoint_nop();
		}

		void test_find()
		{
			char data[20] = "ABCDEFGHIJIHGFEDCBA";

			static_string<20> arr(data);
			range<char*> test_range_front = arr.find_char('D');
			range<char*> test_range_back = arr.find_char_reverse('D');
			range<char*> test_range_two_index = arr.find("FGH");
			unused(test_range_front);
			unused(test_range_back);
			unused(test_range_two_index);

			const static_string<20> arr2(data);
			range<const char*> test_range_front_const = arr2.find_char('D');
			range<const char*> test_range_back_const = arr2.find_char_reverse('D');
			range<const char*> test_range_two_index_const = arr2.find("FGH");
			unused(test_range_front_const);
			unused(test_range_back_const);
			unused(test_range_two_index_const);

			static_string<4> arr_find("FGH");
			range<char*> test_range3_two_index = arr.find(arr_find);
			unused(test_range3_two_index);
			
			static_string<20> arr3(data);
			range<char*> test_range4_find_reverse = arr3.find_reverse("FED");
			unused(test_range4_find_reverse);

			breakpoint_nop();
		}

		void test_starts_ends_contains()
		{
			char data[20] = "ABCDEFGHIJIHGFEDCBA";

			static_string<20> arr(data);
			bool starts = arr.starts_with("ABCD");
			bool ends = arr.ends_with("DCBA");
			bool contains = arr.contains("HIJIH");
			unused(starts);
			unused(ends);
			unused(contains);

			bool not_starts = arr.starts_with("DCBA");
			bool not_ends = arr.ends_with("ABCD");
			bool not_contains = arr.contains("HIZJIH");
			unused(not_starts);
			unused(not_ends);
			unused(not_contains);

			breakpoint_nop();
		}

		void test_range_copy()
		{
			char data[20] = "ABCDEFGHIJIHGFEDCBA";

			range<char*>r= make_range_from_array(data);
			static_string<20> arr(r);

			breakpoint_nop();
		}
	}

	namespace test
	{
		void test_static_string()
		{
			using namespace test_static_string;
			test_constructor_destructor();
			test_copy_constructor();
			test_size();
			test_deep_copy();
			test_clear();
			test_get();
			test_begin_end();
			test_get_range();
			test_internal_array();
			test_find();
			test_starts_ends_contains();
			test_range_copy();
		}
	}
}