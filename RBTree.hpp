#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <string>
#include "Node.hpp"
#include "utils.hpp"
#include "TreeIterator.hpp"
#include "Pair.hpp"

namespace ft
{
	enum{
		black,
		red
	};

	enum{
		LL,
		LR,
		RL,
		RR
	};

	template <class T, class Compare = less<T> , class Allocator = std::allocator<T> >
	class RBTree
	{	
	public:
		typedef T															value_type;
		typedef Compare														value_compare;
		typedef Allocator													allocator_type;
		typedef Node<T>														node_type;
	private:	
		typedef std::allocator_traits<allocator_type>						alloc_traits;

	public:	
		typedef typename Allocator::template rebind< node_type >::other		node_allocator;
		// typedef typename Allocator::template rebind< value_type >::other	value_allocator;
		typedef node_type*													node_pointer;
		typedef typename Allocator::pointer         						pointer;
    	typedef typename Allocator::const_pointer  							const_pointer;
		typedef typename Allocator::reference         						reference;
    	typedef typename Allocator::const_reference  						const_reference;
    	typedef typename Allocator::size_type       						size_type;
    	typedef typename Allocator::difference_type							difference_type;

//////////-------------------------- ITERATORS ----------------------////////////////////
	
	public:
		typedef	treeIterator<T>											iterator;
		typedef	const_treeIterator<T>									const_iterator;
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef pair<iterator, bool>									insert_return_type;
		typedef	bidirectional_iterator_tag								iterator_category;

	public:
		iterator														begin(){ return _begin_ptr; }
		iterator														end(){ return &_root_parent; }
		const_iterator													begin() const { return _begin_ptr; }
		const_iterator													end() const { return &_root_parent; }
		const_iterator													cbegin() const { return _begin_ptr; }
		const_iterator													cend() const { return &_root_parent; }
		reverse_iterator												rbegin(){ return &_root_parent; }
		reverse_iterator												rend(){ return _begin_ptr; }
		const_reverse_iterator											rbegin() const { return &_root_parent; }
		const_reverse_iterator											rend() const { return _begin_ptr; }
		const_reverse_iterator											crbegin() const { return &_root_parent; }
		const_reverse_iterator											crend() const { return _begin_ptr; }

//////////------------------ CONSTRUCTION & ASSIGNMENT ---------------////////////////////

		RBTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _begin_ptr (&_root_parent), _size(0), _compare(comp), _alloc(alloc)
		{

		} 
		RBTree(const value_type* first, const value_type* last, const Compare& comp = Compare())
			: _begin_ptr (&_root_parent), _size(0), _compare(comp)
		{
			while (first != last) insert(*(first++));
		}
		RBTree(const RBTree<value_type, Compare, Allocator>& other)
			: _begin_ptr(&_root_parent), _size(0), _compare(other._compare), _alloc(other._alloc),
				_node_alloc(other._node_alloc)
		{
			*this = other;
		}

		RBTree& operator=(const RBTree& other)
		{
			if ((this != &other) && other.root())
			{
				this->clear();
				_node_alloc = other._node_alloc;
				for (const_iterator iter = other.cbegin(); iter != other.cend(); iter++)
				{
					this->insert(*iter);
				}
			}
			return *this;
		}

		~RBTree() { this->clear(); }

//////////--------------------- GETTERS & SETTERS--------------------////////////////////
private:
		node_type*	root() const { return _root_parent.left_child(); }
		void		set_root(node_type* ptr) { _root_parent.link_left_child(ptr); }
public:
		size_t		size() const { return _size; }
		size_t		confirm_size() const { return root()->size(); }

//////////-------------------------- INSERT ------------------------////////////////////
private:
		insert_return_type	new_insert(const T& val)
		{
			_size++;
			if (_size == 1)
			{
				set_root(_node_alloc.allocate(1));
				_node_alloc.construct(root(), val);
				root()->set_parent(&_root_parent);
				root()->set_color(false);
				_root_parent.set_color(false);
				_begin_ptr = root();
				return ft::make_pair(iterator(root()), true);
			}
			return (insert(*root(), val));
		}

