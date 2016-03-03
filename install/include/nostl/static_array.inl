#ifdef __INTELLISENSE__
#include "static_array.h"
#endif

namespace nostl
{
	template <class T, uint max_length>
	static_array<T, max_length>::static_array()
	{
	}

	template <class T, uint max_length>
	static_array<T, max_length>::~static_array()
	{
	}

	template <class T, uint max_length>
	static_array<T, max_length>::static_array(const T *other_array, uint size)
	{
		deep_copy(other_array, size);
	}

	template <class T, uint max_length>
	static_array<T, max_length>::static_array(range<T*> &r)
	{
		deep_copy(r);
	}

	template <class T, uint max_length>
	static_array<T, max_length>::static_array(const static_array &other)
	{
		deep_copy(other);
	}

	template <class T, uint max_length>
	static_array<T, max_length>::static_array(static_array &&other)
	{
		deep_copy(other);
		other.reconstruct_array();
	}

	template <class T, uint max_length>
	uint static_array<T, max_length>::size() const
	{
		return max_length;
	}

	template <class T, uint max_length>
	uint static_array<T, max_length>::max_size() const
	{
		return max_length;
	}

	template <class T, uint max_length>
	bool static_array<T, max_length>::is_empty() const
	{
		return size() == 0;
	}

	template <class T, uint max_length>
	bool static_array<T, max_length>::is_full() const
	{
		return size() == max_length;
	}

	template <class T, uint max_length>
	template <template <class, uint> class array_type, uint other_max_length>
	static_array<T, max_length> &static_array<T, max_length>::deep_copy(nostl::base_array<T, array_type<T, other_max_length>> &other)
	{
		// do not static_assert the max_lengths. other may have a larger capacity, but fewer elements.
		return deep_copy(other.internal_array(), other.size());
	}

	template <class T, uint max_length>
	template <uint array_size>
	static_array<T, max_length> &static_array<T, max_length>::deep_copy(const T(&other_array)[array_size])
	{
		z_static_assert(array_size <= max_length, "static_array::deep_copy given array larger than capacity can hold.");
		return deep_copy(other_array, array_size);
	}

	template <class T, uint max_length>
	static_array<T, max_length> &static_array<T, max_length>::deep_copy(const T *other_array, uint size)
	{
		z_assert(size <= max_length);
		for(uint i = 0; i < size; ++i)
		{
			m_data[i] = other_array[i];
		}

		return *this;
	}

	template <class T, uint max_length>
	static_array<T, max_length> &static_array<T, max_length>::deep_copy(range<T*> &r)
	{
		range<T*> new_r = r;
		range<T*> current_r = get_range();
		for(; new_r.is_valid(); r.pop_front(), current_r.pop_front())
		{
			current_r.get_element() = r.get_element();
		}

		return *this;
	}

	template <class T, uint max_length>
	static_array<T, max_length> &static_array<T, max_length>::deep_copy(const static_array &other)
	{
		for(uint i = 0; i < max_length; ++i)
		{
			m_data[i] = other.m_data[i];
		}
		return *this;
	}

	template <class T, uint max_length>
	void static_array<T, max_length>::reconstruct_element(uint index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);
		new(m_data + index) T();
	}

	template <class T, uint max_length>
	void static_array<T, max_length>::reconstruct_array()
	{
		for(uint i = 0; i < max_length; ++i)
		{
			reconstruct_element(i);
		}
	}

	template <class T, uint max_length>
	void static_array<T, max_length>::zero_array()
	{
		memset(&m_data, 0, sizeof(m_data));
	}

	template <class T, uint max_length>
	T &static_array<T, max_length>::get(uint index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}

	template <class T, uint max_length>
	const T &static_array<T, max_length>::get(uint index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}


	template <class T, uint max_length>
	T &static_array<T, max_length>::operator[](uint index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}

	template <class T, uint max_length>
	const T &static_array<T, max_length>::operator[](uint index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return m_data[index];
	}


	template <class T, uint max_length>
	T &static_array<T, max_length>::first()
	{
		return m_data[0];
	}

	template <class T, uint max_length>
	const T &static_array<T, max_length>::first() const
	{
		return m_data[0];
	}


	template <class T, uint max_length>
	T &static_array<T, max_length>::last()
	{
		return m_data[max_length - 1];
	}

	template <class T, uint max_length>
	const T &static_array<T, max_length>::last() const
	{
		return m_data[max_length - 1];
	}

	template <class T, uint max_length>
	T* static_array<T, max_length>::begin()
	{
		return m_data;
	}

	template <class T, uint max_length>
	const T *static_array<T, max_length>::begin() const
	{
		return m_data;
	}

	template <class T, uint max_length>
	T *static_array<T, max_length>::end()
	{
		return m_data + max_length;
	}

	template <class T, uint max_length>
	const T *static_array<T, max_length>::end() const
	{
		return m_data + max_length;
	}

	template <class T, uint max_length>
	range<typename static_array<T, max_length>::iterator> static_array<T, max_length>::get_range()
	{
		return make_range_from_container(*this);
	}

	template <class T, uint max_length>
	range<typename static_array<T, max_length>::const_iterator> static_array<T, max_length>::get_range() const
	{
		return make_range_from_container(*this);
	}

	template <class T, uint max_length>
	range<typename static_array<T, max_length>::iterator> static_array<T, max_length>::get_range(uint index)
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return make_range((begin() + index), end());
	}

	template <class T, uint max_length>
	range<typename static_array<T, max_length>::const_iterator> static_array<T, max_length>::get_range(uint index) const
	{
		z_assert(index >= 0);
		z_assert(index < max_length);

		return make_range((begin() + index), end());
	}

	template <class T, uint max_length>
	range<typename static_array<T, max_length>::iterator> static_array<T, max_length>::get_range(uint start_index, uint end_index)
	{
		z_assert(start_index >= 0);
		z_assert(start_index <= end_index);
		z_assert(end_index <= max_length);

		return make_range((begin() + start_index), (begin() + end_index));
	}

	template <class T, uint max_length>
	range<typename static_array<T, max_length>::const_iterator> static_array<T, max_length>::get_range(uint start_index, uint end_index) const
	{
		z_assert(start_index >= 0);
		z_assert(start_index <= end_index);
		z_assert(end_index <= max_length);

		return make_range((begin() + start_index), (begin() + end_index));
	}

	template <class T, uint max_length>
	T *static_array<T, max_length>::internal_array()
	{
		return m_data;
	}

	template <class T, uint max_length>
	const T *static_array<T, max_length>::internal_array() const
	{
		return m_data;
	}
}