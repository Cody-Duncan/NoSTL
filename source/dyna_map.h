/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef DYNA_MAP_H
#define DYNA_MAP_H

// ---------- includes ---------
#include <unordered_map>

namespace z
{
	template<typename Key_t, typename Value_t>
	using dyna_map = std::unordered_map<Key_t, Value_t>;
}

#endif