		insert_return_type	insert(node_type& node, const T& val)
		{
			node_type*			temp;

			temp = &node;
			while (temp)
			{
				if (_compare(temp->value(), val)){
					if (_compare(val, temp->value()))
						return ft::make_pair(iterator(temp), false);
					else if (temp->right_child())
						temp = temp->right_child();
					else{
						temp->link_right_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->right_child(), val);
						temp->right_child()->set_parent(temp);
						temp = temp->right_child();
						break;
					}
				}
				else{
					if (!_compare(val, temp->value()))
						return ft::make_pair(iterator(temp), false);
					else if (temp->left_child())
						temp = temp->left_child();
					else{
						temp->link_left_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->left_child(), val);
						temp->left_child()->set_parent(temp);
						if (temp == _begin_ptr)
							_begin_ptr = temp->left_child();
						temp = temp->left_child();
						break;
					}
				}
			}
			return ft::make_pair(iterator(temp), true);
		}
///////////////////////// inserting with hint

// iterator	__insert(node_pointer x, node_pointer y, const value_type& v) {
//     ++node_count;
//     node_pointer z = _node_alloc.allocate(1);
// 	_node_alloc.construct(z, val)
//     if (y == header || x != NIL || key_compare(KeyOfValue()(v), key(y))) {
//         left(y) = z;  // also makes leftmost() = z when y == header
//         if (y == header) {
//             root() = z;
//             rightmost() = z;
//         } else if (y == leftmost())
//             leftmost() = z;   // maintain leftmost() pointing to minimum node
//     } else {
//         right(y) = z;
//         if (y == rightmost())
//             rightmost() = z;   // maintain rightmost() pointing to maximum node
//     }
//     parent(z) = y;
//     left(z) = NIL;
//     right(z) = NIL;
//     x = z;  // recolor and rebalance the tree
//     color(x) = red;
//     while (x != root() && color(parent(x)) == red) 
//         if (parent(x) == left(parent(parent(x)))) {
//             y = right(parent(parent(x)));
//             if (color(y) == red) {
//                 color(parent(x)) = black;
//                 color(y) = black;
//                 color(parent(parent(x))) = red;
//                 x = parent(parent(x));
//             } else {
//                 if (x == right(parent(x))) {
//                     x = parent(x);
//                     rotate_left(x);
//                 }
//                 color(parent(x)) = black;
//                 color(parent(parent(x))) = red;
//                 rotate_right(parent(parent(x)));
//             }
//         } else {
//             y = left(parent(parent(x)));
//             if (color(y) == red) {
//                 color(parent(x)) = black;
//                 color(y) = black;
//                 color(parent(parent(x))) = red;
//                 x = parent(parent(x));
//             } else {
//                 if (x == left(parent(x))) {
//                     x = parent(x);
//                     rotate_right(x);
//                 }
//                 color(parent(x)) = black;
//                 color(parent(parent(x))) = red;
//                 rotate_left(parent(parent(x)));
//             }
//         }
//     color(root()) = black;
//     return iterator(z);
// }
	

// iterator	insert(iterator position, const Value& v)
// {
//     if (position == begin())
//         if (size() > 0 && _compare(v, *position))
//             return __insert(position.getPtr(), position.getPtr(), v);
//             // first argument just needs to be non-NIL 
//         else
//             return insert(v).first;
//     else if (position == iterator(end()))
//         if (_compare(key(rightmost()), KeyOfValue()(v)))
//             return __insert(NIL, rightmost(), v);
//         else
//             return insert(v).first;
//     else {
//         iterator before = --position;
//         if (_compare(key(before.node), KeyOfValue()(v))
//             && _compare(KeyOfValue()(v), key(position.node)))
//             if (right(before.node) == NIL)
//                 return __insert(NIL, before.node, v); 
//             else
//                 return __insert(position.node, position.node, v);
//                 // first argument just needs to be non-NIL 
//         else
//             return insert(v).first;
//     }
// }

