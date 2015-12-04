/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#include "static_map.h"
#include "unused.h"

namespace nostl
{
	namespace test_static_map
	{
		void test_basic()
		{
			static_map<int, char, 16> map;
			map.emplace(1, 'a');
			map.emplace(2, 'b');
			map.emplace(3, 'c');
			map.emplace(17, 'd');
			map.emplace(18, 'e');
			map.emplace(6, 'f');
			map.emplace(7, 'g');
			map.emplace(8, 'h');
			map.emplace(9, 'i');
			map.emplace(10, 'j');
			map.emplace(11, 'k');
			map.emplace(12, 'l');
			map.emplace(13, 'm');
			map.emplace(14, 'n');
			map.emplace(15, 'o');
			map.emplace(16, 'p');
			breakpoint_nop();

			map.erase(2);
			breakpoint_nop();

			map.emplace(2, 'z');
			breakpoint_nop();

			uint sum = 0;

			map.get(1);  sum += map.get_dist();
			map.get(2);  sum += map.get_dist();
			map.get(3);  sum += map.get_dist();
			map.get(17); sum += map.get_dist();
			map.get(18); sum += map.get_dist();
			map.get(6);  sum += map.get_dist();
			map.get(7);  sum += map.get_dist();
			map.get(8);  sum += map.get_dist();
			map.get(9);  sum += map.get_dist();
			map.get(10); sum += map.get_dist();
			map.get(11); sum += map.get_dist();
			map.get(12); sum += map.get_dist();
			map.get(13); sum += map.get_dist();
			map.get(14); sum += map.get_dist();
			map.get(15); sum += map.get_dist();
			map.get(16); sum += map.get_dist();
			float avg_1 = (float)sum / 16.0f;
			unused(avg_1);
			breakpoint_nop();

			map.erase(12);
			map.erase(3);
			map.erase(16);
			map.erase(9);
			map.erase(11);
			map.erase(17);
			map.erase(1);
			breakpoint_nop();

			map.emplace(1, 'a');
			map.emplace(3, 'c');
			map.emplace(9, 'i');
			map.emplace(11, 'k');
			map.emplace(12, 'l');
			map.emplace(16, 'p');
			map.emplace(17, 'd');
			breakpoint_nop();

			sum = 0;
			map.get(1);  sum += map.get_dist();
			map.get(2);	 sum += map.get_dist();
			map.get(3);	 sum += map.get_dist();
			map.get(17); sum += map.get_dist();
			map.get(18); sum += map.get_dist();
			map.get(6);	 sum += map.get_dist();
			map.get(7);	 sum += map.get_dist();
			map.get(8);	 sum += map.get_dist();
			map.get(9);	 sum += map.get_dist();
			map.get(10); sum += map.get_dist();
			map.get(11); sum += map.get_dist();
			map.get(12); sum += map.get_dist();
			map.get(13); sum += map.get_dist();
			map.get(14); sum += map.get_dist();
			map.get(15); sum += map.get_dist();
			map.get(16); sum += map.get_dist();
			float avg_2 = (float)sum / 16.0f;
			unused(avg_2);
			breakpoint_nop();
		}
	}

	namespace test
	{
		void test_static_map()
		{
			using namespace test_static_map;

			nostl::test_static_map::test_basic();
		}
	}
}