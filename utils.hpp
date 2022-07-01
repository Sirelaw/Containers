#ifndef LESS_HPP
#define LESS_HPP

#include <iostream>
#include <string>
#include "TreeIterator.hpp"

namespace ft
{
	template< class T >
	struct less
	{
		bool	operator()( const T& lhs, const T& rhs ) const
		{
			return (lhs < rhs);
		}
	};

	template< class T, class Compare >
	struct value_compare
	{
		bool	operator() ( const T& lhs, const T& rhs ) const
		{
			return (Compare()(lhs.first, rhs.first));
		}
	};

	template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T        value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template< class Iter >
	class reverse_iterator : public iterator <typename iterator_traits<Iter>::iterator_category, 
												typename iterator_traits<Iter>::value_type, 
												typename iterator_traits<Iter>::difference_type, 
												typename iterator_traits<Iter>::pointer, 
												typename iterator_traits<Iter>::reference>
	{
	public:
    	typedef Iter												iterator_type;
    	typedef typename iterator_traits<Iter>::difference_type		difference_type;
    	typedef typename iterator_traits<Iter>::reference			reference;
    	typedef typename iterator_traits<Iter>::pointer				pointer;
	public:
		reverse_iterator() {}
		reverse_iterator(const Iter& current) : _current(current) { };
		reverse_iterator(const reverse_iterator& other) : _current(other.base()) { };
		~reverse_iterator() {}

		iterator_type				base() const { return _current; }
		reverse_iterator&			operator=(const reverse_iterator& other) { _current = other.base(); return *this; }
		reference					operator*() const { iterator_type tmp = _current; return *(--tmp); }
		pointer						operator->() const { return (&(operator*()));}
		reverse_iterator&			operator++() { --_current; return *this; }
		reverse_iterator&			operator++(int) { reverse_iterator tmp = *this; --_current; return tmp; }
		reverse_iterator&			operator--() { ++_current; return *this; }
		reverse_iterator&			operator--(int) { reverse_iterator tmp = *this; ++_current; return tmp; }
		reverse_iterator			operator+(difference_type n) const { return reverse_iterator(_current - n); }
		reverse_iterator&			operator+=(difference_type n) { _current -= n; return *this; }
		reverse_iterator			operator-(difference_type n) const { return reverse_iterator(_current + n); }
		reverse_iterator&			operator-=(difference_type n) { _current += n; return *this; }
		reference					operator[](difference_type n) const { return *(*this + n); }

		bool						operator==(const reverse_iterator& other) const { return _current == other.base(); } 
		bool						operator!=(const reverse_iterator& other) const { return _current != other.base(); } 

	protected:
		iterator_type	_current;
	};

	template<bool>
	struct	enable_if {};

	template<>
	struct	enable_if<true>
	{
		using type = void;
	};

}


#endif