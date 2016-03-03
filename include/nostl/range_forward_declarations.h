/*
Author: Cody Duncan
Date: November 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef RANGE_FORWARD_DECLARATIONS_H
#define RANGE_FORWARD_DECLARATIONS_H

// ---------- includes ---------

#include <type_traits>
#include <iterator>

namespace nostl
{
	enum cardinality
    {
        infinite = -3,
        unknown = -2,
        finite = -1,
        _max_ = INT_MAX
    };

	struct view_base
    {};

	template<cardinality>
    struct basic_view : view_base
    {};

	template<typename Derived, cardinality = finite>
    struct view_interface;

	template<typename I, typename S = I>
    struct range;

	using range_size_t = std::make_unsigned<int>;

}

#endif