
/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:
	A shim for getting some types implemented using stl for now.
	MUST BE REPLACED OVER TIME

*/

#pragma once

#ifndef Z_STL_SHIM_H
#define Z_STL_SHIM_H

// ---------- includes ---------

#include <array>
#include <vector>
#include <unordered_map>
#include "static_string.h"

namespace z
{
	template<typename T, unsigned int L> 
	using static_array = std::array<T, L>;

	template<typename T>
	using dyna_array = std::vector<T>;

	template<class K, class T>
	using dyna_map = std::unordered_map<K,T>;
}

#define Zero_Struct(s) memset(&s, 0, sizeof(s));

#endif