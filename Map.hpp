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
		struct	key_compare : binary_function<key_type, key_type, bool>
		{
			bool	operator()( const key_type& lhs, const key_type& rhs ) const
			{
				return (Compare()(lhs, rhs));
			}
		};

		// typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef RBTree<value_type, value_compare, Allocator>				tree_type;
		typedef typename tree_type::node_type								node_type;

		//------------------ tree_tags ------------------------------------------//
	public:
		typedef typename tree_type::pointer									pointer;
		typedef typename tree_type::reference								reference;
		typedef typename tree_type::const_reference							const_reference;
		typedef typename tree_type::iterator								iterator;
		typedef typename tree_type::const_iterator							const_iterator;
		typedef typename tree_type::reverse_iterator						reverse_iterator;
		typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename tree_type::size_type								size_type;
		typedef typename tree_type::insert_return_type						insert_return_type;
		typedef typename tree_type::difference_type							difference_type;
	
	public:
		iterator								begin(){ return _tree.begin(); }
		iterator								end(){ return _tree.end(); }
		const_iterator							cbegin() const { return _tree.cbegin(); }
		const_iterator							cend() const { return _tree.cend(); }
		reverse_iterator						rbegin(){ return _tree.rbegin(); }
		reverse_iterator						rend(){ return _tree.rend(); }
		const_reverse_iterator					crbegin() const { return _tree.crbegin(); }
		const_reverse_iterator					crend() const { return _tree.crend(); }

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
		~map() { };
		map& operator=(const map& other)
		{
			_tree = other._tree;
			return (*this);
		}

		allocator_type	get_allocator() { return _alloc; }
		
		void	testpoint()
		{
			_tree.test_map();
			PRINT(empty(), GREEN);
			PRINT(size(), GREEN);
		}
	
		mapped_type& at(const key_type& key)
		{ 
			iterator	temp = _tree.find_equal(key);

			if (!temp)
				throw std::out_of_range("ft::map::out_of_range");
			return (temp->second);
		};
	
		const mapped_type& at(const key_type& key) const
		{ 
			const_iterator	temp = _tree.find_equal(key);

			if (!temp)
				throw std::out_of_range("ft::map::out_of_range");
			return (temp->second);
		};
	
		mapped_type&			operator[](const key_type pos)
		{
			try
			{
				return (at(pos));
			}
			catch(const std::out_of_range& e)
			{
				return(_tree.insert(ft::make_pair(pos, mapped_type())).first->second);
			}
		}
		const mapped_type&		operator[](const key_type pos) const
		{ 
			try
			{
				return (at(pos));
			}
			catch(const std::out_of_range& e)
			{
				return(_tree.insert(ft::make_pair(pos, mapped_type())).first->value().second);
			}
		}

		insert_return_type	insert (const value_type& value)
		{
			return _tree.insert(value);
		}

		size_type			size() { return _tree.size(); }

		size_type			max_size() { return std::numeric_limits<difference_type>::max(); }

		bool				empty() { return size() == 0; }

		void				clear() { return _tree.clear(); }

		void				erase(iterator pos) { return _tree.erase(pos); }
		void				erase(iterator first, iterator last) { return _tree.erase(first, last); }

		void				swap(map& other)
		{
			Allocator		this_alloc = this->_alloc;
			Compare			this_value_compare = this->_value_compare;
			
			_tree.swap(other._tree);
			_alloc = other.get_allocator();
			_value_compare = other._value_compare;
			other._alloc = this_alloc;
			other._value_compare = this_value_compare;
		}

		size_type			count(const key_type& key) const { return _tree.count(key); }

		iterator			find(const Key& key)
		{
			iterator	temp = _tree.find_equal(key);

			if (temp) return temp;
			return end();
		}

	private:
		Allocator		_alloc;
		Compare			_value_compare;
		tree_type		_tree;

	};
}

#endif