//////////// end insert with hint

public:
		insert_return_type	insert(const T& val)
		{
			return rebalance_after_insert(new_insert(val));
		}

		// iterator insert( iterator hint, const value_type& value )
		// {
		// 	return _tree.insert(hint, value);
		// }

		// template< class InputIt >
		// void insert( InputIt first, InputIt last )
		// {
		// 	return _tree.insert(first, last);
		// }


//////////-------------------------- DELETE ------------------------////////////////////
private:
		void	delete_node(node_type* node)
		{
			if (node)
			{
				delete_node(node->left_child());
				delete_node(node->right_child());
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}
		}
public:
		void		clear()
		{
			if (!root())
				return ;
			delete_node(root());
			_size = 0;
			_begin_ptr = &_root_parent;
			set_root(nullptr);
		}
		void		erase(iterator pos)
		{
			if (pos.getPtr())
			{
				if (pos == iterator(_begin_ptr))
					_begin_ptr = (++(iterator(_begin_ptr))).getPtr();
				delete_single_node(*(pos.getPtr()));
				this->_size--;
			}
		}
		void		erase(iterator first, iterator last)
		{
			iterator	temp(first);
		
			++temp;
			for(iterator iter = first; iter != last;)
			{
				if (iter == iterator(_begin_ptr))
					_begin_ptr = (++(iterator(_begin_ptr))).getPtr();
				delete_single_node(*(iter.getPtr()));
				--_size;
				iter = temp++;
			}
		}
		template <typename Key>
		size_type erase( const Key& key )
		{
			iterator	elem = find_equal(key);
			if (elem == end())
				return 0;
			if (elem == iterator(_begin_ptr))
				_begin_ptr = (++(iterator(_begin_ptr))).getPtr();
			delete_single_node(*(elem.getPtr()));
			--_size;
			return 1;
		}

private:
		void	delete_single_node(node_type& node)
		{
			int			offspring	= node.count_children();
			node_type*	temp = &node;

			if (offspring == 1){
				delete_single_node(node.swap_node(node.single_child()));}
			else if (offspring == 2)
				delete_single_node(node.swap_node(node.in_order_successor()));
			else{
				resolve_double_black(node);
				*(node.parent_branch()) = nullptr;
				this->_node_alloc.destroy(temp);
				this->_node_alloc.deallocate(temp, 1);
			}
		}

public:

