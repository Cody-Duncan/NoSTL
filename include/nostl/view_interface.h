/*
Author: Cody Duncan
Date: November 4, 2015
Copyright: N/A
Witty Quote:
Description:

*/

#pragma once

#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H

// ---------- includes ---------

#include <type_traits>


#include "range_forward_declarations.h"
#include "range_concepts.h"
#include "iterator.h"

namespace nostl
{
	template<typename Derived, cardinality Cardinality /*= finite*/>
	struct view_interface
		: basic_view < Cardinality >
	{
		//// Derived
		Derived & derived()
		{
			return static_cast<Derived &>(*this);
		}

		Derived const & derived() const
		{
			return static_cast<Derived const &>(*this);
		}

		//// empty()
		bool empty() const
		{
			return Cardinality == 0 ? true : derived().begin() == derived().end();
		}

		bool operator!() const
		{
			return empty();
		}

		explicit operator bool() const
		{
			return !empty();
		}

		bool is_valid()
		{
			return !empty();
		}

		//// size()
		const range_size_t size() const
		{
			return Cardinality >= 0 ?
				(range_size_t)Cardinality :
				iter_size(derived().begin(), derived().end());
		}

		//// get_element()
		template<typename D = Derived>
		range_reference_t<D> get_element()
		{
			return front();
		}

		//// front()
		template<typename D = Derived>
		range_reference_t<D> front()
		{
			return *derived().begin();
		}

		template<typename D = Derived>
		range_reference_t<D const> front() const
		{
			return *derived().begin();
		}

		//// back()
		template<typename D = Derived>
		range_reference_t<D> back()
		{
			return *prev(derived().end());
		}

		template<typename D = Derived>
		range_reference_t<D const> back() const
		{
			return *prev(derived().end());
		}

		//// operator[]
		template<typename D = Derived>
		auto operator[](range_difference_t<D> n) -> decltype(std::declval<D &>().begin()[n])
		{
			return derived().begin()[n];
		}

		template<typename D = Derived>
		auto operator[](range_difference_t<D> n) const -> decltype(std::declval<D const &>().begin()[n])
		{
			return derived().begin()[n];
		}

		//// operator<<
		template<bool B = true, typename Stream = std::ostream>
		friend Stream &operator<<(Stream &sout, Derived const &rng)
		{
			auto it = rng.begin();
			auto const e = rng.end();
			if(it == e)
			{
				return sout << "[]";
			}
			sout << '[' << *it;
			while(++it != e)
			{
				sout << ',' << *it;
			}
			return sout << ']';
		}

		template<bool B = true, typename Stream = std::ostream>
		friend Stream &operator<<(Stream &sout, Derived &rng)
		{
			Derived const & c_rng = rng;
			return sout << c_rng;
		}
	};
}

#endif