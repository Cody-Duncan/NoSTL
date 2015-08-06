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

namespace z
{
	template<class T, unsigned int max_length>
	struct static_array
	{
	public:
		T data[max_length];

		static_array();
		~static_array();

		static_array(const static_array&);
		static_array(const static_array&&);

		static_array& operator=(const static_array&) = delete;

		unsigned int size() const;
		unsigned int max_size() const;
		bool is_empty() const;
		bool is_full() const;

		void clear();

		T& get(unsigned int index);
		const T& get(unsigned int index) const;

		T& operator[]( unsigned int pos );
		const T& operator[]( unsigned int pos ) const;

		T& first(unsigned int index);
		const T& first(unsigned int index) const;

		T& last(unsigned int index);
		const T& last(unsigned int index) const;

		range<T> get_range();

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

		void static_array::zero_array();
	};

	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array()
	{
		
	}
	
	template<class T, unsigned int max_length>
	static_array<T, max_length>::~static_array()
	{
		
	}

	
	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array(const static_array&)
	{
		
	}
	
	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array(const static_array&&)
	{
		
	}
	
	template<class T, unsigned int max_length>
	unsigned int static_array<T, max_length>::size() const
	{
		
	}
	
	template<class T, unsigned int max_length>
	unsigned int static_array<T, max_length>::max_size() const
	{
		
	}
	
	template<class T, unsigned int max_length>
	bool static_array<T, max_length>::is_empty() const
	{
		
	}
	
	template<class T, unsigned int max_length>
	bool static_array<T, max_length>::is_full() const
	{
		
	}

	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::clear()
	{
		
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::get(unsigned int index)
	{
		
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::get(unsigned int index) const
	{
		
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::operator[]( unsigned int pos )
	{
		
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::operator[]( unsigned int pos ) const
	{
		
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::first(unsigned int index)
	{
		
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::first(unsigned int index) const
	{
		
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::last(unsigned int index)
	{
		
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::last(unsigned int index) const
	{
		
	}

	
	template<class T, unsigned int max_length>
	range<T> static_array<T, max_length>::get_range()
	{
		return make_range<T>(data, m_size);
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::new_element()
	{
		
	}
	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::new_element(const T& copy)
	{
		
	}
	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::new_element(const T&& move_copy)
	{
		
	}

	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::insert_element(unsigned int index)
	{
		
	}
	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::insert_element(unsigned int index, const T& copy)
	{
		
	}
	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::insert_element(unsigned int index, const T&& move_copy)
	{
		
	}

	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::remove(unsigned int index)
	{
		
	}
	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::remove_last(unsigned int index)
	{
		
	}

	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::zero_array()
	{
		
	}

}

#endif