/*
Author: Cody Duncan
Date: August 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef STATIC_STRING_H
#define STATIC_STRING_H

// ---------- includes ---------
#include "z_primitives.h"
#include "z_assert.h"
#include "static_vector.h"

namespace z
{
	template<typename derived>
	struct base_string
	{
		inline derived& get_self()
		{
			return (*static_cast<derived *>(this));
		}

		inline const derived& get_self() const
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

		char* c_str()
		{
			return get_self().c_str();
		}

		const char* c_str() const
		{
			return get_self().c_str();
		}
	};

	template<unsigned int str_max_length>
	struct static_string : public base_string<static_string<str_max_length>>
	{
	private:
		static_vector<char, str_max_length> m_str;

	public:
		static_string();
		static_string(const char*);
		static_string(const char*, unsigned int);
		static_string(const static_string& other);

		template <unsigned int str_length>
		static_string(const char (&)[str_length]);

		template<typename T>
		static_string(const base_string<T>& other);

		static_string& operator=(const static_string &other);

		bool operator==(const static_string &other) const;

		unsigned int size() const;
		unsigned int max_size() const;
		unsigned int max_str_size() const;
		bool is_empty() const;
		bool is_full() const;

		template<template<unsigned int> class str_type, unsigned int other_max_length>
		static_string& deep_copy(z::base_string<str_type<other_max_length>>& other);

		template<unsigned int array_size>
		static_string& deep_copy(const char (&)[array_size]);

		static_string& deep_copy(const char*, unsigned int size);
		static_string& deep_copy(const static_string&);

		void clear();
		void clear_zero();

		char& get(unsigned int index);
		const char& get(unsigned int index) const;

		char& operator[] (unsigned int pos);
		const char& operator[] (unsigned int pos) const;

		template<typename T>
		static_string& append(const base_string<T>& s);
		static_string& append(const char* s);
		static_string& append(const char* s, unsigned int n);

		static_string& fill(char c, unsigned int n);

		char* begin();
		const char* begin() const;

		char* end();
		const char* end() const;

		range<char> get_range();
		range<const char> get_range() const;
		range<char> get_range(unsigned int index);
		range<const char> get_range(unsigned int index) const;
		range<char> get_range(unsigned int start_index, unsigned int end_index);
		range<const char> get_range(unsigned int start_index, unsigned int end_index) const;

		range<char> find_char(char char_to_find);
		range<char> find_char_reverse(char char_to_find);

		range<const char> find_char(char char_to_find) const;
		range<const char> find_char_reverse(char char_to_find) const;

		template<template<unsigned int> class str_type, unsigned int other_max_length>
		range<char> find(const z::base_string<str_type<other_max_length>>& other);

		template<template<unsigned int> class str_type, unsigned int other_max_length>
		range<const char> find(const z::base_string<str_type<other_max_length>>& other) const;

		range<char> find(const char* other);
		range<const char> find(const char* other) const;

		static_string& clone();
		static_string& to_upper();
		static_string& to_lower();
		static_string& trim();
		static_string& trim_left();
		static_string& trim_right();

		bool starts_with(const char* prefix) const;
		bool ends_with(const char* suffix) const;
		bool contains(const char* str) const;

		void recheck_string_size();

		char* c_str();
		const char* c_str() const;

		char* internal_array();
		const char* internal_array() const;
	};
}

#include "static_string.inl"

namespace z
{
	typedef static_string<64> string;

	typedef static_string<32> string_short;
	typedef static_string<32> string_temp;

	typedef static_string<128> string_l;

	typedef static_string<1024> string_long;
	typedef static_string<2048> string_longlong;

	template<unsigned int l>
	z::string create_str(const char (&d)[l])
	{
		return z::string(d);
	}

	inline unsigned int hash_string(const char *string, size_t len)
	{
		unsigned int hash = 0;
		for(size_t i = 0; i < len; ++i)
			hash = 65599 * hash + string[i];
		return hash ^ (hash >> 16);
	}

	namespace test
	{
		void test_static_string();
	}
}

//STL HASH SHIM
//TODO: REPLACE
namespace std 
{
	template<typename T>
	struct hash;

	template <unsigned int str_max_length>
	struct hash<z::static_string<str_max_length>>
	{
		std::size_t operator()(const z::static_string<str_max_length>& k) const
		{
			using std::size_t;
			using std::hash;

			return hash<string>()(std::string(k.c_str()));
		}
	};

}

#endif