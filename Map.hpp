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
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef pair<const key_type, mapped_type>							value_type;

		struct value_compare : binary_function<value_type, value_type, bool>
		{
			bool	operator()( const value_type& lhs, const value_type& rhs ) const
			{
				return (Compare()(lhs.first, rhs.first));
			}
		};

		typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef RBTree<value_type, value_compare, Allocator>				tree_type;
		typedef typename tree_type::node_type								node_type;

		//------------------ Iterator_tags ------------------------------------------//
	public:
		typedef typename tree_type::pointer									pointer;
		typedef typename tree_type::reference								reference;
		typedef typename tree_type::const_reference							const_reference;
		typedef typename tree_type::iterator								iterator;
		typedef typename tree_type::const_iterator							const_iterator;
		typedef typename tree_type::reverse_iterator						reverse_iterator;
		typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename tree_type::size_type								size_type;
		typedef typename tree_type::difference_type							difference_type;

		//----------------------- extras ------------------------------------------//

	public:
		map() { }
		map(const map& other) { _tree = other._tree; }
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), // need to pass this allocator
			const Allocator& alloc = Allocator() ) : _alloc(alloc), _value_compare(comp) // to the tree
		{
			for (iterator temp = first; temp != last; ++temp)
				_tree.insert(*temp);
		}
		~map() {};
		map& operator=(const map& other)
		{
			_tree = other._tree;
			return (*this);
		}
		allocator_type	get_allocator() { return _alloc; }
		T& at(const Key& key)
		{ 
			node_type*	temp = _tree.search(key);

			if (!temp)
				throw std::out_of_range("ft::map::out_of_range");
			return (temp->value().second);
		};
		const T& at(const Key& key) const
		{ 
			const node_type*	temp = _tree.search(key);

			if (!temp)
				throw std::out_of_range("ft::map::out_of_range");
			return (temp->value().second);
		};

	private:
		Allocator			_alloc;
		value_compare		_value_compare;
		tree_type			_tree;

	};
}

#endif