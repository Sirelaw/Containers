#ifndef MAP_HPP
#define MAP_HPP

#include "Pair.hpp"
#include "./base/RBTree.hpp"
#include "./iterators/IteratorTraits.hpp"
#include "./utils/Algorithm.hpp"

namespace ft
{
	template< class Key, class T, class Compare = less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef pair<const key_type, mapped_type>							value_type;

		struct value_compare : binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare>;
		protected:
			Compare	comp;
			value_compare(Compare c) : comp(c) {}
		public:
			bool	operator()( const value_type& lhs, const value_type& rhs ) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

		typedef Compare														key_compare;
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
		const_iterator							begin() const { return _tree.begin(); }
		const_iterator							end() const { return _tree.end(); }
		reverse_iterator						rbegin(){ return _tree.rbegin(); }
		reverse_iterator						rend(){ return _tree.rend(); }
		const_reverse_iterator					rbegin() const { return _tree.crbegin(); }
		const_reverse_iterator					rend() const { return _tree.crend(); }
	private: ////// not present in c++98	
		const_iterator							cbegin() const { return _tree.cbegin(); }
		const_iterator							cend() const { return _tree.cend(); }
		const_reverse_iterator					crbegin() const { return _tree.crbegin(); }
		const_reverse_iterator					crend() const { return _tree.crend(); }

		//----------------------- extras ------------------------------------------//

	public:
		map() : _tree(value_compare(key_compare())) { }
		explicit map( const key_compare& comp, const Allocator& alloc = Allocator() ) : _tree(value_compare(comp), alloc)//////////need to implement
		{

		}
		map(const map& other) : _tree(other._tree) {  }
		template< class InputIt >
		map( InputIt first, InputIt last, const key_compare& comp = key_compare(), // need to pass this allocator
			const Allocator& alloc = Allocator() ) : _tree(value_compare(comp), alloc) // to the tree
		{
			this->insert(first, last);
		}
		~map() { };

		map& operator=(const map& other)
		{
			_tree = other._tree;
			return (*this);
		}

		allocator_type	get_allocator() const { return _alloc; }
		
	private: // map::at was not available until c++11
		mapped_type& at(const key_type& key)
		{ 
			iterator	temp = find(key);

			if (temp == end())
				throw std::out_of_range("ft::map::at:: key not found");
			return (temp->second);
		};
	
		const mapped_type& at(const key_type& key) const
		{ 
			const_iterator	temp = find_(key);

			if (temp == end())
				throw std::out_of_range("ft::map::at:: key not found");
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

		void				erase(iterator pos) { _tree.erase(pos); }
		void				erase(iterator first, iterator last) { _tree.erase(first, last); }
		size_type 			erase(const Key& key) { return _tree.erase(ft::make_pair(key, mapped_type())); }

		void				swap(map& other)
		{
			Allocator		this_alloc = this->_alloc;
			Compare			this_value_compare = this->_key_compare;
			
			_tree.swap(other._tree);
			_alloc = other.get_allocator();
			_key_compare = other._key_compare;
			other._alloc = this_alloc;
			other._key_compare = this_value_compare;
		}

		size_type			count(const key_type& key) const { return _tree.count(ft::make_pair(key, mapped_type())); }
		iterator			find(const Key& key) { return _tree.find_equal(ft::make_pair(key, mapped_type())); }//
		const_iterator		find(const Key& key) const { return _tree.find_equal(ft::make_pair(key, mapped_type())); }//
		iterator			lower_bound(const Key& key) { return _tree.lower_bound(ft::make_pair(key, mapped_type())); }//
		const_iterator		lower_bound(const Key& key) const { return _tree.lower_bound(ft::make_pair(key, mapped_type())); }//
		iterator			upper_bound(const Key& key) { return _tree.upper_bound(ft::make_pair(key, mapped_type())); }//
		const_iterator		upper_bound(const Key& key) const { return _tree.upper_bound(ft::make_pair(key, mapped_type())); }
		pair<iterator,iterator> equal_range( const Key& key )		{ return _tree.equal_range(ft::make_pair(key, mapped_type())); }
		pair<const_iterator,const_iterator> equal_range( const Key& key ) const { return _tree.equal_range(ft::make_pair(key, mapped_type())); }

		key_compare key_comp() const { return _key_compare; }
		value_compare value_comp() const { return value_compare(key_comp()); }
	
	private:
		Allocator		_alloc;
		Compare			_key_compare;
		tree_type		_tree;

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, 
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (!(lhs.size() == rhs.size()))
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), ft::map_equal_compare<ft::pair<Key, T> >());
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, 
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, 
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, 
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, 
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, 
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif