#include "static_map_perf_test.h"
#include "RDTSC.h"

#include "nostl\static_map.h"
#include "nostl\unused.h"
#include <array>
#include <unordered_map>
#include <random>
#include <memory>
#include <numeric>
#include <fstream>
#include "Stopwatch.h"


#undef min
#undef max

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

std::random_device key_rd;
std::random_device value_rd;
std::random_device bool_rd;
std::mt19937 key_gen(key_rd());
std::mt19937 value_gen(value_rd());
std::mt19937 bool_gen(bool_rd());
std::uniform_int_distribution<> uniform_dis;
std::uniform_real_distribution<> uniform_real_dis;
std::uniform_int_distribution <> uniform_bool_dis(0, 50);

int get_rand_int_key()
{
	return uniform_dis(key_gen);
}

int get_rand_int_value()
{
	return uniform_dis(value_gen);
}

double get_rand_double_key()
{
	return uniform_real_dis(key_gen);
}

double get_rand_double_value()
{
	return uniform_real_dis(value_gen);
}

bool get_rand_bool()
{
	int val = uniform_bool_dis(bool_gen);
	return val >= 1;
}

template<uint test_size>
void random_insertion(int n)
{
	std::array<truly_large_object, test_size> key_data;
	std::array<truly_large_object, test_size> value_data;

	for(int i = 0; i < test_size; ++i)
	{
		key_data[i] =
		{
			int64(get_rand_double_key() * std::numeric_limits<int64>::max()),
			int64(get_rand_double_key() * std::numeric_limits<int64>::max()),
			int64(get_rand_double_key() * std::numeric_limits<int64>::max()),
			int64(get_rand_double_key() * std::numeric_limits<int64>::max()),
			int(get_rand_int_key()),
			char(get_rand_double_key() * std::numeric_limits<char>::max())
		};
		value_data[i] =
		{
			int64(get_rand_double_value() * std::numeric_limits<int64>::max()),
			int64(get_rand_double_value() * std::numeric_limits<int64>::max()),
			int64(get_rand_double_value() * std::numeric_limits<int64>::max()),
			int64(get_rand_double_value() * std::numeric_limits<int64>::max()),
			int(get_rand_int_value() * std::numeric_limits<int>::max()),
			char(get_rand_double_value() * std::numeric_limits<char>::max())
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
	const int test_size = 100000;

	std::unique_ptr<int[]> key_data = std::unique_ptr<int[]>(new int[test_size]);
	std::unique_ptr<int[]> value_data = std::unique_ptr<int[]>(new int[test_size]);

	for(int i = 0; i < test_size; ++i)
	{
		key_data[i] = get_rand_int_key();
		value_data[i] = get_rand_int_value();
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

void insertion_test()
{
	WarmupRDTSC();
	uint64 result1 = GetRDTSC();
	uint64 result2 = GetRDTSC();
	unused(result1);
	unused(result2);

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
	static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(), double(iload) / 10, 10});
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
	static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(),double(iload) / 100, 100});
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

	// size 100000
	static_times.clear();
	unordered_times.clear();
	n = 100000;
	iload = int(n * load + 0.5f);
	for(int i = 0; i < 100; ++i)
	{
		random_insertion_large(iload);
		static_times.push_back(random_insert_static_sum);
		unordered_times.push_back(random_insert_unordered_sum);

		random_insert_static_sum = 0;
		random_insert_unordered_sum = 0;
	}
	static_results.push_back({std::accumulate(static_times.begin(), static_times.end(), 0ll) / double(static_times.size()), static_times.size(), double(iload) / 100000, 100000});
	unordered_results.push_back({std::accumulate(unordered_times.begin(), unordered_times.end(), 0ll) / double(unordered_times.size()), unordered_times.size(), double(iload) / 100000, 100000});

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

template<uint test_size>
void random_frontload(
	std::vector<int>& keys,
	nostl::static_map<int, int, test_size>& static_map_test,
	std::unordered_map<int, int>& unordered_map_test,
	int n)
{
	unordered_map_test.reserve(test_size);

	for(int i = 0; i < n; ++i)
	{
		int key = get_rand_int_key();
		int value = get_rand_int_value();

		keys.push_back(key);
		std::pair<std::unordered_map<int, int>::iterator, bool> emplace_result = unordered_map_test.emplace(std::move(key), std::move(value));
		if(emplace_result.second == false)
		{
			breakpoint_nop();
		}
		static_map_test.emplace(std::move(key), std::move(value));
	}
}

template<uint test_size>
void random_modification_test(
	std::vector<int>& keys, 
	nostl::static_map<int, int, test_size>& static_map_test, 
	std::unordered_map<int, int>& unordered_map_test,
	int64& static_map_time, 
	int64& unordered_map_time,
	int& add_count)
{
	bool to_add = get_rand_bool();
	if(to_add && static_map_test.size() == test_size)
		to_add = false;
	else if(!to_add && static_map_test.size() == 0)
		to_add = true;

	int key = get_rand_int_key();
	if(!to_add)
	{
		key = keys.at(key % keys.size());
	}
	int value = get_rand_int_value();


	if(unordered_map_test.count(key) > 0)
	{
		breakpoint_nop();
	}

	add_count += to_add ? 1 : 0;

	int start_static_count = static_map_test.size();
	WarmupRDTSC();
	uint64 static_map_start_time = GetRDTSC();
	{
		if(to_add)
			static_map_test.insert(key, value);
		else
			static_map_test.erase(key);
	}
	uint64 static_map_end_time = GetRDTSC();
	static_map_time = (static_map_end_time - static_map_start_time) - g_correctionFactor;
	int end_static_count = static_map_test.size();

	if(!to_add && start_static_count > 0 && start_static_count != end_static_count + 1)
	{
		breakpoint_nop();
	}

	int count_prior = unordered_map_test.count(key);
	unused(count_prior);
	int start_size = unordered_map_test.size();
	WarmupRDTSC();
	uint64 unordered_map_start_time = GetRDTSC();
	{
		if(to_add)
			unordered_map_test.emplace(key, value);
		else
			unordered_map_test.erase(key);
	}
	uint64 unordered_map_end_time = GetRDTSC();
	unordered_map_time = (unordered_map_end_time - unordered_map_start_time) - g_correctionFactor;

	int end_size = unordered_map_test.size();
	if(start_size == end_size)
	{
		breakpoint_nop();
	}

	if(to_add)
		keys.push_back(key);
	else
		keys.erase(std::find(keys.begin(), keys.end(), key));


	if(static_map_test.size() != unordered_map_test.size())
	{
		breakpoint_nop();
	}
}

std::function<void(std::vector<uint64>&, double&, double&)> calc_stats =
[](std::vector<uint64>& data, double& out_mean, double& out_variance)
{
	double mean = std::accumulate(data.begin(), data.end(), 0ll) / double(data.size());

	double variance = std::accumulate(data.begin(), data.end(), 0.0,
		[&](const double& sum, const uint64& v_i)
	{
		return sum + std::pow((double(v_i) - mean), 2);
	});
	variance /= double(data.size());

	out_mean = mean;
	out_variance = variance;
};

void static_map_perf_test_1()
{
	std::vector<int> keys;
	keys.reserve(1000);

	std::vector<uint64> static_times;
	std::vector<uint64> unordered_times;
	std::vector<uint64> load;

	const int capacity = 10000;
	nostl::static_map<int, int, capacity> static_map_test;
	std::unordered_map<int, int> unordered_map_test;
	unordered_map_test.reserve(capacity);

	int add_count = 0;
	const int front_load = 0000;

	random_frontload(keys, static_map_test, unordered_map_test, front_load);

	for(int i = 0; i < 10000; ++i)
	{
		int64 static_map_time = 0;
		int64 unordered_map_time = 0;
		random_modification_test<capacity>(keys, static_map_test, unordered_map_test, static_map_time, unordered_map_time, add_count);

		static_times.push_back(static_map_time);
		unordered_times.push_back(unordered_map_time);
		load.push_back(static_map_test.size());

		printf("add_count: %d - %d\n", add_count, static_map_test.size());
	}

	int final_size = static_map_test.size();

	std::ofstream out_results_file;
	out_results_file.open("map_results.csv");

	out_results_file << "static, unordered, load, front load, capacity, add count, final size" << std::endl;
	for(uint i = 0; i < static_times.size(); ++i)
	{
		out_results_file << static_times[i] << ", " << unordered_times[i] << ", " << load[i];
		if(i == 0)
		{
			out_results_file << ", " <<
				front_load << ", " <<
				capacity << ", " <<
				add_count << ", " <<
				final_size;
		}

		out_results_file << std::endl;

	}

	out_results_file.close();

	double static_mean;
	double unordered_mean;
	double static_variance;
	double unordered_variance;

	calc_stats(static_times, static_mean, static_variance);
	calc_stats(unordered_times, unordered_mean, unordered_variance);

	double static_standard_devation = std::sqrt(static_variance);
	double unordered_standard_devation = std::sqrt(unordered_variance);

	printf("static   : %10.1f mean ; %10.1f std_dev\n", static_mean, static_standard_devation);
	printf("unordered: %10.1f mean ; %10.1f std_dev\n", unordered_variance, unordered_standard_devation);
	printf("additions: %d ; erasures: %d\n", add_count, 1000 - add_count);
	printf("static size: %d; unordered size: %d", static_map_test.size(), unordered_map_test.size());
}

Stopwatch::Duration perf_test_insertion(double d_load)
{
	const int capacity = 100000;
	const int load = (int)((d_load * capacity) + 0.5);
	nostl::static_map<int,int, capacity> unordered_map_test;
	std::vector<int> keys;
	keys.reserve(150);

	for(int i = 0; i < 150000; ++i)
	{
		keys.push_back(uniform_dis(key_gen));
	}

	std::sort(keys.begin(), keys.end());
	std::unique(keys.begin(), keys.end());

	for(int i = 0; i < load; ++i)
	{
		unordered_map_test.insert(keys[i], uniform_dis(value_gen));
	}

	int key = keys[load + 1];
	int value = uniform_dis(value_gen);

	Stopwatch watch;
	watch.Start();

	unordered_map_test.insert(key, value);

	watch.Stop();

	return watch.ElapsedTime();
}

void perf_test_insertion_n_times(int n, double load, std::vector<std::pair<double, double>>& out_mean_variance)
{
	std::vector<uint64> results;
	results.reserve(n);

	for(int i = 0; i < n; ++i)
	{
		Stopwatch::Duration result = perf_test_insertion(load);
		results.push_back(result.count());
	}

	double mean = 0.0;
	double variance = 0.0;
	calc_stats(results, mean, variance);

	out_mean_variance.emplace_back(mean, variance);
}

void perf_test_insertion_n_times_over_load()
{
	std::vector<std::pair<double, double>> mean_variance_per_load;
	mean_variance_per_load.reserve(100);
	int n_tests = 1000;

	for(int i = 0; i < 100; ++i)
	{
		Stopwatch watch;
		printf("%d", i);
		watch.Start();
		perf_test_insertion_n_times(n_tests, (i / 100.0), mean_variance_per_load);
		watch.Stop();
		printf(" - %f seconds. Estimate: %f seconds\n", watch.ElapsedTimeSeconds(), watch.ElapsedTimeSeconds()*(100 - i - 1));
	}

	std::ofstream out_results_file;
	out_results_file.open("perf_test_insertion_n_times_over_load_release_robin.csv");


	out_results_file << ("sample, load, mean, variance") << std::endl;
	for(uint i = 0; i < mean_variance_per_load.size(); ++i)
	{
		out_results_file << 
			i << ", " <<
			(i / 100.0) << ", " <<
			mean_variance_per_load[i].first << ", " <<
			mean_variance_per_load[i].second << std::endl;

	}
	out_results_file << std::endl << "n = " << n_tests << std::endl;
	out_results_file.close();
}

void run_static_map_perf_test()
{
	perf_test_insertion_n_times_over_load();
}
