#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>
#include <string>

namespace ft
{
	template< class T1, class T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		pair() : first(T1()), second(T2()) {}
		pair( const T1& x, const T2& y ) : first(x), second(y) {}
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}
		~pair() {}
		pair& operator=(const pair& p)
		{
			first = p.first;
			second = p.second;
			return *this;
		}

		T1	first;
		T2	second;
	};

	template< class T1, class T2 >
	pair<T1,T2> make_pair( T1 t, T2 u )
	{
		pair<T1, T2>	new_pair(t, u);
		return new_pair;
	}

	template< class T1, class T2 >
	bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
	}

	template< class T1, class T2 >
	bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ 
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && (lhs.second < rhs.second)));
	}

	template< class T1, class T2 >
	bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>=( const pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif