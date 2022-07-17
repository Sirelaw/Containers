#ifndef UTILS_HPP
#define UTILS_HPP
#include "../iterators/IteratorTraits.hpp"

namespace ft
{
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};

	template< class T >
	struct less : binary_function<T, T, bool>
	{
		bool	operator()( const T& lhs, const T& rhs ) const
		{
			return (lhs < rhs);
		}
	};

	template< class T >
	struct equal_to : binary_function<T, T, bool>
	{
		bool	operator()( const T& lhs, const T& rhs ) const
		{
			return ((lhs < rhs) == (rhs < lhs));
		}
	};

	template< class T >
	struct equal_pair
	{
		bool operator()( T& lhs_first, T& lhs_second, T& rhs_first, T& rhs_second ) const
		{
			return (equal_to<T>()(lhs_first, rhs_first) && equal_to<T>()(lhs_second, rhs_second));
		}
	};
}


#endif