#include "static_map_perf_test.h"
#include "RDTSC.h"

#include "nostl\static_map.h"
#include <array>
#include <unordered_map>
#include <random>
#include <memory>
#include <numeric>

uint64 random_insert_static_sum = 0;
uint64 random_insert_unordered_sum = 0;

struct truly_large_object
{
	int64 a;
	int64 b;
	int64 c;
	int64 d;
	int h;
	char i; //just to mess up the byte ordering, make the size of the struct prime

	bool operator==(const truly_large_object& other) const
	{
		return
			a == other.a &&
			b == other.b &&
			c == other.c &&
			d == other.d &&
			h == other.h &&
			i == other.i;
	}
};

namespace std
{
	template <>
	struct hash<truly_large_object>
	{
		std::size_t operator()(const truly_large_object& k) const
		{
			using std::size_t;
			using std::hash;
			return ((hash<int64>()(k.a)
				^ (hash<int64>()(k.b) << 1)) >> 1)
				^ (hash<int64>()(k.c) << 1);
		}
	};

}

template<uint test_size>
void random_insertion(int n)
{
	std::random_device key_rd;
	std::random_device value_rd;
	std::mt19937 key_gen(key_rd());
	std::mt19937 value_gen(value_rd());
	std::uniform_real_distribution<> uniform_dis;

	std::array<truly_large_object, test_size> key_data;
	std::array<truly_large_object, test_size> value_data;

	for(int i = 0; i < test_size; ++i)
	{
		key_data[i] =
		{
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int(uniform_dis(key_gen) * std::numeric_limits<int>::max()),
			char(uniform_dis(key_gen) * std::numeric_limits<char>::max())
		};
		value_data[i] =
		{
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int64(uniform_dis(key_gen) * std::numeric_limits<int64>::max()),
			int(uniform_dis(key_gen) * std::numeric_limits<int>::max()),
			char(uniform_dis(key_gen) * std::numeric_limits<char>::max())
		};
	}

	nostl::static_map<truly_large_object, truly_large_object, test_size> static_map_test;
	WarmupRDTSC();
	uint64 static_map_start_time = GetRDTSC();
	{
		for(int i = 0; i < n; ++i)
		{
			static_map_test.emplace(std::move(key_data[i]), std::move(value_data[i]));
		}
	}
	uint64 static_map_end_time = GetRDTSC();
	random_insert_static_sum += (static_map_end_time - static_map_start_time) - g_correctionFactor;

	std::unordered_map<truly_large_object, truly_large_object> unordered_map_test;
	unordered_map_test.reserve(test_size);
	WarmupRDTSC();
	uint64 unordered_map_start_time = GetRDTSC();
	{
		for(int i = 0; i < n; ++i)
		{
			unordered_map_test.emplace(std::move(key_data[i]), std::move(value_data[i]));
		}
	}
	uint64 unordered_map_end_time = GetRDTSC();
	random_insert_unordered_sum += (unordered_map_end_time - unordered_map_start_time) - g_correctionFactor;
}

void random_insertion_large(int n)
{
	std::random_device key_rd;
	std::random_device value_rd;
	std::mt19937 key_gen(key_rd());
	std::mt19937 value_gen(value_rd());
	std::uniform_int_distribution<> uniform_dis;

	const int test_size = 100000;

	std::unique_ptr<int[]> key_data = std::unique_ptr<int[]>(new int[test_size]);
	std::unique_ptr<int[]> value_data = std::unique_ptr<int[]>(new int[test_size]);

	for(int i = 0; i < test_size; ++i)
	{
		key_data[i] = uniform_dis(key_gen);
		value_data[i] = uniform_dis(value_gen);
	}

	std::unique_ptr<nostl::static_map<int, int, test_size>> static_map_test =
		std::unique_ptr<nostl::static_map<int, int, test_size>>(new nostl::static_map<int, int, test_size>());
	WarmupRDTSC();
	uint64 static_map_start_time = GetRDTSC();
	{
		for(int i = 0; i < n; ++i)
		{
			static_map_test->emplace(std::move(key_data[i]), std::move(value_data[i]));
		}
	}
	uint64 static_map_end_time = GetRDTSC();
	random_insert_static_sum += (static_map_end_time - static_map_start_time) - g_correctionFactor;

	std::unique_ptr<std::unordered_map<int, int>> unordered_map_test =
		std::unique_ptr<std::unordered_map<int, int>>(new std::unordered_map<int, int>());
	unordered_map_test->reserve(test_size);
	WarmupRDTSC();
	uint64 unordered_map_start_time = GetRDTSC();
	{
		for(int i = 0; i < n; ++i)
		{
			unordered_map_test->emplace(std::move(key_data[i]), std::move(value_data[i]));
		}
	}
	uint64 unordered_map_end_time = GetRDTSC();
	random_insert_unordered_sum += (unordered_map_end_time - unordered_map_start_time) - g_correctionFactor;
}

