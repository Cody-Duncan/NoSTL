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
#include "range.h"
#include "z_assert.h"

#include "base_array.h"

// ---------- definitions ----------

namespace z
{
	

	template<class T, unsigned int max_length>
	struct static_array : protected base_array<T, static_array<T, max_length>>
	{
	public:
		static_array();
		~static_array();

		static_array(const T*, unsigned int size);
		static_array(range<T>&);
		static_array(const static_array&);
		static_array(static_array&&);

		//operator= , compiler generated
		
		unsigned int size() const;
		unsigned int max_size() const;
		bool is_empty() const;
		bool is_full() const;

		template<template<class, unsigned int> class array_type, unsigned int other_max_length>
		static_array& deep_copy(z::base_array<T, array_type<T, other_max_length>>& other);

		template<unsigned int array_size>
		static_array& deep_copy(const T (&)[array_size]);

		static_array& deep_copy(const T*, unsigned int size);
		static_array& deep_copy(range<T>&);
		static_array& deep_copy(const static_array&);

		void reconstruct_element(unsigned int index);
		void reconstruct_array();
		void zero_array();

		T& get(unsigned int index);
		const T& get(unsigned int index) const;

		T& operator[]( unsigned int index );
		const T& operator[]( unsigned int index ) const;

		T& first();
		const T& first() const;

		T& last();
		const T& last() const;

		T* end();
		const T* end() const;

		range<T> get_range();
		range<const T> get_range() const;
		range<T> get_range(unsigned int index);
		range<const T> get_range(unsigned int index) const;
		range<T> get_range(unsigned int start_index, unsigned int end_index);
		range<const T> get_range(unsigned int start_index, unsigned int end_index) const;

		T* internal_array();
		const T* internal_array() const;

	private:
		T m_data[max_length];
	};	
}

#include "static_array.inl"

// --------- testing functions --------

namespace z
{
	namespace test
	{
		void test_static_array();
	}
}

#endif