
#ifndef RANGES_RANGE_CONCEPTS_HPP
#define RANGES_RANGE_CONCEPTS_HPP

#include "iterator_concepts.h"

namespace nostl
{
	namespace concepts
	{
		struct Range
		{
			// Associated types
			template<typename T>
			using iterator_t = decltype(std::declval<T&>().begin());

			template<typename T>
			using sentinel_t = decltype(std::end(std::declval<T&>()));

			//template<typename T>
            //using difference_t = concepts::WeaklyIncrementable::difference_t<iterator_t<T>>;
		};

		struct InputRange
		{
			//template<typename T>
            //using value_t = concepts::Readable::value_t<iterator_t<T>>;

            template<typename T>
            using reference_t = concepts::Readable::reference_t<Range::iterator_t<T>>;
		};
	}

	/////////////////////////////////////////////////////////////////////
	// RANGE TRAITS
	template<typename Rng>
	using range_reference_t = concepts::InputRange::reference_t<Rng>;

	template<typename Rng>
	using range_difference_t = int;

}
#endif