#ifdef __INTELLISENSE__
	#include "static_string.h"
#endif

#include <string.h>

namespace z
{
	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string()
	{
		clear_zero();
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string(const char* other)
	{
		clear_zero();
		append(other);
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string(const char* other, unsigned int length)
	{
		z_assert(length <= str_max_length-1);
		clear_zero();
		append(other, length);
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string(const static_string& other)
	{
		clear_zero();
		append(other);
	}

	template<unsigned int str_max_length>
	template<unsigned int str_length>
	static_string<str_max_length>::static_string(const char (&other)[str_length])
	{
		//this could be static_assert, but reporting doesn't show what declaration broke it.
		z_assert(str_length <= str_max_length-1);
		clear_zero();
		append(other, str_length);
	}

	template<unsigned int str_max_length>
	template<typename T>
	static_string<str_max_length>::static_string(const base_string<T>& other)
	{
		z_assert(other.max_size() <= str_max_length-1);
		clear_zero();
		append(other);
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::operator=(const static_string<str_max_length> &other) const
	{
		clear_zero();
		append(other);
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::operator==(const static_string<str_max_length> &other) const
	{
		return strcmp(m_str.internal_array(), other.m_str.internal_array()) == 0;
	}

	template<unsigned int str_max_length>
	unsigned int static_string<str_max_length>::size() const
	{
		return m_str.size();
	}

	template<unsigned int str_max_length>
	unsigned int static_string<str_max_length>::max_size() const
	{
		return m_str.max_size();
	}

	template<unsigned int str_max_length>
	unsigned int static_string<str_max_length>::max_str_size() const
	{
		return m_str.max_size()-1;
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::is_empty() const
	{
		return m_str.is_empty();
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::is_full() const
	{
		return m_str.is_full();
	}

	template<unsigned int str_max_length>
	void static_string<str_max_length>::clear()
	{
		return m_str.clear();
	}

	template<unsigned int str_max_length>
	void static_string<str_max_length>::clear_zero()
	{
		m_str.clear_zero();
	}

	template<unsigned int str_max_length>
	template<template<unsigned int> class str_type, unsigned int other_max_length>
	static_string<str_max_length>& static_string<str_max_length>::deep_copy(z::base_string<str_type<other_max_length>>& other)
	{
		m_str.deep_copy(other.c_str(), other.size());
		return *this;
	}

	template<unsigned int str_max_length>
	template<unsigned int array_size>
	static_string<str_max_length>& static_string<str_max_length>::deep_copy(const char(&other)[array_size])
	{
		z_assert(array_size <= str_max_length);
		m_str.deep_copy(other);
		m_str.remove_last(); //do not include null terminator in size
		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::deep_copy(const char* other_array, unsigned int size)
	{
		z_assert(size < str_max_length);
		m_str.deep_copy(other_array, size);
		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::deep_copy(const static_string<str_max_length>& other)
	{
		z_assert(other.size() < str_max_length);
		m_str.deep_copy(other.m_str);
		return *this;
	}

	template<unsigned int str_max_length>
	char& static_string<str_max_length>::get(unsigned int pos)
	{
		return const_cast<char&>(const_cast<const static_string<str_max_length>*>(this)->get(pos));
	}

	template<unsigned int str_max_length>
	const char& static_string<str_max_length>::get(unsigned int pos) const
	{
		z_assert(pos >= 0 && pos < size());
		return m_str[pos];
	}

	template<unsigned int str_max_length>
	char& static_string<str_max_length>::operator[] (unsigned int pos)
	{
		return const_cast<char&>(const_cast<const static_string<str_max_length>*>(this)->operator[](pos));
	}

	template<unsigned int str_max_length>
	const char& static_string<str_max_length>::operator[] (unsigned int pos) const
	{
		return m_str[pos];
	}

	template<unsigned int str_max_length>
	template<typename T>
	static_string<str_max_length>& static_string<str_max_length>::append(const base_string<T>& s)
	{
		z_assert((size() + s.size()) <= max_str_size());
		append(s.c_str(), s.size());

		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::append(const char* s)
	{
		int append_size = 0;
		const char* temp = s;

		while(*temp != '\0' && (size() + append_size) <= max_size())
		{
			++append_size;
			++temp;
		}

		z_assert((size() + append_size) <= max_str_size());
		append(s, append_size);

		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::append(const char* s, unsigned int n)
	{
		z_assert(n <= (max_str_size() - size()));

		for(unsigned int i = 0; i < n; ++i)
		{
			m_str.new_element(*s);
			++s;
		}

		printf("%s %d", s, n);

		m_str[m_str.size()] = '\0';

		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::fill(char c, unsigned int n)
	{
		z_assert(n <= max_size());

		clear_zero();
		for(int i = 0; i < n; ++i)
		{
			m_str.new_element(c);
		}

		return *this;
	}

	template<unsigned int str_max_length>
	char* static_string<str_max_length>::begin()
	{
		return const_cast<char*>(const_cast<const static_string<str_max_length>*>(this)->begin());
	}

	template<unsigned int str_max_length>
	const char* static_string<str_max_length>::begin() const
	{
		return c_str();
	}

	template<unsigned int str_max_length>
	char* static_string<str_max_length>::end()
	{
		return const_cast<char*>(const_cast<const static_string<str_max_length>*>(this)->end());
	}

	template<unsigned int str_max_length>
	const char* static_string<str_max_length>::end() const
	{
		return c_str() + size();
	}

	template<unsigned int str_max_length>
	range<char> static_string<str_max_length>::get_range()
	{
		return m_str.get_range();
	}

	template<unsigned int str_max_length>
	range<const char> static_string<str_max_length>::get_range() const
	{
		return m_str.get_range();
	}
	
	template<unsigned int str_max_length>
	range<char> static_string<str_max_length>::get_range(unsigned int index)
	{
		return m_str.get_range(index);
	}

	template<unsigned int str_max_length>
	range<const char> static_string<str_max_length>::get_range(unsigned int index) const
	{
		return m_str.get_range(index);
	}

	template<unsigned int str_max_length>
	range<char> static_string<str_max_length>::get_range(unsigned int start_index, unsigned int end_index)
	{
		return m_str.get_range(start_index, end_index);
	}

	template<unsigned int str_max_length>
	range<const char> static_string<str_max_length>::get_range(unsigned int start_index, unsigned int end_index) const
	{
		return m_str.get_range(start_index, end_index);
	}

	template<unsigned int str_max_length>
	range<char> static_string<str_max_length>::find_char(char char_to_find)
	{
		const static_string<str_max_length>* this_ptr = const_cast<const static_string<str_max_length>*>(this);
		range<const char> result = this_ptr->find_char(char_to_find);
		return make_range(const_cast<char*>(result.iterator), result.length);
	}

	template<unsigned int str_max_length>
	range<char> static_string<str_max_length>::find_char_reverse(char char_to_find)
	{
		const static_string<str_max_length>* this_ptr = const_cast<const static_string<str_max_length>*>(this);
		range<const char> result = this_ptr->find_char_reverse(char_to_find);
		return make_range(const_cast<char*>(result.iterator), result.length);
	}

	template<unsigned int str_max_length>
	range<const char> static_string<str_max_length>::find_char(char char_to_find) const
	{
		const char* start_location = m_str.internal_array();
		const char* found_location = (const char*) memchr(start_location, char_to_find, m_str.size());
		if(found_location)
		{
			const int& index = found_location - start_location;
			return m_str.get_range(index);
		}
		return make_range<const char>(m_str.end(), 0); //null range
	}

	template<unsigned int str_max_length>
	range<const char> static_string<str_max_length>::find_char_reverse(char char_to_find) const
	{
		int i = m_str.size() - 1;
		for(; i >= 0; --i)
		{
			if(m_str[i] == char_to_find)
			{
				break;
			}
		}

		if(i >= 0)
		{
			return m_str.get_range(i);
		}
		return make_range<const char>(m_str.end(), 0); //null range
	}

	template<unsigned int str_max_length>
	template<template<unsigned int> class str_type, unsigned int other_max_length>
	range<char> static_string<str_max_length>::find(const z::base_string<str_type<other_max_length>>& other)
	{
		const static_string<str_max_length>* this_ptr = const_cast<const static_string<str_max_length>*>(this);
		range<const char> result = this_ptr->find(other.c_str());
		return make_range(const_cast<char*>(result.iterator), result.length);
	}

	template<unsigned int str_max_length>
	template<template<unsigned int> class str_type, unsigned int other_max_length>
	range<const char> static_string<str_max_length>::find(const z::base_string<str_type<other_max_length>>& other) const
	{
		return find(other.c_str());
	}

	template<unsigned int str_max_length>
	range<char> static_string<str_max_length>::find(const char* other)
	{
		const static_string<str_max_length>* this_ptr = const_cast<const static_string<str_max_length>*>(this);
		range<const char> result = this_ptr->find(other);
		return make_range(const_cast<char*>(result.iterator), result.length);
	}

	template<unsigned int str_max_length>
	range<const char> static_string<str_max_length>::find(const char* other) const
	{
		const char* str_this = m_str.internal_array();
		const char* found_location = (const char*) strstr(str_this, other);

		if(found_location)
		{
			const int& index = found_location - str_this;
			return m_str.get_range(index);
		}
		return make_range<const char>(m_str.end(), 0); //null range
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::clone()
	{
		return static_string<str_max_length>(*this);
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::to_upper()
	{
		std::transform(begin(), end(), begin(), std::toupper);
		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::to_lower()
	{
		std::transform(begin(), end(), begin(), std::tolower);
		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::trim()
	{
		z_assert(false && "not implemented");
		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::trim_left()
	{
		char* loc = std::find_if(m_str.internal_array(), m_str.end(), std::not1(std::ptr_fun<int, int>(std::isspace)));

		z_assert(false && "not implemented");
		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::trim_right()
	{
		z_assert(false && "not implemented");
		return *this;
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::starts_with(const char* prefix) const
	{
		unsigned int length = strlen(prefix);
		z_assert(length <= size());
		return strncmp(m_str.internal_array(), prefix, length) == 0;
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::ends_with(const char* suffix) const
	{
		unsigned int length = strlen(suffix);
		z_assert(length <= size());
		unsigned int end_index = size() - length;
		return strncmp(m_str.internal_array() + end_index, suffix, length) == 0;
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::contains(const char* str) const
	{
		z::range<const char> range = find(str);
		return !range.is_end();
	}

	template<unsigned int str_max_length>
	char* static_string<str_max_length>::c_str()
	{
		return m_str.internal_array();
	}

	template<unsigned int str_max_length>
	const char* static_string<str_max_length>::c_str() const
	{
		return m_str.internal_array();
	}

	template<unsigned int str_max_length>
	char* static_string<str_max_length>::internal_array()
	{
		return m_str.internal_array();
	}

	template<unsigned int str_max_length>
	const char* static_string<str_max_length>::internal_array() const
	{
		return m_str.internal_array();
	}
}