#ifdef __INTELLISENSE__
	#include "static_array.h"
#endif

#include "algorithmz.h"

namespace z
{
	template<class T, unsigned int max_length>
	static_vector<T, max_length>::static_vector() :
		m_size(0)
	{
		
	}


	template<class T, unsigned int max_length>
	static_vector<T, max_length>::~static_vector()
	{
		
	}


	template<class T, unsigned int max_length>
	static_vector<T, max_length>::static_vector(const T* other_array, unsigned int size)
	{
		deep_copy(other_array, size);
	}


	template<class T, unsigned int max_length>
	static_vector<T, max_length>::static_vector(const static_vector& other)
	{
		deep_copy(other);
	}


	template<class T, unsigned int max_length>
	static_vector<T, max_length>::static_vector(static_vector&& other)
	{
		deep_copy(other);
		other.clear();
	}

		
	template<class T, unsigned int max_length>
	unsigned int static_vector<T, max_length>::size() const
	{
		return m_size;
	}


	template<class T, unsigned int max_length>
	unsigned int static_vector<T, max_length>::max_size() const
	{
		return max_length;
	}


	template<class T, unsigned int max_length>
	unsigned int static_vector<T, max_length>::size_remaining() const
	{
		return max_length - m_size;
	}


	template<class T, unsigned int max_length>
	bool static_vector<T, max_length>::is_empty() const
	{
		return size() == 0;
	}


