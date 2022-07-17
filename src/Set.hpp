#ifndef SET_HPP
#define SET_HPP

#include "Pair.hpp"
#include "./base/RBTree.hpp"
#include "./iterators/IteratorTraits.hpp"
#include "./utils/Algorithm.hpp"

namespace ft
{
	template< class Key, class Compare = less<Key>, 
		class Allocator = std::allocator<Key> >
	class set
	{
	public:
		typedef Key															key_type;
		typedef key_type													mapped_type;
		typedef key_type													value_type;

		typedef Compare														key_compare;
		typedef key_compare													value_compare;
		typedef Allocator													allocator_type;
		typedef RBTree<value_type, value_compare, Allocator>				tree_type;
		typedef typename tree_type::node_type								node_type;

		//------------------ tree_tags ------------------------------------------//
	public:
		typedef typename tree_type::pointer									pointer;
		typedef typename tree_type::reference								reference;
		typedef typename tree_type::const_reference							const_reference;
		typedef typename tree_type::const_iterator							iterator;
		typedef typename tree_type::const_iterator							const_iterator;
		typedef typename tree_type::const_reverse_iterator					reverse_iterator;
		typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename tree_type::size_type								size_type;
		typedef typename tree_type::insert_return_type						insert_return_type;
		typedef typename tree_type::difference_type							difference_type;
	
	public:
		iterator								begin(){ return _tree.begin(); }
		iterator								end(){ return _tree.end(); }
		const_iterator							begin() const { return _tree.begin(); }
		const_iterator							end() const { return _tree.end(); }
		reverse_iterator						rbegin(){ return _tree.rbegin(); }
		reverse_iterator						rend(){ return _tree.rend(); }
		const_reverse_iterator					rbegin() const { return _tree.crbegin(); }
		const_reverse_iterator					rend() const { return _tree.crend(); }
	private: // constant iterators were not present in c++98
		const_iterator							cbegin() const { return _tree.cbegin(); }
		const_iterator							cend() const { return _tree.cend(); }
		const_reverse_iterator					crbegin() const { return _tree.crbegin(); }
		const_reverse_iterator					crend() const { return _tree.crend(); }

		//----------------------- extras ------------------------------------------//

	public:
		set() : _tree(value_compare(key_compare())) { }
		explicit set( const key_compare& comp, const Allocator& alloc = Allocator() ) : _tree(value_compare(comp), alloc)//////////need to implement
		{

		}
		set(const set& other) : _tree(other._tree) {  }
		template< class InputIt >
		set( InputIt first, InputIt last, const key_compare& comp = key_compare(), // need to pass this allocator
			const Allocator& alloc = Allocator() ) : _tree(value_compare(comp), alloc) // to the tree
		{
			this->insert(first, last);
		}
		~set() { };

		set& operator=(const set& other)
		{
			_tree = other._tree;
			return (*this);
		}

		allocator_type	get_allocator() const { return _alloc; }
		
	private: // set_at was not available untill c++11
		mapped_type& at(const key_type& key)
		{ 
			iterator	temp = find(key);

			if (temp == end())
				throw std::out_of_range("ft::set::at:: key not found");
			return (temp->second);
		};
	
		const mapped_type& at(const key_type& key) const
		{ 
			const_iterator	temp = find_(key);

			if (temp == end())
				throw std::out_of_range("ft::set::at:: key not found");
			return (temp->second);
		};
	public:
		mapped_type&			operator[](const key_type pos)
		{
			try
			{
				return (at(pos));
			}
			catch(const std::out_of_range& e)
			{
				return(this->insert(ft::make_pair(pos, mapped_type())).first->second);
			}
		}

		insert_return_type	insert (const value_type& value)
		{
			return _tree.insert(value);
		}

		iterator insert( iterator hint, const value_type& value )
		{
			if (hint == begin())
			return (_tree.insert(value)).first;
			else
			return (_tree.insert(value)).first;
		}

		template< class InputIt >
		void insert( InputIt first, InputIt last )
		{
			for (InputIt temp = first; temp != last; ++temp)
				_tree.insert(*temp);
		}

		bool				empty() const { return size() == 0; }
		size_type			size() const { return _tree.size(); }
		size_type			max_size() const { return _tree.max_size();}



		void				clear() { return _tree.clear(); }

		void				erase(iterator pos) { _tree.erase(*pos); }
		void				erase(iterator first, iterator last) 
		{
			while (first != last)
				_tree.erase(*(first++));
		}
		size_type 			erase(const Key& key) { return _tree.erase(key); }

		void				swap(set& other)
		{
			Allocator		this_alloc = this->_alloc;
			Compare			this_value_compare = this->_key_compare;
			
			_tree.swap(other._tree);
			_alloc = other.get_allocator();
			_key_compare = other._key_compare;
			other._alloc = this_alloc;
			other._key_compare = this_value_compare;
		}

		size_type			count(const key_type& key) const { return _tree.count(key); }

		iterator			find(const key_type& key) { return _tree.find_equal(key); }

		const_iterator		find(const key_type& key) const { return _tree.find_equal(key); }
		iterator			lower_bound(const key_type& key) { return _tree.lower_bound(key); }
		const_iterator		lower_bound(const key_type& key) const { return _tree.lower_bound(key); }
		iterator			upper_bound(const key_type& key) { return _tree.upper_bound(key); }
		const_iterator		upper_bound(const key_type& key) const { return _tree.upper_bound(key); }
		pair<iterator,iterator> equal_range( const key_type& key )		{ return _tree.equal_range(key); }
		pair<const_iterator,const_iterator> equal_range( const key_type& key ) const { return _tree.equal_range(key); }

		key_compare key_comp() const { return _key_compare; }
		value_compare value_comp() const { return _key_compare; }

	private:
		Allocator		_alloc;
		Compare			_key_compare;
		tree_type		_tree;

	};

	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs, 
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		if (!(lhs.size() == rhs.size()))
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), ft::equal_to<Key>());
	}
	
	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs, 
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}
	
	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs, 
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs, 
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}
	
	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs, 
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}
	
	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs, 
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key,Compare,Alloc>& lhs,
			ft::set<Key,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif