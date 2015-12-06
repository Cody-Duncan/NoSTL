/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef STATIC_MAP_H
#define STATIC_MAP_H

// ---------- includes ---------
#include "primitives.h"
#include "static_array.h"
#include "assert.h"
#include <functional> // std::Hash, std::equal_to

namespace nostl
{
#define NONE -1
	constexpr uint empty_hash = 0;
	constexpr uint deleted_hash = NONE;


	template <class Key, class Value>
	struct map_pair
	{
		uint hash_value;
		Key key;
		Value value;
	};

	template <class Key, class Value, uint max_length, typename HashFunction = std::hash<Key>, typename Equality = std::equal_to<Key>>
	class static_map : protected base_array<map_pair<Key, Value>, static_map<Key, Value, max_length, HashFunction, Equality>>
	{
	public:
		struct Bucket
		{
			uint hash_value;
			uint storage_index;
		};

		// ==== constructors / destructors ====

		static_map();
		virtual ~static_map() = default;

		// ==== base_array interface ====
		unsigned int size();
		unsigned int max_size();
		map_pair<Key, Value>* internal_array();
		const map_pair<Key, Value>* internal_array() const;

		void insert(Key new_key, Value new_value);
		void emplace(Key&& new_key, Value&& new_value);
		bool erase(const Key& key);
		Value& get(const Key&);
		const Value& get(const Key&) const;

		bool contains(const Key&) const;

		uint get_dist()
		{
			return *m_max_dist;
		}

	private:
		HashFunction m_hash_function;

		static_array<map_pair<Key, Value>, max_length> m_buckets;
		uint m_size;
		uint* m_max_dist;

		uint compute_hash(const Key& key) const;
		uint probe_distance(uint input_hash_value, uint index) const;
		uint find_index(const Key& key) const;

		void construct(uint pos, uint hash_value, Key&& key, Value&& value);
		void emplace_with_hash(uint hash_value, Key&& new_key, Value&& new_value);

		inline uint clamp_to_bucket_length(uint index) const
		{
			return index % max_length;
		}

