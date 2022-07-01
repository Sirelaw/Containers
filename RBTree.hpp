#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <string>
#include "Stack.hpp"
#include "Vector.hpp"
#include "Node.hpp"
#include "utils.hpp"
#include "TreeIterator.hpp"

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
		typedef T														value_type;
		typedef Compare													value_compare;
		typedef Allocator												allocator_type;
	private:
		typedef std::allocator_traits<allocator_type>					alloc_traits;
		typedef Node<T>													NodeType;


	public:
		typedef typename Allocator::template rebind< Node<T> >::other	node_allocator;
		typedef Node<T>*												node_pointer;
		typedef typename Allocator::pointer         					pointer;
    	typedef typename Allocator::const_pointer  						const_pointer;
		typedef typename Allocator::reference         					reference;
    	typedef typename Allocator::const_reference  					const_reference;
    	typedef typename Allocator::size_type       					size_type;
    	typedef typename Allocator::difference_type						difference_type;

//////////-------------------------- ITERATORS ----------------------////////////////////
	
	public:
		typedef	treeIterator<T>											iterator;
		typedef	const_treeIterator<T>									const_iterator;
		typedef	ft::reverse_iterator<iterator>								reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef	bidirectional_iterator_tag								iterator_category;

		// typedef	const_treeReverseIterator<T>							const_reverse_iterator;
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
		RBTree(const Node<T>& node) : _size(0) { _begin_ptr = &_root_parent; *this = node; }
		RBTree(const RBTree& to_copy) : _size(0) { _begin_ptr = &_root_parent; *this = to_copy; }

		RBTree& operator=(const Node<T>& node) 
		{
			if (root() != &node)
			{
				vector<const Node<T>*>	ptr_vec;
				int						i = 0;

				if (root()){
					destroy_children(*(root()));
					delete_single_node(*(root()));
				}
				ptr_vec.push_back(&node);
				while (ptr_vec.size() > i)
				{
					if (ptr_vec[i]->left_child())
						ptr_vec.push_back(ptr_vec[i]->left_child());
					if ((ptr_vec[i]->right_child()))
						ptr_vec.push_back(ptr_vec[i]->right_child());
					this->insert((ptr_vec[i])->value());
					i++;
				}
			}
			return *this;
		}

		RBTree& operator=(const RBTree& tree)
		{
			if ((this != &tree) && tree.root())
			{
				vector<const Node<T>*>	ptr_vec;
				int						i = 0;

				if (root()){
					destroy_children(*(root()));
					delete_single_node(*(root()));
				}
				ptr_vec.push_back(tree.root());
				while (ptr_vec.size() > i)
				{
					if (ptr_vec[i]->left_child())
						ptr_vec.push_back(ptr_vec[i]->left_child());
					if ((ptr_vec[i]->right_child()))
						ptr_vec.push_back(ptr_vec[i]->right_child());
					this->insert((ptr_vec[i])->value());
					i++;
				}
			}
			return *this;
		}

		~RBTree(){
			if (root()){
				destroy_children(*(root()));
				delete_single_node(*(root()));
			}
		}

//////////--------------------- GETTERS & SETTERS--------------------////////////////////

		Node<T>*	root() const { return _root_parent.left_child(); }
		void		set_root(Node<T>* ptr) { _root_parent.set_left_child(ptr); }
		size_t		size() const { return _size; }
		size_t		confirm_size() const { return root()->size(); }
		void		set_begin_ptr(){
			Node<T>*	temp = root();
			while (temp->left_child()) 
				temp = temp->left_child();
			_begin_ptr = temp;
		}
		Node<T>*		get_end_ptr() const {
			Node<T>*	temp = root();
			while (temp->right_child()) 
				temp = temp->right_child();
			return temp;
		}

//////////-------------------------- INSERT ------------------------////////////////////

		Node<T>&	new_insert(const T& val)
		{
			_size++;
			if (_size == 1)
			{

				set_root(_node_alloc.allocate(1));
				_node_alloc.construct(root(), Node<T>(val));
				root()->set_parent(&_root_parent);
				root()->set_color(false);
				_root_parent.set_color(false);
				return *root();
			}
			return (insert(*root(), val));
		}

		Node<T>&	insert(Node<T>& node, const T& val)
		{
			Node<T>*			temp;
			temp = &node;

			while (temp)
			{
				if (Compare()(temp->value(), val)){
					if (Compare()(val, temp->value()))
						return _root_parent;
					else if (temp->right_child())
						temp = temp->right_child();
					else{
						temp->set_right_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->right_child(), Node<T>(val));
						temp->right_child()->set_parent(temp);
						temp = temp->right_child();
						break;
					}
				}
				else{
					if (!Compare()(val, temp->value()))
						return _root_parent;
					else if (temp->left_child())
						temp = temp->left_child();
					else{
						temp->set_left_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->left_child(), Node<T>(val));
						temp->left_child()->set_parent(temp);
						temp = temp->left_child();
						break;
					}
				}
			}
			return *temp;
		}

		Node<T>&	insert(const T& val)
		{
			Node<T>&	inserted = new_insert(val);
			Node<T>*	temp = &inserted;

			if (&inserted == &_root_parent)
				_size--;
			else if (inserted.parent_is_black())
			{ }
			else if (inserted.uncle_is_black())
				rotate_to_balance(inserted);
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
			set_begin_ptr();
			return inserted;
		}

