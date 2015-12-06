#include "stdafx.h"
#include "CppUnitTest.h"
#include <random>
#include <numeric>
#include <algorithm>
#include "nostl\static_map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#undef max

namespace nostl_unit_test
{
	struct test_struct
	{
		int value;
		test_struct() : value(-1)
		{}
	};

	TEST_CLASS(unit_test)
	{
	public:
		static const unsigned int data_size = 20;
		static int data[data_size];

		static const int max_rand_value = std::numeric_limits<int>::max();
		static int random_uniq_keys[data_size];
		static int random_uniq_values[data_size];

		static int random_nonuniq_keys[data_size];
		static int random_nonuniq_values[data_size];
		static int random_nonuniq_mapping[data_size];
		static uint num_uniq_keys_in_nonuniq_set;

		// ==================== Initialization and Cleanup ====================

		TEST_CLASS_INITIALIZE(static_map_initialize)
		{
			// runs before class starts running tests.

			//fill data with 0->n
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}

			std::fill(random_uniq_keys, random_uniq_keys + data_size, -1);
			std::fill(random_uniq_values, random_uniq_values + data_size, -1);

			std::mt19937 key_gen(13);
			std::mt19937 value_gen(17);
			std::uniform_int_distribution<> uniform_dis(0, max_rand_value);

			for(int i = 0; i < data_size; ++i)
			{
				int key = uniform_dis(key_gen);
				while(std::find(random_uniq_keys, random_uniq_keys + data_size, key) != (random_uniq_keys + data_size))
				{
					key = uniform_dis(key_gen);
				}
				random_uniq_keys[i] = key;

				int value = uniform_dis(value_gen);
				while(std::find(random_uniq_values, random_uniq_values + data_size, key) != (random_uniq_values + data_size))
				{
					value = uniform_dis(value_gen);
				}
				random_uniq_values[i] = uniform_dis(value_gen);
			}

			std::uniform_int_distribution<> uniform_small_dis(0, data_size/2);

			for(int i = 0; i < data_size; ++i)
			{
				int key = uniform_small_dis(key_gen);
				int value = uniform_small_dis(value_gen);

				random_nonuniq_keys[i] = key;
				random_nonuniq_values[i] = value;
			}

			int* random_nonuniq_keys_end = random_nonuniq_keys + data_size;

			int temp_nonuniq_keys[data_size];
			std::copy(random_nonuniq_keys, random_nonuniq_keys_end, temp_nonuniq_keys);

			std::sort(std::begin(temp_nonuniq_keys), std::end(temp_nonuniq_keys));
			int* end_unique = std::unique(std::begin(temp_nonuniq_keys), std::end(temp_nonuniq_keys));
			num_uniq_keys_in_nonuniq_set = data_size - ((temp_nonuniq_keys + data_size) - end_unique);

			for(int i = 0; i < data_size; ++i)
			{
				std::reverse_iterator<int*>result = 
					std::find_first_of(
						std::rbegin(random_nonuniq_keys), 
						std::rend(random_nonuniq_keys), 
						&random_nonuniq_keys[i],
						&random_nonuniq_keys[i+1]);
				random_nonuniq_mapping[i] = &(*result) - random_nonuniq_keys;
			}
		}

		TEST_METHOD_INITIALIZE(static_map_cleanup)
		{
			// runs before each method
		}

		TEST_METHOD_CLEANUP(method_initialize)
		{
			// runs after each method			
		}

		TEST_CLASS_CLEANUP(method_cleanup)
		{
			// runs after class finishes running tests.
		}


		// ==================== TESTS ====================

