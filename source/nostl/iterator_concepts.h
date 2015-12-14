/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_UTILITY_ITERATOR_CONCEPTS_HPP
#define RANGES_V3_UTILITY_ITERATOR_CONCEPTS_HPP

#include <iterator>
#include <type_traits>

namespace nostl
{	
	namespace concepts
	{
		struct Readable
		{
			template<typename I>
			using reference_t = decltype(*std::declval<I>());
		};
	}
}

#endif // RANGES_V3_UTILITY_ITERATOR_CONCEPTS_HPP
