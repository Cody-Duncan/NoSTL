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
#include "base_array.h"
#include <functional> // std::Hash, std::equal_to

namespace nostl
{
	template <class Key, class Value, uint max_length, typename Hash = std::hash<Key>, typename Equality = std::equal_to<Key>>
	class static_map : protected base_array<T, static_map<Key, Value, max_length, Hash, Equality>>
	{
	public:
		static_map() = default;

		
	};
}

#endif