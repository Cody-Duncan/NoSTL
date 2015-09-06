/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

// ---------- includes ---------
#include "z_primitives.h"
#include "range.h"
#include "z_assert.h"

#include "base_array.h"
#include "static_array.h"

namespace z
{
	template<class T, uint max_length>
	struct static_vector
	{
	public:
		static_vector();
		~static_vector();

		static_vector(const T*, uint size);
		static_vector(const static_vector&);
		static_vector(static_vector&&);

		//operator=, compiler generated
		
		uint size() const;
		uint max_size() const;
		uint size_remaining() const;
		bool is_empty() const;
		bool is_full() const;

		void clear();
		void clear_zero();
		void clear_reconstruct();

		template<template<class, uint> class array_type, uint other_max_length>
		static_vector& deep_copy(z::base_array<T, array_type<T, other_max_length>>& other);

		template<uint array_size>
		static_vector& deep_copy(const T (&)[array_size]);

		static_vector& deep_copy(const T*, uint size);
		static_vector& deep_copy(const static_vector&);

		void reconstruct_element(uint index);
		void reconstruct_array();
		void zero_array();

		T& get(uint index);
		const T& get(uint index) const;

		T& operator[](uint index);
		const T& operator[](uint index) const;

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

		T& new_element_raw();
		T& new_element();
		T& new_element(const T& copy);
		T& new_element(const T&& move_copy);

		T& insert_element_raw(uint index);
		T& insert_element(uint index);
		T& insert_element(uint index, const T& copy);
		T& insert_element(uint index, const T&& move_copy);

		void remove(uint index);
		void remove(uint start_index, uint end_index);
		void remove_first();
		void remove_last();

	private:
		uint m_size;
		static_array<T, max_length> m_data;
	};
}

#include "static_vector.inl"

// --------- testing functions --------

namespace z
{
	namespace test
	{
		void test_static_vector();
	}
}

#endif