#ifdef __INTELLISENSE__
	#include "static_array.h"
#endif

namespace z
{
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
	static_array<T, max_length>::static_array(range<T>& r)
	{
		deep_copy(r);
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
	template<template<class, unsigned int> class array_type, unsigned int other_max_length>
	static_array<T, max_length>& static_array<T, max_length>::deep_copy(z::base_array<T, array_type<T, other_max_length>>& other)
	{
		// do not static_assert the max_lengths. other may have a larger capacity, but fewer elements.
		return deep_copy(other.internal_array(), other.size());
	}

	template<class T, unsigned int max_length>
	template<unsigned int array_size>
	static_array<T, max_length>& static_array<T, max_length>::deep_copy(const T(&other_array)[array_size])
	{
		z_static_assert(array_size <= max_length, "static_array::deep_copy given array larger than capacity can hold.");
		return deep_copy(other_array, array_size);
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
	static_array<T, max_length>& static_array<T, max_length>::deep_copy(range<T>& r)
	{
		z_assert(r.length <= max_length);
		
		int length = r.length;
		for(int i = 0; i < length; ++i)
		{
			m_data[i] = r.get_element();
			++r;
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
		return m_data[max_length - 1];
	}

	template<class T, unsigned int max_length>
	const T& static_array<T, max_length>::last() const
	{
		return m_data[max_length - 1];
	}

	template<class T, unsigned int max_length>
	T* static_array<T, max_length>::end()
	{
		return m_data + max_length;
	}

	template<class T, unsigned int max_length>
	const T* static_array<T, max_length>::end() const
	{
		return m_data + max_length;
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

		return make_range<T>((m_data + index), max_length);
	}

	template<class T, unsigned int max_length>
	range<const T> static_array<T, max_length>::get_range(unsigned int index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return make_range<const T>((m_data + index), max_length);
	}

	template<class T, unsigned int max_length>
	range<T> static_array<T, max_length>::get_range(unsigned int start_index, unsigned int end_index)
	{
		z_assert(start_index >= 0);
		z_assert(start_index <= end_index);
		z_assert(end_index <= max_length);

		return make_range<T>((m_data + start_index), end_index - start_index);
	}

	template<class T, unsigned int max_length>
	range<const T> static_array<T, max_length>::get_range(unsigned int start_index, unsigned int end_index) const
	{
		z_assert(start_index >= 0);
		z_assert(start_index <= end_index);
		z_assert(end_index <= max_length);

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
}