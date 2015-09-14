/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef RANGE_ALGORITHMS_H
#define RANGE_ALGORITHMS_H

// ---------- includes ---------
#include <type_traits>
#include "range.h"

namespace nostl
{







	// ******************** find_first_of ********************

	// ------------------------------
	// find single value in a range

	template<typename T, typename iterator_t>
	range<const T, iterator_t> find_first_of(range<const T, iterator_t> search_range, const T& val)
	{
		iterator_t& current_iter = search_range.iterator;
		int length = search_range.length;
		for(int i = 0; i < length; ++i)
		{
			if(*current_iter == val)
			{
				return make_range(current_iter, length - i);
			}

			++current_iter;
		}

		return make_null_range(search_range);
	}

	template<typename T, typename iterator_t>
	range<T, iterator_t> find_first_of(range<T, iterator_t> search_range, const T& val)
	{
		range<const T> result= find_first_of(range<const T>(search_range), val);
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}


	// ------------------------------
	// find any of those in a range

	template<typename T, typename iterator_t>
	range<const T, iterator_t> find_first_of(range<const T, iterator_t> search_range, range<const T> values)
	{
		iterator_t current_iter = search_range.iterator;
		int length = search_range.length;
		for(int i = 0; i < length; ++i)
		{
			typename range<const T>::iterator_type values_iter = values.iterator;
			for(int k = 0; k < values.length; ++k)
			{
				if(*current_iter == *values_iter)
				{
					return make_range(current_iter, length - i);
				}

				++values_iter;
			}

			++current_iter;
		}

		return make_null_range(search_range);
	}

	// (const range, non-const range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> find_first_of(range<const T, iterator_t> search_range, range<T> values)
	{
		range<const T> result= find_first_of(search_range, range<const T>(values));
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}

	// (non-const range, const range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> find_first_of(range<T, iterator_t> search_range, range<const T> values)
	{
		range<const T> result= find_first_of(range<const T>(search_range), values);
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}

	// (non-const range, non_const range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> find_first_of(range<T, iterator_t> search_range, range<T> values)
	{
		range<const T> result= find_first_of(range<const T>(search_range), range<const T>(values));
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}


	// ------------------------------
	// find any of those in an array

	// (const range, const array)
	template<typename T, typename iterator_t, unsigned int arr_length>
	range<const T, iterator_t> find_first_of(range<const T, iterator_t> search_range, const T(&values)[arr_length])
	{		
		return nostl::find_first_of(search_range, make_range(values, arr_length));
	}

	// (non-const range, const array)
	template<typename T, typename iterator_t, unsigned int arr_length>
	range<T, iterator_t> find_first_of(range<T, iterator_t> search_range, const T(&values)[arr_length])
	{	
		range<const T> result= find_first_of(range<const T>(search_range), values);
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}	
	






	// ******************** find_last_of ********************

	// ------------------------------
	// find single value in a range

	template<typename T, typename iterator_t>
	range<const T, iterator_t> find_last_of(range<const T, iterator_t> search_range, const T& val)
	{
		int length = search_range.length;
		for(int i = length - 1; i >= 0; --i)
		{
			iterator_t current_iter = search_range.iterator + i;
			if(*current_iter == val)
			{
				return make_range(current_iter, length - i);
			}
		}

		return make_null_range(search_range);
	}

	template<typename T, typename iterator_t>
	range<T, iterator_t> find_last_of(range<T, iterator_t> search_range, const T& val)
	{
		range<const T> result= find_last_of(range<const T>(search_range), val);
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}


	// ------------------------------
	// find any of those in a range

	template<typename T, typename iterator_t>
	range<const T, iterator_t> find_last_of(range<const T, iterator_t> search_range, range<const T> values)
	{
		int length = search_range.length;
		for(int i = length-1; i >= 0; --i)
		{
			iterator_t current_iter = search_range.iterator + i;
			typename range<const T>::iterator_type values_iter = values.iterator;
			for(int k = 0; k < values.length; ++k)
			{
				if(*current_iter == *values_iter)
				{
					return make_range(current_iter, length - i);
				}

				++values_iter;
			}	
		}

		return make_null_range(search_range);
	}

	// (const range, non-const range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> find_last_of(range<const T, iterator_t> search_range, range<T> values)
	{
		range<const T> result= find_last_of(search_range, range<const T>(values));
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}

	// (non-const range, const range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> find_last_of(range<T, iterator_t> search_range, range<const T> values)
	{
		range<const T> result= find_last_of(range<const T>(search_range), values);
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}

	// (non-const range, non_const range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> find_last_of(range<T, iterator_t> search_range, range<T> values)
	{
		range<const T> result= find_last_of(range<const T>(search_range), range<const T>(values));
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}


	// ------------------------------
	// find any of those in an array

	// (const range, const array)
	template<typename T, typename iterator_t, unsigned int arr_length>
	range<const T, iterator_t> find_last_of(range<const T, iterator_t> search_range, const T(&values)[arr_length])
	{		
		return nostl::find_last_of(search_range, make_range(values, arr_length));
	}

	// (non-const range, const array)
	template<typename T, typename iterator_t, unsigned int arr_length>
	range<T, iterator_t> find_last_of(range<T, iterator_t> search_range, const T(&values)[arr_length])
	{	
		range<const T> result= find_last_of(range<const T>(search_range), values);
		return make_range(const_cast<iterator_t>(result.iterator), result.length);
	}

}

#endif