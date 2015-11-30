/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

// ---------- includes ---------
#include "primitives.h"
#include "range2.h"
#include "assert.h"

#include "base_array.h"

// ---------- definitions ----------

namespace nostl
{


	template <class T, uint max_length>
	struct static_array : protected base_array<T, static_array<T, max_length>>
	{
	public:
		using self = static_array;
        using value_type = T;
        using reference = T&;
        using const_reference = T const&;
        using iterator = T*;
		using I = iterator;
        using const_iterator = T const*;
		using const_I = const_iterator;
        using pointer = T*;
        using const_pointer = T const*;
        using size_type = unsigned int;
        using difference_type = uint64;
        //using reverse_iterator = ranges::reverse_iterator<iterator>;
        //using const_reverse_iterator = ranges::reverse_iterator<const_iterator>;

		static_array();
		~static_array();

		static_array(const T *, uint size);
		static_array(range<T*> &);
		static_array(const static_array &);
		static_array(static_array &&);

		//operator= , compiler generated

		uint size() const;
		uint max_size() const;
		bool is_empty() const;
		bool is_full() const;

		template <template <class, uint> class array_type, uint other_max_length>
		static_array &deep_copy(nostl::base_array<T, array_type<T, other_max_length>> &other);

		template <uint array_size>
		static_array &deep_copy(const T(&)[array_size]);

		static_array &deep_copy(const T *, uint size);
		static_array &deep_copy(range<T*> &);
		static_array &deep_copy(const static_array &);

		void reconstruct_element(uint index);
		void reconstruct_array();
		void zero_array();

		T &get(uint index);
		const T &get(uint index) const;

		T &operator[](uint index);
		const T &operator[](uint index) const;

		T &first();
		const T &first() const;

		T &last();
		const T &last() const;

		T* begin();
		const T *begin() const;

		T *end();
		const T *end() const;

		range<I> get_range();
		range<const_I> get_range() const;
		range<I> get_range(uint index);
		range<const_I> get_range(uint index) const;
		range<I> get_range(uint start_index, uint end_index);
		range<const_I> get_range(uint start_index, uint end_index) const;

		T *internal_array();
		const T *internal_array() const;

	private:
		T m_data[max_length];
	};
}

#include "static_array.inl"

// --------- testing functions --------

namespace nostl
{
	namespace test
	{
		void test_static_array();
	}
}

#endif