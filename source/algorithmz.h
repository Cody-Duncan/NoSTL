/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef ALGORITHMZ_H
#define ALGORITHMZ_H

// ---------- includes ---------
#include <type_traits>
#include "range.h"
#include "range_algorithms.h"

namespace z
{
	// ******************** move ********************

	template<class input_iter, class output_iter>
	typename std::enable_if<!std::is_fundamental<output_iter>::value, output_iter>::type 
		move(input_iter first, input_iter last, output_iter d_first)
	{
		while (first != last) 
		{
			*d_first++ = std::move(*first++);
		}
		return d_first;
	}

	template<class T>
	typename std::enable_if<!std::is_fundamental<T>::value, T*>::type
		move(T* first, T* last, T* d_first)
	{
		while (first != last) 
		{
			*d_first++ = std::move(*first++);
		}
		return d_first;
	}

	template<class T>
	typename std::enable_if<std::is_fundamental<T>::value, T*>::type
		move(T* first, T* last, T* d_first)
	{
		unsigned int num = last - first;
		return (T*) memmove(d_first, first, num * sizeof(T));
	}

}

#endif