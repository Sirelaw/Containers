#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
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
		explicit stack( const Container& cont = Container() ) { _container = cont; }
		stack( const stack& other ) { *this = other; }
		~stack() {}

		stack& 			operator=(const stack& to_assign)
		{
			if (this != &to_assign)
				_container = to_assign._container;
			return *this;
		}

		reference		top(){ return  _container.back(); }
		const_reference	top() const { return _container.back(); }
		bool			empty() const { return _container.empty(); }
		size_type		size() const { return _container.size(); }
		void			push( const value_type& value ) { _container.push_back(value); }
		void			pop() { _container.pop_back(); }
		
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
		Container	_container;
	};

	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs._container == rhs._container);
	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs._container != rhs._container);
	}
	
	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs._container < rhs._container);
	}
	
	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs._container <= rhs._container);
	}
	
	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs._container > rhs._container);
	}
	
	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return (lhs._container >= rhs._container);
	}

}
#endif