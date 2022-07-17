#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "IteratorTraits.hpp"

namespace ft
{


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
		typedef	typename iterator_traits<Iter>::value_type			value_type; 
	public:
		reverse_iterator(pointer ptr = nullptr) : _current(ptr) { }
		reverse_iterator(const Iter& current) : _current(current) { };
		template<class T1>
		reverse_iterator(const reverse_iterator<T1>& other) : _current(other.base())	{ }
		~reverse_iterator() {}

		iterator_type				base() const { return _current; }


		template<class T1>
		reverse_iterator&			operator=(const reverse_iterator<T1>& other) { _current = other.base(); return *this; }
		value_type&					operator*() const { iterator_type tmp = _current; return *(--tmp); }
		value_type*					operator->() const { return (&(operator*()));}
		reverse_iterator&			operator+=(difference_type n) { _current -= n; return *this; }
		reverse_iterator&			operator-=(difference_type n) { _current += n; return *this; }
		reverse_iterator&			operator++() { --_current; return *this; }
		reverse_iterator&			operator--() { ++_current; return *this; }
		reverse_iterator			operator++(int) { reverse_iterator tmp = *this; --_current; return tmp; }
		reverse_iterator			operator--(int) { reverse_iterator tmp = *this; ++_current; return tmp; }
		reverse_iterator			operator+(difference_type n) const { return reverse_iterator(_current - n); }
		reverse_iterator			operator-(difference_type n) const { return reverse_iterator(_current + n); }
		reference					operator[](difference_type n) const { return *(*this + n); }
		template<typename Iter1>
		bool						operator==(const reverse_iterator<Iter1>& other) const { return _current == other.base(); } 
		template<typename Iter1>
		bool						operator!=(const reverse_iterator<Iter1>& other) const { return !(*this == other); } 
		template<typename Iter1>
		bool						operator<(const reverse_iterator<Iter1>& other)const{ return other.base() < _current; }
		template<typename Iter1>
		bool						operator<=(const reverse_iterator<Iter1>& other)const{ return !(other < *this); }
		template<typename Iter1>
		bool						operator>=(const reverse_iterator<Iter1>& other)const{ return !(*this < other); }
		template<typename Iter1>
		bool						operator>(const reverse_iterator<Iter1>& other)const{ return (other < *this); }


	protected:
		iterator_type	_current;
	};

	template<typename Iter1>
	reverse_iterator<Iter1>			operator+(typename reverse_iterator<Iter1>::difference_type movement, const reverse_iterator<Iter1>& iter) { reverse_iterator<Iter1> temp(iter); temp += movement; return (temp); }
	template<typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type	operator-(const reverse_iterator<Iter1>& iter1, const reverse_iterator<Iter2>& iter2) { return (iter2.base() - iter1.base()); }
}
#endif