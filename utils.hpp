#ifndef LESS_HPP
#define LESS_HPP

#include <iostream>
#include <string>
// #include <__functional_base>

namespace ft
{
	template< class T >
	struct less : std::binary_function<T, T, bool>
	{
		bool	operator()( const T& lhs, const T& rhs ) const
		{
			return (lhs < rhs);
		}
	};
}

#endif

