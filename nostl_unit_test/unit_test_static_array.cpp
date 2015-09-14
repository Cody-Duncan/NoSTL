#include "stdafx.h"
#include "CppUnitTest.h"
#include "nostl\static_array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nostl_unit_test
{
	struct test_struct
	{
		int value;
		test_struct() : value(-1)
		{}
	};

	TEST_CLASS(unit_test_static_array)
	{
	public:
		static const unsigned int data_size = 20;
		static int data[data_size];

		// ==================== Initialization and Cleanup ====================

		TEST_CLASS_INITIALIZE(static_array_initialize)
		{
			// runs before class starts running tests.

			//fill data with 0->n
			for(int i = 0; i < data_size; ++i)
			{
				data[i] = i;
			}
		}

		TEST_METHOD_INITIALIZE(static_array_cleanup)
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
			nostl::static_array<int, 10> s_array;
		}

		TEST_METHOD(Default_Constructor_Complex)
		{
			nostl::static_array<test_struct, 10> s_array;
		}

		TEST_METHOD(Copy_Constructor_PointerSize)
		{
			nostl::static_array<int, data_size> s_array(data, data_size);
		}

		TEST_METHOD(Copy_Constructor_static_array)
		{
			nostl::static_array<int, data_size> s_array(data, data_size);

			nostl::static_array<int, data_size> test_array(s_array);
		}

		TEST_METHOD(Move_Constructor_static_array)
		{
			nostl::static_array<int, data_size> s_array(data, data_size);

			nostl::static_array<int, data_size> test_array(std::move(s_array));
		}

	};

	int nostl_unit_test::unit_test_static_array::data[nostl_unit_test::unit_test_static_array::data_size];
}