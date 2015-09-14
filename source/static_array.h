/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

// ---------- includes ---------
#include "primitives.h"
#include "range.h"
#include "assert.h"

#include "base_array.h"

// ---------- definitions ----------

namespace nostl
{
	

	template<class T, uint max_length>
	struct static_array : protected base_array<T, static_array<T, max_length>>
	{
	public:
		static_array();
		~static_array();

		static_array(const T*, uint size);
		static_array(range<T>&);
		static_array(const static_array&);
		static_array(static_array&&);

		//operator= , compiler generated
		
		uint size() const;
		uint max_size() const;
		bool is_empty() const;
		bool is_full() const;

		template<template<class, uint> class array_type, uint other_max_length>
		static_array& deep_copy(nostl::base_array<T, array_type<T, other_max_length>>& other);

		template<uint array_size>
		static_array& deep_copy(const T (&)[array_size]);

		static_array& deep_copy(const T*, uint size);
		static_array& deep_copy(range<T>&);
		static_array& deep_copy(const static_array&);

		void reconstruct_element(uint index);
		void reconstruct_array();
		void zero_array();

		T& get(uint index);
		const T& get(uint index) const;

		T& operator[]( uint index );
		const T& operator[]( uint index ) const;

		T& first();
		const T& first() const;

		T& last();
		const T& last() const;

		T* end();
		const T* end() const;

		range<T> get_range();
		range<const T> get_range() const;
		range<T> get_range(uint index);
		range<const T> get_range(uint index) const;
		range<T> get_range(uint start_index, uint end_index);
		range<const T> get_range(uint start_index, uint end_index) const;

		T* internal_array();
		const T* internal_array() const;

	private:
		T m_data[max_length];
	};	
}

#include "static_array.inl"

// --------- testing functions --------

namespace nostl
{
	namespace test
	{
		void test_static_array();
	}
}

#endif