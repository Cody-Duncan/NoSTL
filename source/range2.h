/*
Author: Cody Duncan
Date: November 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef RANGE2_H
#define RANGE2_H

// ---------- includes ---------

#include <type_traits>
#include <iterator>

#include "range_forward_declarations.h"
#include "view_interface.h"

namespace nostl
{
	template<typename I, typename S /* = I */>
	struct range : 
		view_interface < range<I, S> >
	{
		using iterator = I;
		using sentinel = S;

		iterator first;
		sentinel second;
		
		range() = default;
		range(iterator begin, sentinel end) : 
			first(std::move(begin)),
			second(std::move(end))
		{}

		template<typename X, typename Y>
        range(range<X, Y> rng) : 
			first(rng.first), 
			second(rng.second)
        {}

		iterator begin() const
		{
			return first;
		}
		sentinel end() const
		{
			return second;
		}

		void pop_front()
		{
			++first;
		}

		void pop_back()
		{
			--second;
		}
	};

	template <typename I, typename S>
	range<I, S> make_range(I&& begin, S&& end)
	{
		return range<I, S>(begin, end);
	}
	
	template <typename Container>
	auto make_range_from_container(Container&& arg) ->
		decltype(make_range(arg.begin(), arg.end()))
	{
		return make_range(arg.begin(), arg.end());
	}

	template <typename T, unsigned int arr_length>
	range<T*> make_range_from_array(T(&values)[arr_length])
	{
		return make_range(values+0, values+arr_length);
	}
}

#endif