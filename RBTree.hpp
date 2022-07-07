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
		typedef typename Allocator::template rebind< value_type >::other	value_allocator;
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
	iterator								begin(){ return iterator(_begin_ptr); }
	iterator								end(){ return iterator(&_root_parent); }
	const_iterator							cbegin() const { return const_iterator(_begin_ptr); }
	const_iterator							cend() const { return const_iterator(&_root_parent); }
	reverse_iterator						rbegin(){ return reverse_iterator(&_root_parent); }
	reverse_iterator						rend(){ return reverse_iterator(_begin_ptr); }
	const_reverse_iterator					crbegin() const { return const_iterator(&_root_parent); }
	const_reverse_iterator					crend() const { return const_iterator(_begin_ptr); }

//////////------------------ CONSTRUCTION & ASSIGNMENT ---------------////////////////////

		RBTree() : _size(0) { _begin_ptr = &_root_parent; }
		RBTree(const RBTree& to_copy) : _size(0) { _begin_ptr = &_root_parent; *this = to_copy; }

		RBTree& operator=(const RBTree& tree)
		{
			if ((this != &tree) && tree.root())
			{
				if (root()){
					destroy_children(*(root()));
					delete_single_node(*(root()));
				}
				for (const_iterator iter = tree.cbegin(); iter != tree.cend(); iter++)
				{
					this->insert(iter->value());
				}
			}
			return *this;
		}

		~RBTree(){
			this->clear();
		}

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
				_node_alloc.construct(root(), node_type(val));
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
				if (Compare()(temp->value(), val)){
					if (Compare()(val, temp->value()))
						return ft::make_pair(iterator(temp), false);
					else if (temp->right_child())
						temp = temp->right_child();
					else{
						temp->link_right_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->right_child(), node_type(val));
						temp->right_child()->set_parent(temp);
						temp = temp->right_child();
						break;
					}
				}
				else{
					if (!Compare()(val, temp->value()))
						return ft::make_pair(iterator(temp), false);
					else if (temp->left_child())
						temp = temp->left_child();
					else{
						temp->link_left_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->left_child(), node_type(val));
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
public:
		insert_return_type	insert(const T& val)
		{
			insert_return_type	inserted = new_insert(val);
			node_type*			temp = inserted.first;

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

//////////-------------------------- DELETE ------------------------////////////////////
public:
		void		clear()
		{
			if (!root())
				return ;
			for(iterator iter = begin(), temp; iter != end();)
			{
				temp = iter + 1;
				_node_alloc.destroy(iter);
				_node_alloc.deallocate(iter, 1);
				iter = temp;
			}
			_size = 0;
			set_root(nullptr);
		}
		void		erase(iterator pos)
		{
			if (pos)
			{
				if (pos == iterator(_begin_ptr))
					_begin_ptr = _begin_ptr->parent();
				delete_single_node(**pos);
				this->_size--;
			}
		}
public:


		void	remove(node_type& node)
		{
			if (&node == _begin_ptr)
				_begin_ptr = _begin_ptr->parent();
			delete_single_node(node);
			this->_size--;
		}

		void	remove(T value)
		{
			node_type*	temp = this->search(value);

			if (temp){
				if (temp == _begin_ptr)
					_begin_ptr = _begin_ptr->parent();
				delete_single_node(*temp);
				this->_size--;
			}
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
				this->_value_alloc.destroy(&(temp->value()));
				this->_node_alloc.deallocate(temp, 1);
			}
		}

//////////------------------------ TRANSVERSE-----------------------////////////////////
public:
		void	level_order_transverse() 
		{
			vector<node_type*>	ptr_vec;
			int					i = 0;

			if (!root())
				return;
			ptr_vec.push_back(root());
			while (ptr_vec.size() > i)
			{
				if (ptr_vec[i]->left_child())
					ptr_vec.push_back(ptr_vec[i]->left_child());
				if ((ptr_vec[i]->right_child()))
					ptr_vec.push_back(ptr_vec[i]->right_child());
				i++;
			}
		}

//////////------------------------ PRINTERS -----------------------////////////////////

		void	print_tree_in_order() const
		{
			stack<const node_type*>	temp;
			const node_type*			current = root();

			while (current || !(temp.empty()))
			{
				while (current)
				{
					temp.push(current);
					current = current->left_child();
				}
				while (!(temp.empty()) && !current)
				{
					std::cout << " ->" << temp.top()->value() << "\t(" << temp.top()->color() << ", " 
						<< temp.top()->balance_factor() << ", " << temp.top()->parent()->value() << ")" << std::endl;
					current = temp.top()->right_child();
					temp.pop();
				}
			}
			std::cout << "--------------------" << std::endl;

		}

		void	print_map_tree_in_order() const
		{
			stack<const node_type*>	temp;
			const node_type*			current = root();

			while (current || !(temp.empty()))
			{
				while (current)
				{
					temp.push(current);
					current = current->left_child();
				}
				while (!(temp.empty()) && !current)
				{
					std::cout << " ->" << temp.top()->value().first
							<< " : " << temp.top()->value().second << "\t(" << temp.top()->color() << ", " 
						<< temp.top()->balance_factor() << ", " << temp.top()->parent()->value().first << ")" << std::endl;
					current = temp.top()->right_child();
					temp.pop();
				}
			}
			std::cout << "--------------------" << std::endl;

		}

		void	print_tree_by_level() const
		{
			vector<node_type*>	ptr_vec;
			size_t					i = 0;

			if (!root())
				return;
			ptr_vec.push_back(root());
			while (ptr_vec.size() > i)
			{
				std::cout << " ->" << ptr_vec[i]->value() << "\t(" << ptr_vec[i]->color() << ", " << ptr_vec[i]->balance_factor() << ", " 
							<< ptr_vec[i]->parent()->value() << ")" << std::endl;
				if (ptr_vec[i]->left_child())
					ptr_vec.push_back(ptr_vec[i]->left_child());
				if ((ptr_vec[i]->right_child()))
					ptr_vec.push_back(ptr_vec[i]->right_child());
				
				i++;
			}
			std::cout << "--------------------" << std::endl;
		}

		void	print_tree_map_by_level() const
		{
			vector<node_type*>	ptr_vec;
			size_t					i = 0;

			if (!root())
				return;
			ptr_vec.push_back(root());
			while (ptr_vec.size() > i)
			{
				std::cout << " ->" << ptr_vec[i]->value().first
							<< " : " << ptr_vec[i]->value().second << "\t(" << ptr_vec[i]->color() << ", " << ptr_vec[i]->balance_factor() << ", " 
							<< ptr_vec[i]->parent()->value().first << ")" << std::endl;
				if (ptr_vec[i]->left_child())
					ptr_vec.push_back(ptr_vec[i]->left_child());
				if ((ptr_vec[i]->right_child()))
					ptr_vec.push_back(ptr_vec[i]->right_child());
				
				i++;
			}
			std::cout << "--------------------" << std::endl;
		}

//////////------------------------ HELPERS -----------------------////////////////////

		template<class U>
		struct	key_equals : binary_function<value_type, U, bool>
		{
			bool	operator()(value_type lhs, U rhs) { return lhs.first == rhs; }
		};

		template <class U>
		iterator	find_equal(U key)
		{
			node_type*	node = root();

			while (node != nullptr && !key_equals<U>()(node->value(), key))
			{
				if (key < node->value().first)
					node = node->left_child();
				else
					node = node->right_child();
			}
			return iterator(node);
		}

		node_type*	search(const T& value)
		{
			node_type*	node = root();

			while (node != nullptr && node->value() != value)
			{
				if (Compare()(value, node->value()))
					node = node->left_child();
				else
					node = node->right_child();
			}
			return node;
		}

		const node_type*	search(const T& value) const
		{
			node_type*	node = root();

			while (node != nullptr && node->value() != value)
			{
				if (Compare()(value, node->value()))
					node = node->left_child();
				else
					node = node->right_child();
			}
			return node;
		}
private:
		int		determine_setup(node_type& node)
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

		int	balance_factor(node_type& node)
		{
			return node.balance_factor();
		}

//////////------------------------ REBALANCE -----------------------////////////////////

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
//////////------------------------ TESTING -----------------------////////////////////
public :
		void	test_node()
		{
			PRINT("<<<<<--------->>>>>>", GREEN);
			print_tree_by_level();
			print_tree_in_order();
		}

		void	test_map()
		{
			PRINT("<<<<<--------->>>>>>", GREEN);
			print_tree_map_by_level();
			print_map_tree_in_order();
		}

	protected:
		node_type						_root_parent;
		node_type*						_begin_ptr;
		size_t							_size;
		value_allocator					_value_alloc;
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