	template<class T, unsigned int max_length>
	bool static_vector<T, max_length>::is_full() const
	{
		return size() > 0;
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::clear()
	{
		m_size = 0;
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::clear_zero()
	{
		clear();
		zero_array();
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::clear_reconstruct()
	{
		clear();
		reconstruct_array();
	}


	template<class T, unsigned int max_length>
	template<template<class, unsigned int> class array_type, unsigned int other_max_length>
	static_vector<T, max_length>& static_vector<T, max_length>::deep_copy(z::base_array<T, array_type<T, other_max_length>>& other)
	{
		// do not static_assert the max_lengths. other may have a larger capacity, but fewer elements.
		return deep_copy(other.internal_array(), other.size());
	}


	template<class T, unsigned int max_length>
	template<unsigned int array_size>
	static_vector<T, max_length>& static_vector<T, max_length>::deep_copy(const T (&other_array)[array_size])
	{
		z_static_assert(array_size <= max_length, "static_vector::deep_copy given array larger than capacity can hold.");
		return deep_copy(other_array, array_size);
	}


	template<class T, unsigned int max_length>
	static_vector<T, max_length>& static_vector<T, max_length>::deep_copy(const T* other_array, unsigned int size)
	{
		z_assert(size <= max_length);
		for(unsigned int i = 0; i < size; ++i)
		{
			m_data[i] = other_array[i];
		}

		m_size = size;

		return *this;
	}


	template<class T, unsigned int max_length>
	static_vector<T, max_length>& static_vector<T, max_length>::deep_copy(const static_vector& other)
	{
		const unsigned int size = other.size();

		for(unsigned int i = 0; i < size; ++i)
		{
			m_data[i] = other.m_data[i];
		}

		m_size = size;

		return *this;
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::reconstruct_element(unsigned int index)
	{
		m_data.reconstruct_element(index);
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::reconstruct_array()
	{
		m_data.reconstruct_array();
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::zero_array()
	{
		m_data.zero_array();
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::get(unsigned int index)
	{
		return m_data.get(index);
	}


	template<class T, unsigned int max_length>
	const T& static_vector<T, max_length>::get(unsigned int index) const
	{
		return m_data.get(index);
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::operator[](unsigned int index)
	{
		return m_data[index];
	}


	template<class T, unsigned int max_length>
	const T& static_vector<T, max_length>::operator[](unsigned int index) const
	{
		return m_data[index];
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::first()
	{
		return m_data.first();
	}


	template<class T, unsigned int max_length>
	const T& static_vector<T, max_length>::first() const
	{
		return m_data.first();
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::last()
	{
		return m_data.last();
	}


	template<class T, unsigned int max_length>
	const T& static_vector<T, max_length>::last() const
	{
		return m_data.last();
	}


	template<class T, unsigned int max_length>
	range<T> static_vector<T, max_length>::get_range()
	{
		return m_data.get_range(0, size()-1);
	}


	template<class T, unsigned int max_length>
	range<const T> static_vector<T, max_length>::get_range() const
	{
		return m_data.get_range(0, size()-1);
	}


	template<class T, unsigned int max_length>
	range<T> static_vector<T, max_length>::get_range(unsigned int index)
	{
		z_assert(index < size());
		return m_data.get_range(index, size()-1);
	}


	template<class T, unsigned int max_length>
	range<const T> static_vector<T, max_length>::get_range(unsigned int index) const
	{
		z_assert(index < size());
		return m_data.get_range(index, size()-1);
	}


	template<class T, unsigned int max_length>
	range<T> static_vector<T, max_length>::get_range(unsigned int start_index, unsigned int end_index)
	{
		z_assert(start_index < size());
		z_assert(start_index <= end_index);
		z_assert(end_index < size());
		return m_data.get_range(start_index, end_index);
	}


	template<class T, unsigned int max_length>
	range<const T> static_vector<T, max_length>::get_range(unsigned int start_index, unsigned int end_index) const
	{
		z_assert(start_index < size());
		z_assert(start_index <= end_index);
		z_assert(end_index < size());
		return m_data.get_range(start_index, end_index);
	}


	template<class T, unsigned int max_length>
	T* static_vector<T, max_length>::internal_array()
	{
		return m_data.internal_array();
	}


	template<class T, unsigned int max_length>
	const T* static_vector<T, max_length>::internal_array() const
	{
		return m_data.internal_array();
	}

	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::new_element_raw()
	{
		const unsigned int new_index = size();
		z_assert(new_index < max_size());

		T* element = &m_data[new_index];

		++m_size;

		return *element;
	}

	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::new_element()
	{
		T* element = &new_element_raw();
		new (element) T();
		return *element;
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::new_element(const T& copy)
	{
		T* element = &new_element_raw();
		new (element) T(copy);
		return *element;
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::new_element(const T&& move_copy)
	{
		T* element = &new_element_raw();
		new (element) T(move_copy);
		return *element;
	}

	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::insert_element_raw(unsigned int index)
	{
		z_assert(index < max_length);
		z_assert(size() < max_length);

		T* m_data_array = m_data.internal_array();
		T* space_location = m_data_array + index;
		T* end_location = m_data_array + m_data.max_size();

		z::move(space_location, end_location - 1, space_location + 1); // shift elements right at index

		++m_size;

		return *space_location;
	}

	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::insert_element(unsigned int index)
	{
		T* element = &insert_element_raw(index);
		new (element) T();
		return *element;
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::insert_element(unsigned int index, const T& copy)
	{
		T* element = &insert_element_raw(index);
		new (element) T(copy);
		return *element;
	}


	template<class T, unsigned int max_length>
	T& static_vector<T, max_length>::insert_element(unsigned int index, const T&& move_copy)
	{
		T* element = &insert_element_raw(index);
		new (element) T(move_copy);
		return *element;
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::remove(unsigned int index)
	{
		z_assert(index < size());
		z_assert(size() > 0);

		T* m_data_array = m_data.internal_array();
		T* space_location = m_data_array + index;
		T* end_location = m_data_array + m_data.max_size();

		z::move(space_location + 1, end_location, space_location); // shift elements left at index

		--m_size;
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::remove_first()
	{
		remove(0);
	}


	template<class T, unsigned int max_length>
	void static_vector<T, max_length>::remove_last()
	{
		--m_size;
	}

}