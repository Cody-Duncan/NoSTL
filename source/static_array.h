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

		derived& get_self() const
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

	template<class T, unsigned int max_length>
	struct static_array : protected base_array<T, static_array<T, max_length>>
	{
	public:
		static_array();
		~static_array();

		static_array(const T*, unsigned int size);
		static_array(const static_array&);
		static_array(static_array&&);

		static_array& operator=(const static_array&) = delete;
		
		unsigned int size() const;
		unsigned int max_size() const;

		template<unsigned int array_size>
		static_array& deep_copy(const T (&)[array_size]);
		static_array& deep_copy(const T*, unsigned int size);
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

	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array()
	{}
	
	template<class T, unsigned int max_length>
	static_array<T, max_length>::~static_array()
	{}

	
	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array(const T* other_array, unsigned int size)
	{
		deep_copy(other_array, size);
	}

	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array(const static_array& other)
	{
		deep_copy(other);
	}
	
	template<class T, unsigned int max_length>
	static_array<T, max_length>::static_array(static_array&& other)
	{
		deep_copy(other);
		other.reconstruct_array();
	}
	
	template<class T, unsigned int max_length>
	unsigned int static_array<T, max_length>::size() const
	{
		return max_length;
	}
	
	template<class T, unsigned int max_length>
	unsigned int static_array<T, max_length>::max_size() const
	{
		return max_length;
	}

	template<class T, unsigned int max_length>
	template<unsigned int array_size>
	static_array<T, max_length>& static_array<T, max_length>::deep_copy(const T (&other_array)[array_size])
	{
		z_assert(array_size <= max_length);
		for(unsigned int i = 0; i < array_size; ++i)
		{
			m_data[i] = other_array[i];
		}
		return *this;
	}

	template<class T, unsigned int max_length>
	static_array<T, max_length>& static_array<T, max_length>::deep_copy(const T* other_array, unsigned int size)
	{
		z_assert(size <= max_length);
		for(unsigned int i = 0; i < size; ++i)
		{
			m_data[i] = other_array[i];
		}

		return *this;
	}

	template<class T, unsigned int max_length>
	static_array<T, max_length>& static_array<T, max_length>::deep_copy(const static_array& other)
	{
		for(unsigned int i = 0; i < max_length; ++i)
		{
			m_data[i] = other.m_data[i];
		}
		return *this;
	}
	
	template<class T, unsigned int max_length>
	void static_array<T, max_length>::reconstruct_element(unsigned int index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);
		new (m_data + index) T();
	}

	template<class T, unsigned int max_length>
	void static_array<T, max_length>::reconstruct_array()
	{
		for(unsigned int i = 0; i < max_length; ++i)
		{
			reconstruct_element(i);
		}
	}

	template<class T, unsigned int max_length>
	void static_array<T, max_length>::zero_array()
	{
		memset(&m_data, 0, sizeof(m_data));
	}

	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::get(unsigned int index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::get(unsigned int index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::operator[](unsigned int index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::operator[](unsigned int index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::first()
	{
		return m_data[0];
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::first() const
	{
		return m_data[0];
	}

	
	template<class T, unsigned int max_length>
	T& static_array<T, max_length>::last()
	{
		return m_data[max_length-1];
	}
	
	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::last() const
	{
		return m_data[max_length-1];
	}
	
	template<class T, unsigned int max_length>
	range<T> static_array<T, max_length>::get_range()
	{
		return make_range<T>(m_data, max_length);
	}

	template<class T, unsigned int max_length>
	range<const T> static_array<T, max_length>::get_range() const
	{
		return make_range<const T>(m_data, max_length);
	}

	template<class T, unsigned int max_length>
	range<T> static_array<T, max_length>::get_range(unsigned int index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return make_range<T>((m_data + index), max_length-index);
	}

	template<class T, unsigned int max_length>
	range<const T> static_array<T, max_length>::get_range(unsigned int index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return make_range<const T>((m_data + index), max_length-index);
	}

	template<class T, unsigned int max_length>
	range<T> static_array<T, max_length>::get_range(unsigned int start_index, unsigned int end_index)
	{
		z_assert(start_index >= 0);
		z_assert(start_index <= end_index);
		z_assert(end_index < max_length);

		return make_range<T>((m_data + start_index), end_index - start_index);
	}

	template<class T, unsigned int max_length>
	range<const T> static_array<T, max_length>::get_range(unsigned int start_index, unsigned int end_index) const
	{
		z_assert(start_index >= 0);
		z_assert(start_index <= end_index);
		z_assert(end_index < max_length);

		return make_range<const T>((m_data + start_index), end_index - start_index);
	}

	template<class T, unsigned int max_length>
	T* static_array<T, max_length>::internal_array()
	{
		return m_data;
	}

	template<class T, unsigned int max_length>
	const T* static_array<T, max_length>::internal_array() const
	{
		return m_data;
	}

	namespace test
	{
		void test_static_array();
	}
}

#endif