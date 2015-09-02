
namespace z
{
	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_first_of(const T& val) const
	{
		iterator_t current_iter = iterator;
		for(int i = 0; i < length; ++i)
		{
			if(*current_iter == val)
			{
				return make_range(current_iter, length - i);
			}
			
			++current_iter;
		}

		return make_range(iterator + length, 0); // null range
	}

	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_first_of(const range<const T>& values) const
	{
		iterator_t current_iter = iterator;
		for(int i = 0; i < length; ++i)
		{
			typename range<const T>::iterator_type values_iter = values.iterator;
			for(int k = 0; k < values.length; ++k)
			{
				if(*current_iter == *values_iter)
				{
					return make_range(current_iter, length - i);
				}

				++values_iter;
			}

			++current_iter;
		}

		return make_range(iterator + length, 0); // null range
	}

	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_last_of(const T& val) const
	{
		for(int i = length-1; i >= 0; --i)
		{
			iterator_t current_iter = iterator + i;
			if(*current_iter == val)
			{
				return make_range(current_iter, length - i);
			}
		}

		return make_range(iterator + length, 0); // null range
	}

	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_last_of(const range<const T>& values) const
	{
		for(int i = length-1; i >= 0; --i)
		{
			iterator_t current_iter = iterator + i;
			typename range<const T>::iterator_type values_iter = values.iterator;
			for(int k = 0; k < values.length; ++k)
			{
				if(*current_iter == *values_iter)
				{
					return make_range(current_iter, length - i);
				}

				++values_iter;
			}	
		}

		return make_range(iterator + length, 0); // null range
	}

	template<typename T, typename iterator_t>
	template<unsigned int arr_length>
	range<T, iterator_t> range<T, iterator_t>::find_first_of(const T(&values)[arr_length]) const
	{		
		return find_first_of(make_range(values, arr_length));
	}

	template<typename T, typename iterator_t>
	template<unsigned int arr_length>
	range<T, iterator_t> range<T, iterator_t>::find_last_of(const T(&values)[arr_length]) const
	{		
		return find_last_of(make_range(values, arr_length));
	}
}