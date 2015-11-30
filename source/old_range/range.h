/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef RANGE_H
#define RANGE_H

// ---------- includes ---------

#include <type_traits>
#include <iterator>

namespace nostl
{
	template <typename T, typename iterator_t = T *>
	struct range
	{
		typedef iterator_t iterator_type;
		iterator_t iterator;
		int length;

		range(const iterator_t &iter, int length) : iterator(iter),
													length(length)
		{
		}

		// allows non-const to be assigned to const type
		template <typename other_T, typename other_iterator>
		range(range<other_T, other_iterator *> &other) : iterator(other.iterator),
														 length(other.length)
		{
		}

		T &operator*() const
		{
			return *iterator;
		}

		T &get_element() const
		{
			return *iterator;
		}

		bool is_end() { return length == 0; }

		range &operator++()
		{
			++iterator;
			--length;
			return *this;
		}

		range &operator++(int)
		{
			iterator_t temp = iterator;
			int temp_len = length;
			++iterator;
			--length;
			return range(temp, temp_len);
		}

		bool operator==(const range &it)
		{
			return this->iterator == it.iterator &&
				   this->length == it.length;
		}

		range find_first_of(const T &val) const;
		range find_first_of(const range<const T> &values) const;

		template <unsigned int arr_length>
		range find_first_of(const T(&values)[arr_length]) const;

		range find_last_of(const T &val) const;
		range find_last_of(const range<const T> &values) const;

		template <unsigned int arr_length>
		range find_last_of(const T(&values)[arr_length]) const;
	};

	template <typename T, typename I>
	range<T, I> make_range(I iter, unsigned int length)
	{
		return range<T, I>(iter, length);
	}

	template <typename T>
	range<T, T *> make_range(T *iter, unsigned int length)
	{
		return range<T, T *>(iter, length);
	}

	template <typename T, typename I>
	range<T, I> make_null_range(I iter, unsigned int length)
	{
		return range<T, I>(iter + length, 0);
	}

	template <typename T, typename I>
	range<T, I> make_null_range(const range<T, I> &source_range)
	{
		return range<T, I>(source_range.iterator + source_range.length, 0);
	}

	template <typename T, typename I>
	range<T, I> make_null_range(const range<T, I> *source_range)
	{
		return range<T, I>(source_range->iterator + source_range->length, 0);
	}
}

#include "range_algorithms.h"
#include "range.inl"

#endif