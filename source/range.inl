
namespace z
{
	// find first instance of single value
	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_first_of(const T& val) const
	{
		return z::find_first_of(*this, val);
	}

	// find first instance of any of multiple values (range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_first_of(const range<const T>& values) const
	{
		return z::find_first_of(*this, values);
	}

	// find first instance of any of multiple values (array)
	template<typename T, typename iterator_t>
	template<unsigned int arr_length>
	range<T, iterator_t> range<T, iterator_t>::find_first_of(const T(&values)[arr_length]) const
	{	
		return z::find_first_of(*this, make_range<const T>(values, arr_length));
	}
	

	//// find last instance of single value
	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_last_of(const T& val) const
	{
		return z::find_last_of(*this, val);
	}

	// find last instance of any of multiple values (range)
	template<typename T, typename iterator_t>
	range<T, iterator_t> range<T, iterator_t>::find_last_of(const range<const T>& values) const
	{
		return z::find_last_of(*this, values);
	}

	// find first instance of any of multiple values (array)
	template<typename T, typename iterator_t>
	template<unsigned int arr_length>
	range<T, iterator_t> range<T, iterator_t>::find_last_of(const T(&values)[arr_length]) const
	{		
		return z::find_last_of(*this, make_range<const T>(values, arr_length));
	}
}