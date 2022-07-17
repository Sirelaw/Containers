#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{
	template< class T, class Container = vector<T> >
	class stack
	{
	public:
		//------------------ Typedefs------------------------------------------//
		typedef	Container									container_type;
		typedef	typename Container::value_type				value_type;
		typedef	typename Container::size_type				size_type;
		typedef	typename Container::reference				reference;
		typedef	typename Container::const_reference			const_reference;
	public:
		explicit stack( const Container& cont = Container() ) : c(cont) {  }
		stack( const stack& other ) { *this = other; }
		~stack() {}

		stack& 			operator=(const stack& other)
		{
			if (this != &other)
				c = other.c;
			return *this;
		}

		reference		top(){ return  c.back(); }
		const_reference	top() const { return c.back(); }
		bool			empty() const { return c.empty(); }
		size_type		size() const { return c.size(); }
		void			push( const value_type& value ) { c.push_back(value); }
		void			pop() { c.pop_back(); }
		
	template< class T1, class Cont >
	friend bool 		operator==( const stack<T1,Cont>& lhs, const stack<T1,Cont>& rhs );

	template< class T1, class Cont >
	friend bool 		operator!=( const stack<T1,Cont>& lhs, const stack<T1,Cont>& rhs );

	template< class T1, class Cont >
	friend bool 		operator<( const stack<T1,Cont>& lhs, const stack<T1,Cont>& rhs );

	template< class T1, class Cont >
	friend bool 		operator<=( const stack<T1,Cont>& lhs, const stack<T1,Cont>& rhs );
	
	template< class T1, class Cont >
	friend bool 		operator>( const stack<T1,Cont>& lhs, const stack<T1,Cont>& rhs );
	
	template< class T1, class Cont >
	friend bool 		operator>=( const stack<T1,Cont>& lhs, const stack<T1,Cont>& rhs );

	protected:
		Container	c;
	};

	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs.c == rhs.c);
	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return !(lhs.c == rhs.c);
	}
	
	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs.c < rhs.c);
	}
	
	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return !(rhs.c < lhs.c);
	}
	
	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (rhs.c < lhs.c);
	}
	
	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return !(lhs.c < rhs.c);
	}

}
#endif