		inline uint compute_desired_pos(uint hash_value) const
		{
			return hash_value % max_length;
		}
	};

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	static_map<Key, Value, max_length, HashFunction, Equality>::
		static_map() :
		m_size(0)
	{
		m_buckets.zero_array();
		m_max_dist = new uint();
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	unsigned int
		static_map<Key, Value, max_length, HashFunction, Equality>::
		size()
	{
		return m_size;
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	unsigned int
		static_map<Key, Value, max_length, HashFunction, Equality>::
		max_size()
	{
		return max_length;
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	map_pair<Key, Value>*
		static_map<Key, Value, max_length, HashFunction, Equality>::
		internal_array()
	{
		return m_storage.internal_array();
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	const map_pair<Key, Value>*
		static_map<Key, Value, max_length, HashFunction, Equality>::
		internal_array() const
	{
		return m_storage.internal_array();
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	void
		static_map<Key, Value, max_length, HashFunction, Equality>::
		insert(Key new_key, Value new_value)
	{
		emplace(std::move(new_key), std::move(new_value));
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	void
		static_map<Key, Value, max_length, HashFunction, Equality>::
		emplace(Key&& new_key, Value&& new_value)
	{
		emplace_with_hash(
			compute_hash(std::forward<Key>(new_key)),
			std::forward<Key>(new_key),
			std::forward<Value>(new_value));
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	uint
		static_map<Key, Value, max_length, HashFunction, Equality>::
		compute_hash(const Key& key) const
	{
		return m_hash_function(key);
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	uint
		static_map<Key, Value, max_length, HashFunction, Equality>::
		probe_distance(uint input_hash_value, uint index) const
	{
		uint desired_pos = compute_desired_pos(input_hash_value);
		return (index + max_length - desired_pos) % max_length;
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	uint
		static_map<Key, Value, max_length, HashFunction, Equality>::
		find_index(const Key& key) const
	{
		const uint hash_value = compute_hash(key);
		uint pos = compute_desired_pos(hash_value);
		uint dist = 0;
		*m_max_dist = dist;

		for(;;)
		{
			const map_pair<Key, Value>& bucket = m_buckets[pos];

			if(bucket.hash_value != deleted_hash) //skip deleted
			{
				if(bucket.hash_value == empty_hash)
				{
					return NONE;
				}
				else
				{
					uint bucket_probe_dist = probe_distance(bucket.hash_value, pos);
					if(dist > bucket_probe_dist)
					{
						return NONE;
					}
					else if(bucket.hash_value == hash_value && bucket.key == key)
					{
						return pos;
					}
				}
			}

			pos = clamp_to_bucket_length(pos + 1);
			++dist;
			*m_max_dist = dist;
		}
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	void
		static_map<Key, Value, max_length, HashFunction, Equality>::
		construct(uint pos, uint hash_value, Key&& key, Value&& value)
	{
		m_buckets[pos] = {
			hash_value,
			key,
			value};
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	void
		static_map<Key, Value, max_length, HashFunction, Equality>::
		emplace_with_hash(uint hash_value, Key&& new_key, Value&& new_value)
	{
		uint desired_pos = compute_desired_pos(hash_value);
		uint pos = desired_pos;
		int dist = 0;

		for(;;)
		{
			map_pair<Key, Value>& bucket = m_buckets[pos];

			if(bucket.hash_value == hash_value)
			{
				//found existing, replace it
				bucket.value = new_value;
				break;
			}

			if(bucket.hash_value == empty_hash)
			{
				//construct
				construct(pos, hash_value, std::forward<Key>(new_key), std::forward<Value>(new_value));
				++m_size;
				break;
			}

			// If the existing elem has probed less than us, 
			// then swap places with existing
			// elem, and keep going to find another slot for that elem.
			int existing_distance = probe_distance(bucket.hash_value, pos);
			if(existing_distance < dist)
			{
				// if this bucket is a tombstone, go ahead and take it.
				if(bucket.hash_value == deleted_hash)
				{
					//construct
					construct(pos, hash_value, std::forward<Key>(new_key), std::forward<Value>(new_value));
					++m_size;
					break;
				}

				// otherwise, swap the entry with the one in the bucket.
				// The entry in the bucket is "rich" in that it got a slot early.
				// We are giving it's easily obtained spot to one that is "poor" and had to resolve more collisions.
				std::swap(hash_value, bucket.hash_value);
				std::swap(new_key, bucket.key);
				std::swap(new_value, bucket.value);
				dist = existing_distance;
			}

			pos = clamp_to_bucket_length(pos + 1);
			++dist;
		}
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	bool
		static_map<Key, Value, max_length, HashFunction, Equality>::
		erase(const Key& key)
	{
		const uint pos = find_index(key);

		if(pos == NONE)
		{
			find_index(key);
			return false;
		}

		m_buckets[pos].~map_pair<Key, Value>();
		m_buckets[pos].hash_value = deleted_hash;
		--m_size;
		return true;
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	Value&
		static_map<Key, Value, max_length, HashFunction, Equality>::
		get(const Key& key)
	{
		return const_cast<Value&>(const_cast<const static_map<Key, Value, max_length, HashFunction, Equality>*>(this)->get(key));
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	const Value&
		static_map<Key, Value, max_length, HashFunction, Equality>::
		get(const Key& key) const
	{
		const uint pos = find_index(key);
		z_assert(pos != NONE);
		return m_buckets[pos].value;
	}

	template <class Key, class Value, uint max_length, typename HashFunction, typename Equality>
	bool
		static_map<Key, Value, max_length, HashFunction, Equality>::
		contains(const Key& key) const
	{
		const uint pos = find_index(key);
		return pos != NONE;
	}

}

// --------- testing functions --------

namespace nostl
{
	namespace test
	{
		void test_static_map();
	}
}


#endif