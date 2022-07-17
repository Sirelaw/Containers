#ifndef LESS_HPP
#define LESS_HPP
#include "IteratorTraits.hpp"

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
			return (less<T>()(lhs, rhs) == less<T>()(rhs, lhs));
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


	template<bool>
	struct	enable_if {};

	template<>
	struct	enable_if<true>
	{
		typedef	void type;
	};

	template<class T, T v>
	struct	integral_constant
	{
		static const T	value = v;
		typedef T		value_type;
		typedef integral_constant	type;
		operator	value_type() const { return value; }
		value_type	operator()() const { return value; }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;


	template <class T>	struct is_integral						: public false_type {};
	template <>			struct is_integral<bool>				: public true_type {};
	template <>			struct is_integral<char>				: public true_type {};
	template <>			struct is_integral<signed char>			: public true_type {};
	template <>			struct is_integral<unsigned char>		: public true_type {};
	template <>			struct is_integral<wchar_t>				: public true_type {};
	#if __cplusplus > 201703L || defined(__cpp_char8_t)
	template <>			struct is_integral<char8_t>				: public true_type {};
	#endif
	#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
	template <>			struct is_integral<char16_t>			: public true_type {};
	template <>			struct is_integral<char32_t>			: public true_type {};
	#endif
	template <>			struct is_integral<short>				: public true_type {};
	template <>			struct is_integral<unsigned short>		: public true_type {};
	template <>			struct is_integral<int>					: public true_type {};
	template <>			struct is_integral<unsigned int>		: public true_type {};
	template <>			struct is_integral<long>				: public true_type {};
	template <>			struct is_integral<unsigned long>		: public true_type {};
	template <>			struct is_integral<long long>			: public true_type {};
	template <>			struct is_integral<unsigned long long>	: public true_type {};
	#ifdef __SIZEOF_INT128__
	template <>			struct is_integral<__int128_t>			: public true_type {};
	template <>			struct is_integral<__uint128_t>			: public true_type {};		
	#endif // sizeof_int128_
}


#endif