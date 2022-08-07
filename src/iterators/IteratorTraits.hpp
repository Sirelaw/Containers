#ifndef ITERATORTRAITS_HPP
#define ITERATORTRAITS_HPP

#include <iterator>

namespace ft
{
	// struct input_iterator_tag { };
	// struct output_iterator_tag { };
	// struct forward_iterator_tag : 		public input_iterator_tag { };
	// struct bidirectional_iterator_tag : public forward_iterator_tag { };
	// struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	typedef std::input_iterator_tag				input_iterator_tag;
	typedef std::output_iterator_tag			output_iterator_tag;
	typedef std::forward_iterator_tag			forward_iterator_tag;
	typedef std::bidirectional_iterator_tag  	bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag 	random_access_iterator_tag;

	template< typename iterator >
	struct iterator_traits
	{
		typedef	typename iterator::value_type			value_type;
		typedef	typename iterator::difference_type		difference_type;
		typedef	typename iterator::reference			reference;
		typedef typename iterator::pointer				pointer;
		typedef	typename iterator::iterator_category	iterator_category;
	};

	template< typename T >
	struct iterator_traits<T*>
	{
		typedef	T										value_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	T&										reference;
		typedef	T*										pointer;
		typedef	random_access_iterator_tag				iterator_category;	
	};

	template< typename T >
	struct iterator_traits<const T*>
	{
		typedef	T										value_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	const value_type&						reference;
		typedef	const T*								pointer;
		typedef	random_access_iterator_tag				iterator_category;	
	};
}

#endif