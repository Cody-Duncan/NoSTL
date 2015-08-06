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
		void zero_array();
	};
}

#endif