//////////-------------------------- DELETE ------------------------////////////////////

		void	remove(Node<T>& node)
		{
			delete_single_node(node);
			set_begin_ptr();
			this->_size--;
		}

		void	remove(T value)
		{
			Node<T>*	temp = this->search(value);

			if (temp){
				delete_single_node(*temp);
				set_begin_ptr();
				this->_size--;
			}
		}

		void	destroy_children(Node<T>& node)
		{
			stack<Node<T>*>		temp;
			Node<T>*			current = &node;

			while (current || !(temp.empty()))
			{
				while (current)
				{
					temp.push(current);
					current = current->left_child();
				}
				while (!(temp.empty()) && !current)
				{
					current = temp.top()->right_child();
					if (temp.top() != &node)
					{
						_node_alloc.destroy(temp.top());
						_node_alloc.deallocate(temp.top(), 1);
					}
					temp.pop();
				}
			}
			node.set_right_child(nullptr);
			node.set_left_child(nullptr);
			_size = root()->size();
		}

		void	delete_single_node(Node<T>& node)
		{
			int			offspring	= node.count_children();
			Node<T>*	temp = &node;

			if (offspring == 1)
				delete_single_node(node.replace_value(node.single_child()));
			else if (offspring == 2)
				delete_single_node(node.replace_value(node.in_order_successor()));
			else{
				resolve_double_black(node);
				*(node.parent_branch()) = nullptr;
				this->_node_alloc.destroy(temp);
				this->_node_alloc.deallocate(temp, 1);
			}
		}

//////////------------------------ TRANSVERSE-----------------------////////////////////

		void	level_order_transverse() 
		{
			vector<Node<T>*>	ptr_vec;
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
			stack<const Node<T>*>	temp;
			const Node<T>*			current = root();

			while (current || !(temp.empty()))
			{
				while (current)
				{
					temp.push(current);
					current = current->left_child();
				}
				while (!(temp.empty()) && !current)
				{
					// std::cout << " ->" << temp.top()->value() << " bf: " << temp.top()->balance_factor();
					std::cout << " ->" << temp.top()->value() << "\t(" << temp.top()->color() << ", " 
						<< temp.top()->balance_factor() << ", " << temp.top()->parent()->value() << ")" << std::endl;
					current = temp.top()->right_child();
					temp.pop();
				}
			}
		}

		void	print_tree_by_level() const
		{
			vector<Node<T>*>	ptr_vec;
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
		}

//////////------------------------ HELPERS -----------------------////////////////////

		Node<T>*	search(const T& value)
		{
			Node<T>*	node = root();

			while (node != nullptr && node->value() != value)
			{
				if (Compare()(value, node->value()))
					node = node->left_child();
				else
					node = node->right_child();
			}
			return node;
		}

		int		determine_setup(Node<T>& node)
		{
			if (node.parent()->is_left() && node.is_left())
				return LL;
			else if (node.parent()->is_left() && node.is_right())
				return LR;
			else if (node.parent()->is_right() && node.is_left())
				return RL;
			return RR;
		}

		Node<T>&	predecessor(Node<T>& node)
		{
			Node<T>*	max;

			max = node->left_child();
			while (max->right_child())
				max = max->right_child();
			return *max;
		}

		Node<T>&	successor(Node<T>& node)
		{
			Node<T>*	min;

			min = node->right_child();
			while (min->left_child())
				min = min->left_child();
			return *min;
		}

		int	balance_factor(Node<T>& node)
		{
			return node.balance_factor();
		}

//////////------------------------ REBALANCE -----------------------////////////////////

		void	rotate_to_balance(Node<T>& node)
		{
			Node<T>**	grand_parent_position;
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

		void	resolve_double_black(Node<T>& node)
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

		int	double_black_case_type(Node<T>& node)
		{
			Node<T>*	sib = node.sibling();
			Node<T>*	close_neph = node.close_nephew();
			Node<T>*	distant_neph = node.distant_nephew();

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

		void	test_node()
		{
			// remove(79);
			// remove(18);
			// remove("B");
			// remove("B");
			// remove("CC");
			// remove("AA");
			// remove(78);
			// remove(28);
			// remove(35);/////////
			// remove(81);
			// remove(99);
			// remove(74);
			// remove(47);
			// remove(5);
			// remove(80);
			// remove(93);
			// remove(65);
			// remove(33);
			// remove(69);
			// remove(37);
			// remove(71);
			// remove(36);
			// remove(20);
			// remove(95);
			// remove(48);
			// remove(21);
			// remove(63);
			// remove(73);
			// remove(3);
			// remove(16);
			// remove(7);
			// remove(9);
			// remove(94);////
			// remove(55);
			// remove(14);
			// remove(6);
			// remove(61);
			// remove(27);/////
			// remove(89);
			// remove(49);
			// remove(66);
			// remove(82);
			PRINT("<<<<<--------->>>>>>", GREEN);
			print_tree_by_level();
			// remove(26);
			// remove(70);///
			// remove(68);
			// remove(58);
			// remove(2);
			// remove(44);
			// remove(88);
			// remove(85);
			// print_tree_in_order();
			// level_order_transverse();
		}

	protected:
		Node<T>						_root_parent;
		Node<T>*					_begin_ptr;
		size_t						_size;
		node_allocator				_node_alloc;
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