//////////------------------------ HELPERS -----------------------////////////////////

		template <class Key>
		iterator	find_equal(const Key& key)
		{
			node_type*	node = root();

			while (node != nullptr && !equal_to<Key>()(node->value().first, key))
			{
				if (key < node->value().first)
					node = node->left_child();
				else
					node = node->right_child();
			}
			if (!node)
				return end();
			return iterator(node);
		}

		template <class Key>
		const_iterator	find_equal(const Key& key) const
		{
			node_type*	node = root();

			while (node != nullptr && !equal_to<Key>()(node->value().first, key))
			{
				if (key < node->value().first)
					node = node->left_child();
				else
					node = node->right_child();
			}
			if (!node)
				return cend();
			return const_iterator(node);
		}

		template<class Key>
		pair<iterator,iterator> equal_range( const Key& key )
		{
			return make_pair(lower_bound(key), upper_bound(key)); 
		}

		template<class Key>
		pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			return make_pair(lower_bound(key), upper_bound(key)); 
		}

		template <class Key>
		iterator	lower_bound(const Key& key)
		{
			node_type*	node = root();
			iterator	result = end();

			while (node != nullptr)
			{
				if (!less<Key>()(node->value().first, key))
				{
					result = iterator(node);
					node = (node->left_child());
				}
				else
					node = node->right_child();
			}
			return result;
		}

		template <class Key>
		const_iterator	lower_bound(const Key& key) const
		{
			const node_type*	node = root();
			const_iterator		result = cend();

			while (node != nullptr)
			{
				if (!less<Key>()(node->value().first, key))
				// if (!_compare(val, temp->value()))
				{
					result = const_iterator(node);
					node = (node->left_child());
				}
				else
					node = node->right_child();
			}
			return result;
		}

		template<class Key>
		iterator	upper_bound(const Key& key)
		{
			node_type*	node = root();
			node_type*	result = end().getPtr();

			while (node != nullptr)
			{
				if (less<Key>()(key, node->value().first))
				{
					result = node;
					node = node->left_child();
				}
				else
					node = node->right_child();
			}
			return iterator(result);
		}

		template <class Key>
		const_iterator upper_bound(const Key& key) const
		{
			const node_type*	node = root(); /* Current node. */
			const_iterator		result = cend(); /* Last node which is greater than k. */

			while (node != nullptr) 
			{
				if (less<Key>()(key, node->value().first))
				{
					result = const_iterator(node);
					node = node->left_child();
				}	
				else
					node = node->right_child();
			}	
			return result;
		}

		template <class U>
		size_type	count(const U& key) const
		{
			const_iterator	elem = find_equal(key);
			size_type	num;

			if (elem != cend())
			{
				num = 1;
				while (((++elem)->first < key) == (key < (elem)->first))
					num++;
				return num; 
			}
			return 0;
		}

		void	swap(RBTree& other)
		{
			node_type*			this_root = this->root();
			node_type*			this_begin_ptr = this->_begin_ptr;
			size_t				this_size = this->_size;
			node_allocator		this_node_alloc = this->_node_alloc;

			this->_root_parent.link_left_child(other.root());
			if (other.size())
				this->_begin_ptr = other._begin_ptr;
			else
				this->_begin_ptr = (this->end()).getPtr();
			this->_size = other._size;
			this->_node_alloc = other._node_alloc;
			other._root_parent.link_left_child(this_root);
			if (this_size)
				other._begin_ptr = this_begin_ptr;
			else
				other._begin_ptr = (other.end()).getPtr();
			other._size = this_size;
			other._node_alloc = this_node_alloc;
		}

private:
		int		determine_setup(node_type& node) const
		{
			if (node.parent()->is_left() && node.is_left())
				return LL;
			else if (node.parent()->is_left() && node.is_right())
				return LR;
			else if (node.parent()->is_right() && node.is_left())
				return RL;
			return RR;
		}

		node_type&	predecessor(node_type& node)
		{
			node_type*	max;

			max = node->left_child();
			while (max->right_child())
				max = max->right_child();
			return *max;
		}

		node_type&	successor(node_type& node)
		{
			node_type*	min;

			min = node->right_child();
			while (min->left_child())
				min = min->left_child();
			return *min;
		}

		int	balance_factor(node_type& node) const
		{
			return node.balance_factor();
		}