		TEST_METHOD(Assert_Namespace_Test)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Default_Constructor_Primitive)
		{
			nostl::static_map<int, int, data_size> test_map;
		}

		TEST_METHOD(Default_Constructor_Complex)
		{
			nostl::static_map<int, test_struct, data_size> test_map;
		}

		TEST_METHOD(Copy_Constructor)
		{
			nostl::static_map<int, int, data_size> test_map;

			nostl::static_map<int, int, data_size> test_array(test_map);
		}

		TEST_METHOD(Move_Constructor)
		{
			nostl::static_map<int, int, data_size> test_map;

			nostl::static_map<int, int, data_size> test_array(std::move(test_map));
		}

		TEST_METHOD(Insert)
		{
			nostl::static_map<int, int, data_size> test_map;

			for(int i = 0; i < data_size; ++i)
			{
				int key = random_uniq_keys[i];
				int value = random_uniq_values[i];
				test_map.insert(key, value);
			}

			Assert::AreEqual(data_size, test_map.size());
		}

		TEST_METHOD(Emplace)
		{
			nostl::static_map<int, int, data_size> test_map;

			for(int i = 0; i < data_size; ++i)
			{
				int key = random_uniq_keys[i];
				int value = random_uniq_values[i];
				test_map.emplace(std::move(key), std::move(value));
			}

			Assert::AreEqual(data_size, test_map.size());
		}

		TEST_METHOD(Find_Index)
		{
			nostl::static_map<int, int, data_size> test_map;

			for(int i = 0; i < data_size; ++i)
			{
				test_map.insert(random_uniq_keys[i], random_uniq_values[i]);
			}

			for(int i = 0; i < data_size; ++i)
			{
				Assert::AreEqual(random_uniq_values[i], test_map.get(random_uniq_keys[i]));
			}
		}

		TEST_METHOD(Erase)
		{
			nostl::static_map<int, int, data_size> test_map;

			for(int i = 0; i < data_size; ++i)
			{
				test_map.insert(random_uniq_keys[i], random_uniq_values[i]);
			}

			for(int i = 0; i < data_size; ++i)
			{
				test_map.erase(random_uniq_keys[i]);

				//make sure size is correct
				Assert::AreEqual(data_size - (i + 1), test_map.size(), L"incorrect size");

				//make sure other values still exist
				for(int k = i+1; k < data_size; ++k)
				{
					Assert::AreEqual(random_uniq_values[k], test_map.get(random_uniq_keys[k]), L"could not reference existing key");
				}
			}
		}

		TEST_METHOD(Insert_Duplicate)
		{
			nostl::static_map<int, int, data_size> test_map;

			for(int i = 0; i < data_size; ++i)
			{
				int key = random_nonuniq_keys[i];
				int value = random_uniq_values[i];
				test_map.insert(key, value);
			}

			Assert::AreEqual(num_uniq_keys_in_nonuniq_set, test_map.size());

			for(int i = 0; i < data_size; ++i)
			{
				Assert::AreEqual(random_uniq_values[random_nonuniq_mapping[i]], test_map.get(random_nonuniq_keys[i]));
			}
		}

		bool exists(std::vector<std::pair<int, int>> keys, int key, std::vector<std::pair<int, int>>::iterator& out_iter)
		{
			out_iter = std::find_if(keys.begin(), keys.end(), [&](const std::pair<int, int>& value)
			{
				return value.first == key;
			});
			return out_iter!= keys.end();
		}

		TEST_METHOD(Random_Modification)
		{
			nostl::static_map<int, int, data_size> test_map;
			std::vector<std::pair<int, int>> current_pairs;

			for(int i = 0; i < data_size; ++i)
			{
				int key = random_uniq_values[i];
				int value = random_uniq_values[i];
				test_map.insert(key, value);
				current_pairs.push_back(std::make_pair(key, value));
			}

			std::mt19937 rand_gen_bool(23);
			std::uniform_int_distribution<> uniform_dis_bool(0,1);

			std::mt19937 rand_gen_index(31);
			std::mt19937 rand_gen_key(37);
			std::mt19937 rand_gen_value(41);
			std::uniform_int_distribution<> uniform_dis(0, max_rand_value);
			std::uniform_int_distribution<> uniform_small_dis_key(0, data_size / 2);

			for(int test_count = 0; test_count < 1000; ++test_count)
			{
				bool to_add = uniform_dis_bool(rand_gen_bool) == 1;
				if(to_add && test_map.size() == test_map.max_size())
				{
					to_add = false;
				}
				else if(!to_add && test_map.size() == 0)
				{
					to_add = true;
				}

				if(to_add) //insert
				{
					int key = uniform_dis(rand_gen_key);
					int value = uniform_dis(rand_gen_value);
					std::vector<std::pair<int, int>>::iterator existing_pair = current_pairs.end();

					if(key == 1088450312)
					{
						breakpoint_nop();
					}

					if(exists(current_pairs, key, existing_pair))
					{
						uint size_prior = test_map.size();
						int value_prior = test_map.get(key);
						test_map.insert(key, value);

						Assert::AreEqual(size_prior, test_map.size());
						Assert::AreNotEqual(value_prior, test_map.get(key));
						Assert::AreEqual(value, test_map.get(key));

						existing_pair->second = value;

						if(!test_map.contains(1088450312))
						{
							breakpoint_nop();
						}
					}
					else
					{
						if(key == 547181388)
						{
							breakpoint_nop();
						}

						uint size_prior = test_map.size();
						test_map.insert(key, value);

						Assert::AreEqual(size_prior + 1, test_map.size());
						Assert::AreEqual(value, test_map.get(key));

						current_pairs.push_back(std::make_pair(key, value));

						if(!test_map.contains(1088450312))
						{
							breakpoint_nop();
						}
					}

					Assert::IsTrue(test_map.contains(key));
				}
				else // erase
				{

					std::uniform_int_distribution<> uniform_dis_index(0, current_pairs.size()-1);
					int random_pair_index = uniform_dis_index(rand_gen_index);
					std::pair<int, int> key_value = current_pairs.at(random_pair_index);

					if(key_value.first == 2094092985)
					{
						breakpoint_nop();
					}

					if(key_value.first == 1088450312)
					{
						breakpoint_nop();
					}

					Assert::IsTrue(test_map.contains(key_value.first));

					uint size_prior = test_map.size();
					test_map.erase(key_value.first);

					Assert::AreEqual(size_prior - 1, test_map.size());
					Assert::IsFalse(test_map.contains(key_value.first));

					current_pairs.erase(current_pairs.begin() + random_pair_index);

					if(!test_map.contains(1088450312))
					{
						breakpoint_nop();
					}
				}
				if(!test_map.contains(1088450312))
				{
					breakpoint_nop();
				}
			}
		}
	};

	int nostl_unit_test::unit_test::data[nostl_unit_test::unit_test::data_size];
	int nostl_unit_test::unit_test::random_uniq_keys[nostl_unit_test::unit_test::data_size];
	int nostl_unit_test::unit_test::random_uniq_values[nostl_unit_test::unit_test::data_size];
	int nostl_unit_test::unit_test::random_nonuniq_keys[nostl_unit_test::unit_test::data_size];
	int nostl_unit_test::unit_test::random_nonuniq_values[nostl_unit_test::unit_test::data_size];
	int nostl_unit_test::unit_test::random_nonuniq_mapping[nostl_unit_test::unit_test::data_size];
	uint nostl_unit_test::unit_test::num_uniq_keys_in_nonuniq_set = 0;
}