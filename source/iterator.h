/*
Author: Cody Duncan
Date: November 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef ITERATOR_UTIL_H
#define ITERATOR_UTIL_H

// ---------- includes ---------

namespace nostl
{
	template<typename I>
	using iterator_size_t = unsigned int;

	template<typename I, typename S>
    iterator_size_t<I> iter_size(I begin, S end)
    {
        //RANGES_ASSERT(0 <= (end - begin));
        return static_cast<iterator_size_t<I>>(end - begin);
    }
}

#endif