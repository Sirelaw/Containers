#ifndef ITERATORTRAITS_HPP
#define ITERATORTRAITS_HPP

#include <iostream>
#include <string>
#include <iterator>

namespace ft
{

	struct input_iterator_tag : 		public std::input_iterator_tag { };
	struct output_iterator_tag : 		public std::output_iterator_tag{ };
	struct forward_iterator_tag : 		public std::forward_iterator_tag { };
	struct bidirectional_iterator_tag : public std::bidirectional_iterator_tag { };
	struct random_access_iterator_tag : public std::random_access_iterator_tag { };

	template<typename iterator>
	class iterator_traits
	{
	public:
		typedef	typename iterator::value_type			value_type;
		typedef	typename iterator::difference_type		difference_type;
		typedef	typename iterator::reference			reference;
		typedef	typename iterator::const_reference		const_reference;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::const_pointer		const_pointer;
		typedef	typename iterator::iterator_category	iterator_category;
	};

	template< class T >
	struct iterator_traits<T*>
	{
	public:
		typedef	T										value_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	T&										reference;
		typedef	const T& 								const_reference;
		typedef	T*										pointer;
		typedef	const T*								const_pointer;
		typedef	random_access_iterator_tag				iterator_category;	
	};

	template< class T >
	struct iterator_traits<const T*>
	{
	public:
		typedef	T										value_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	const value_type&						reference;
		typedef	const value_type& 						const_reference;
		typedef	const T*								pointer;
		typedef	const T*								const_pointer;
		typedef	random_access_iterator_tag				iterator_category;	
	};
}

#endif