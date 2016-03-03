/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#include "nostl/static_vector.h"
#include "nostl/unused.h"

namespace nostl
{
	namespace test_static_vector
	{
		struct test_struct
		{
			int value;
			test_struct() : value(-1) {}
		};

		void test_constructor_destructor()
		{
			static const int data_size = 20;
			static_vector<int, data_size> arr;
			static_vector<test_struct, data_size> test_arr;
			breakpoint_nop();
		}

		void test_copy_constructor()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, 20);
			breakpoint_nop();
		}

		void test_move_constructor()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, 20);
			static_vector<int, 20> result(std::move(arr));
			breakpoint_nop();
		}

		void test_size()
		{
			static_vector<int, 20> arr;
			breakpoint_nop();
		}

		void test_deep_copy()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, 20);
			static_vector<int, 20> result;
			result.deep_copy(arr);
			breakpoint_nop();

			////////////////////////////
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = 2;
			}

			result.deep_copy(data, 20);
			breakpoint_nop();

			////////////////////////////
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = -i;
			}

			result.deep_copy(data);
			breakpoint_nop();
		}

		void test_reconstruct_element()
		{
			static_vector<int, 20> arr;
			arr.get(0) = 7;
			arr.reconstruct_element(0);
			breakpoint_nop();

			static_vector<test_struct, 20> test_arr;
			test_arr.get(0).value = 12;
			test_arr.reconstruct_element(0);
			breakpoint_nop();
		}

		void test_reconstruct_array()
		{
			static_vector<int, 20> arr;
			arr.get(0) = 7;
			arr.reconstruct_array();
			breakpoint_nop();

			static_vector<test_struct, 20> test_arr;
			test_arr.get(0).value = 12;
			test_arr.reconstruct_array();
			breakpoint_nop();
		}

		void test_zero_array()
		{
			static_vector<int, 20> arr;
			arr.get(0) = 7;
			arr.zero_array();
			breakpoint_nop();

			static_vector<test_struct, 20> test_arr;
			test_arr.get(0).value = 12;
			test_arr.zero_array();
			breakpoint_nop();
		}

		void test_get()
		{
			static const int data_size = 5;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, data_size> arr(data, data_size);
			int val = -1;
			for(int i = 0; i < data_size; ++i)
			{
				val = arr.get(i);
				breakpoint_nop();
			}
		}

		void test_first_last()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, data_size);
			int first = arr.first();
			int last = arr.last();
			unused(first);
			unused(last);
			breakpoint_nop();
		}

		void test_get_range()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, data_size);

			range<int*> test_range_base = arr.get_range();
			range<int*> test_range_index = arr.get_range(data_size / 2);
			range<int*> test_range_two_index = arr.get_range(1, data_size - 1);
			unused(test_range_base);
			unused(test_range_index);
			unused(test_range_two_index);
			breakpoint_nop();
		}

		void test_internal_array()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, data_size);
			int *ptr = arr.internal_array();
			unused(ptr);
			breakpoint_nop();
		}

		void test_is_empty_full()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr2;
			bool empty2 = arr2.is_empty();
			unused(empty2);
			breakpoint_nop();

			static_vector<int, 20> arr(data, data_size);
			bool empty = arr.is_empty();
			unused(empty);
			breakpoint_nop();
		}

		void test_clear()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, data_size);
			arr.clear();
			breakpoint_nop();

			static_vector<int, 20> arr2(data, data_size);
			arr2.clear_zero();
			breakpoint_nop();

			static_vector<test_struct, data_size> arr3;
			for(unsigned int i = 0; i < data_size; ++i)
			{
				arr3.new_element();
			}
			for(unsigned int i = 0; i < arr3.size(); ++i)
			{
				arr3[i].value = i;
			}
			arr3.clear_reconstruct();
			breakpoint_nop();
		}

		void test_new_element()
		{
			static_vector<int, 20> arr;
			for(unsigned int i = 0; i < arr.max_size(); ++i)
			{
				arr.new_element(i);
			}
			breakpoint_nop();
		}

		void test_insert_element()
		{
			static_vector<int, 20> arr;
			for(unsigned int i = 0; i < arr.max_size(); ++i)
			{
				arr.insert_element(0, i);
			}
			breakpoint_nop();
		}

		void test_remove()
		{
			static const int data_size = 20;
			int data[data_size];
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			static_vector<int, 20> arr(data, data_size);
			arr.remove_first();
			breakpoint_nop();

			arr.remove_last();
			breakpoint_nop();

			int size = arr.size();
			for(int i = 0; i < size; ++i)
			{
				arr.remove(0);
				breakpoint_nop();
			}
			breakpoint_nop();
		}
	}

	namespace test
	{
		void test_static_vector()
		{
			using namespace test_static_vector;

			test_constructor_destructor();
			test_copy_constructor();
			test_move_constructor();
			test_size();
			test_deep_copy();
			test_reconstruct_element();
			test_reconstruct_array();
			test_zero_array();
			test_get();
			test_first_last();
			test_get_range();
			test_internal_array();

			test_is_empty_full();
			test_clear();
			test_new_element();
			test_insert_element();
			test_remove();
		}
	}
}