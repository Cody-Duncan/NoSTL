/*
Author: Cody Duncan
Date: August 15, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef BASE_ARRAY_H
#define BASE_ARRAY_H

// ---------- includes ---------

// ---------- definitions ----------

namespace z
{
	template<typename T, typename derived>
	struct base_array
	{
	public:
		derived& get_self()
		{
			return (*static_cast<derived *>(this));
		}

		const derived& get_self() const
		{
			return (*static_cast<const derived *>(this));
		}

		unsigned int size() const
		{
			return get_self().size();
		}

		unsigned int max_size() const
		{
			return get_self().max_size();
		}

		T* internal_array()
		{
			return get_self().internal_array();
		}

		const T* internal_array() const
		{
			return get_self().internal_array();
		}
	};
}

#endif