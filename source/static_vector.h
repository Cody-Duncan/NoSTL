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
#include "static_array.h"

namespace z
{
	template<class T, unsigned int max_length>
	struct static_vector
	{
	public:
		static_vector();
		~static_vector();

		static_vector(const static_array&);
		static_vector(const static_array&&);

		static_vector& operator=(const static_vector&) = delete;

		unsigned int size() const;
		unsigned int max_size() const;
		bool is_empty() const;
		bool is_full() const;

		void clear();
		void clear_zero();

		void reconstruct_element(unsigned int index);		

		T& get(unsigned int index);
		const T& get(unsigned int index) const;

		T& operator[](unsigned int pos);
		const T& operator[](unsigned int pos) const;

		T& first(unsigned int index);
		const T& first(unsigned int index) const;

		T& last(unsigned int index);
		const T& last(unsigned int index) const;

		range<T> get_range();
		range<const T> get_range() const;
		range<T> get_range(unsigned int index);
		range<const T> get_range(unsigned int index) const;

		T* internal_array();
		const T* internal_array() const;

		T& new_element();
		T& new_element(const T& copy);
		T& new_element(const T&& move_copy);

		void insert_element(unsigned int index);
		void insert_element(unsigned int index, const T& copy);
		void insert_element(unsigned int index, const T&& move_copy);

		void remove(unsigned int index);
		void remove_last(unsigned int index);

	private:
		unsigned int m_size;
		static_array<T, max_length> m_data;
	};
}

#endif