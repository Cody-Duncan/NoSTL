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

namespace z
{
	template<typename derived>
	struct base_string
	{
		inline derived& get_impl()
		{
			return (*static_cast<derived *>(this));
		}

		inline derived& get_impl() const
		{
			return (*static_cast<const derived *>(this));
		}

		unsigned int size() const
		{
			return get_impl().size();
		}

		unsigned int max_size() const
		{
			return get_impl().max_size();
		}

		char* c_str()
		{
			return get_impl().c_str();
		}

		const char* c_str() const
		{
			return get_impl().c_str();
		}
	};
	template<unsigned int str_max_length>
	struct static_string
	{
	private:
		char m_str[str_max_length];
		unsigned int m_size;

	public:
		static_string();
		static_string(const char*);
		static_string(const char*, unsigned int);

		template <unsigned int str_length>
		static_string(const char (&)[str_length]);

		template<typename T>
		static_string(const base_string<T>& other);

		bool operator==(const static_string &other) const;

		unsigned int size() const { return m_size; }
		unsigned int max_size() const { return str_max_length; }
		bool is_empty() const { return size == 0; }
		char* c_str() { return m_str; }
		const char* c_str() const { return m_str; }

		void clear();
		void clear_zero();

		char& operator[] (unsigned int pos);
		const char& operator[] (unsigned int pos) const;

		char& at(unsigned int pos);
		const char& at(unsigned int pos) const;

		template<typename T>
		static_string& append(const base_string<T>& s);
		static_string& append(const char* s);
		static_string& append(const char* s, unsigned int n);

		static_string& fill(char c, unsigned int n);

		char* begin();
		const char* begin() const;

		char* end();
		const char* end() const;

		static_string& clone();
		static_string& to_upper();
		static_string& to_lower();
		static_string& trim();
		static_string& trim_left();
		static_string& trim_right();

		bool starts_with(const char* prefix) const;
		bool ends_with(const char* suffix) const;
		bool contains(const char* str) const;

	private:
		void set_zero_str();
	};

	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string() :
		m_size(0)
	{
		set_zero_str();
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string(const char* other) :
		m_size(0)
	{
		set_zero_str();
		append(other);
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>::static_string(const char* other, unsigned int length)
	{
		z_assert(length <= str_max_length-1);
		set_zero_str();
		append(other, length);
	}

	template<unsigned int str_max_length>
	template<unsigned int str_length>
	static_string<str_max_length>::static_string(const char (&other)[str_length])
	{
		z_assert(str_length <= str_max_length-1);
		set_zero_str();
		append(other, str_length);
	}

	template<unsigned int str_max_length>
	template<typename T>
	static_string<str_max_length>::static_string(const base_string<T>& other) :
		m_size(0)
	{
		z_assert(other.max_size() <= str_max_length-1);
		set_zero_str();
		append(other);
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::operator==(const static_string &other) const
	{
		return strcmp(m_str, other.m_str) == 0;
	}

	template<unsigned int str_max_length>
	void static_string<str_max_length>::clear()
	{
		m_size = 0;
	}
	template<unsigned int str_max_length>
	void static_string<str_max_length>::clear_zero()
	{
		m_size = 0;
		set_zero_str();
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
	char& static_string<str_max_length>::at(unsigned int pos)
	{
		return const_cast<char&>(const_cast<const static_string<str_max_length>*>(this)->at(pos));
	}

	template<unsigned int str_max_length>
	const char& static_string<str_max_length>::at(unsigned int pos) const
	{
		z_assert(pos >= 0 && pos < size());
		return m_str[pos];
	}

	template<unsigned int str_max_length>
	template<typename T>
	static_string<str_max_length>& static_string<str_max_length>::append(const base_string<T>& s)
	{
		z_assert((size() + s.size()) <= str_max_length-1);
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

		if(*temp != '\0')
		{
			// ended early, must be out of space
			// add once to make the assert more clear that buffer is overfull
			++append_size;
			++temp;
		}

		z_assert((size() + append_size) <= str_max_length-1);
		append(s, append_size);

		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::append(const char* s, unsigned int n)
	{
		z_assert(n <= (max_size() - size()));
		for(unsigned int i = 0; i < n; ++i)
		{
			m_str[i] = *s;
			++s;
		}

		m_size = n;

		return *this;
	}

	template<unsigned int str_max_length>
	static_string<str_max_length>& static_string<str_max_length>::fill(char c, unsigned int n)
	{
		z_assert(n <= (max_size() - size()));
		for(int i = 0; i < n; ++i)
		{
			m_str[i] = c;
			++s;
		}
		m_size = n;

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
		z_assert(false && "not implemented");
		return false;
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::ends_with(const char* suffix) const
	{
		z_assert(false && "not implemented");
		return false;
	}

	template<unsigned int str_max_length>
	bool static_string<str_max_length>::contains(const char* str) const
	{
		z_assert(false && "not implemented");
		return false;
	}

	template<unsigned int str_max_length>
	void static_string<str_max_length>::set_zero_str()
	{
		for(unsigned int i = 0; i < max_size(); ++i)
		{
			m_str[i] = 0;
		}
	}

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