//////////------------------------ REBALANCE -----------------------////////////////////

		insert_return_type	rebalance_after_insert(insert_return_type inserted)
		{
			node_type*			temp = inserted.first.getPtr();

			if (inserted.second == false)
				_size--;
			else if (temp->parent_is_black())
			{ }
			else if (temp->uncle_is_black())
				rotate_to_balance(*temp);
			else{
				while (temp->uncle_is_red())
				{
					temp->uncle()->set_color(black);
					temp->parent()->set_color(black);
					if (temp->parent()->parent() != this->root())
					{
						temp->parent()->parent()->set_color(red);
						if (temp->parent()->parent()->parent_is_black())
							break ;
						else {
							if (temp->parent()->parent()->uncle_is_black())
							{
								rotate_to_balance(*(temp->parent()->parent()));
								break ;
							}
							else
								temp = temp->parent()->parent();
						}
					}
				}
			}
			return inserted;
		}

		void	rotate_to_balance(node_type& node)
		{
			node_type**	grand_parent_position;
			int			setup;

			grand_parent_position = node.parent()->parent()->parent_branch();	
			setup = this->determine_setup(node);
			if (setup == LL)
				node.parent()->parent()->right_rotate();
			else if (setup == LR){
				node.parent()->left_rotate();
				node.parent()->right_rotate();
			}
			else if (setup == RL){
				node.parent()->right_rotate();
				node.parent()->left_rotate();
			}
			else
				node.parent()->parent()->left_rotate();
			(*grand_parent_position)->set_color(black);
			(*grand_parent_position)->right_child()->set_color(red);
			(*grand_parent_position)->left_child()->set_color(red);
		}

		void	resolve_double_black(node_type& node)
		{
			bool	temp = node.parent()->color();

			switch (double_black_case_type(node))
			{
				case 1:
					break ;
				case 3:
					node.sibling()->set_color(red);
					if(node.parent_is_red())
						node.parent()->set_color(black);
					else
						resolve_double_black(*(node.parent()));
					break;
				case 4:
					node.sibling()->set_color(black);
					node.parent()->set_color(red);
					if (node.is_left())
						node.parent()->left_rotate();
					else
						node.parent()->right_rotate();
					resolve_double_black(node);
					break;
				case 5:
					node.sibling()->set_color(red);
					node.close_nephew()->set_color(black);
					if (node.is_left())
						node.sibling()->right_rotate();
					else
						node.sibling()->left_rotate();
				case 6:
					node.parent()->set_color(node.sibling()->color());
					node.sibling()->set_color(temp);
					node.distant_nephew()->set_color(black);
					if (node.is_left())
						node.parent()->left_rotate();
					else
						node.parent()->right_rotate();
			}
		}

		int	double_black_case_type(node_type& node)
		{
			node_type*	sib = node.sibling();
			node_type*	close_neph = node.close_nephew();
			node_type*	distant_neph = node.distant_nephew();

			if (node.is_red() || (&node == this->root()))
				return 1;
			else if (sib->is_black() && !node.color(close_neph) && !node.color(distant_neph))
				return 3;
			else if (sib->is_red())
				return 4;
			else if (node.color(close_neph) && !node.color(distant_neph))
				return 5;
			else if (node.color(distant_neph))
				return 6;
			return 0;
		}
	public:
		// Compare	key_comp() const { return _compare; }

	protected:
		node_type						_root_parent;
		node_type*						_begin_ptr;
		size_t							_size;
		Compare							_compare;
		Allocator						_alloc;
		node_allocator					_node_alloc;

	};

}

/*
	Delete cases
	case 1 & 2: node is red || node is root
	case 3: 	S,D,C are all black
	case 4:		S is red
	case 5:		S,D are black. C is red
	case 6:		D is red
*/

/*

Root must always be BLACK.
Nil nodes are always BLACK i.e Nil_is_Black must be implemented.
No RED node must PARENT another RED node.
Any path from any node to any of it's descendant Nil node must have equal number of BLACK nodes.
The longest path from the root is no more than twice the shortest path.

Insertion
1. If there is an empty, create newnode as root node with color BLACK. Done.
2. If there is no empty, create newnode as leaf node with color RED.
3. If parent of newnode is BLACK then EXIT.
4. If parent of newnode is RED, then check the color of parent's sibling of newnode
   (a) If color is black or null then do suitable rotation and recolor.
   (b) If parent's parent of new node is not root node then recolor it and recheck

Deletion
1. If node to be deleted is a RED, simply delete and exit.
2. If node has one child, value with the value of it's child them call delete function on the child;
	Could be implememted with recursion.

Double black node has black sibling, but double black node is a left child and the
right nephew is black. Rotate tree to make opposite nephew red.
*/

#endif