void random_deletion()
{

}

void random_find_key()
{

}

struct result
{
	double average;
	uint64 samples;
	double load_factor;
	uint64 max_size;
};

void run_tests()
{
	WarmupRDTSC();
	uint64 result1= GetRDTSC();
	uint64 result2 = GetRDTSC();

	std::vector<uint64> static_times;
	std::vector<uint64> unordered_times;

	std::vector<result> static_results;
	std::vector<result> unordered_results;

	int n = 1;
	double load = 0.88;
	int iload = 1;

	// size 10
	static_times.clear();
	unordered_times.clear();
	n = 10;
	iload = int(n * load + 0.5);
	for(int i = 0; i < 1000; ++i)
	{
		random_insertion<10>(iload);
		static_times.push_back(random_insert_static_sum);
		unordered_times.push_back(random_insert_unordered_sum);

		random_insert_static_sum = 0;
		random_insert_unordered_sum = 0;
	}
	static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(), double(iload)/10, 10});
	unordered_results.push_back({std::accumulate(unordered_times.begin(), unordered_times.end(), 0ll) / double(unordered_times.size()), unordered_times.size(), double(iload) / 10, 10});

	// size 100
	static_times.clear();
	unordered_times.clear();
	n = 100;
	iload = int(n * load + 0.5f);
	for(int i = 0; i < 1000; ++i)
	{
		random_insertion<100>(iload);
		static_times.push_back(random_insert_static_sum);
		unordered_times.push_back(random_insert_unordered_sum);

		random_insert_static_sum = 0;
		random_insert_unordered_sum = 0;
	}
	static_results.push_back({ std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(),double(iload) / 100, 100 });
	unordered_results.push_back({std::accumulate(unordered_times.begin(), unordered_times.end(), 0ll) / double(unordered_times.size()), unordered_times.size(), double(iload) / 100, 100});

	// size 1000
	static_times.clear();
	unordered_times.clear();
	n = 1000;
	iload = int(n * load + 0.5f);
	for(int i = 0; i < 1000; ++i)
	{
		random_insertion<1000>(iload);
		static_times.push_back(random_insert_static_sum);
		unordered_times.push_back(random_insert_unordered_sum);

		random_insert_static_sum = 0;
		random_insert_unordered_sum = 0;
	}
	static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(), double(iload) / 1000, 1000});
	unordered_results.push_back({std::accumulate(unordered_times.begin(), unordered_times.end(), 0ll) / double(unordered_times.size()), unordered_times.size(), double(iload) / 1000, 1000});

	// size 10000
	static_times.clear();
	unordered_times.clear();
	n = 10000;
	iload = int(n * load + 0.5f);
	for(int i = 0; i < 1000; ++i)
	{
		random_insertion<10000>(iload);
		static_times.push_back(random_insert_static_sum);
		unordered_times.push_back(random_insert_unordered_sum);
	
		random_insert_static_sum = 0;
		random_insert_unordered_sum = 0;
	}
	static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(), double(iload) / 10000, 10000});
	unordered_results.push_back({std::accumulate(unordered_times.begin(), unordered_times.end(), 0ll) / double(unordered_times.size()), unordered_times.size(), double(iload) / 10000, 10000});
	//
	//// size 100000
	//static_times.clear();
	//unordered_times.clear();
	//n = 100000;
	//iload = int(n * load + 0.5f);
	//for(int i = 0; i < 100; ++i)
	//{
	//	random_insertion_large(iload);
	//	static_times.push_back(random_insert_static_sum);
	//	unordered_times.push_back(random_insert_unordered_sum);
	//
	//	random_insert_static_sum = 0;
	//	random_insert_unordered_sum = 0;
	//}
	//static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(), double(iload) / 100000, 100000});
	//unordered_results.push_back({std::accumulate(unordered_times.begin(), unordered_times.end(), 0ll) / double(unordered_times.size()), unordered_times.size(), double(iload) / 100000, 100000});

	for(uint i = 0; i < static_results.size(); ++i)
	{
		result& static_r = static_results[i];
		printf("savg: %12.1f, samples: %10llu, load: %5f, capacity: %10llu\n", 
			static_r.average,
			static_r.samples,
			static_r.load_factor,
			static_r.max_size);

		result& unordered_r = unordered_results[i];
		printf("uavg: %12.1f, samples: %10llu, load: %5f, capacity: %10llu\n",
			unordered_r.average,
			unordered_r.samples,
			unordered_r.load_factor,
			unordered_r.max_size);
	}
}
