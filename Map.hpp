#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
#include "Pair.hpp"
#include "RBTree.hpp"
#include "TreeIterator.hpp"
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
		typedef typename treeIterator<T>::pointer				iterator;
		typedef typename const_treeIterator<T>::pointer			const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		//----------------------- extras ------------------------------------------//

		typedef Node<T>											node_type;

		// typedef typename template <class Iter, class NodeType>
		// struct insert_type {
		// 	Iter		position;
		// 	bool		inserted;
		// 		NodeType 	node;
		// } insert_return_type;

		/*
"ft::map<int, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, ft::less<int>,
              std::__1::allocator<ft::pair<int const, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > > >::map()"
   */

	public:
		map() {}
		map(const map& other) { _tree = other._tree; }
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() ) : _alloc(alloc), _value_compare(comp)
		{
			for (iterator temp = first; temp != last; ++temp)
				_tree.insert(*temp);
		}
		~map() {};
		map& operator=(const map& to_assign)
		{
			if (this != &to_assign)
			{
				
			}
			return (*this);
		}

	private:
		Allocator	_alloc;
		Compare		_value_compare;
		RBTree<value_type, value_compare<Key, Compare>, Allocator>	_tree;

	};

}

#endif