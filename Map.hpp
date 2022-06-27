#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
#include "Pair.hpp"
#include "RBTree.hpp"
#include "IteratorTraits.hpp"

namespace ft
{
	template< class Key, class T, class Compare = less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef pair<const key_type, T>							value_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;

		//------------------ Iterator_tags ------------------------------------------//

		typedef	bidirectional_iterator_tag						iterator_category;
		// typedef __tree_iterator<value_type, __node_pointer, difference_type>             iterator;
		typedef typename iterator_traits<map>::pointer			iterator;
		typedef typename iterator_traits<map>::const_pointer	const_iterator;
		typedef std::reverse_iterator<iterator>					reverse_iterator;
		typedef	std::reverse_iterator<const_iterator>			const_reverse_iterator;

	public:
		map();
		map(const map& to_copy);
		~map();
		map& operator=(const map& to_assign)
		{
			if (this != &to_assign)
			{
				
			}
			return (*this);
		}
	};
}

#endif