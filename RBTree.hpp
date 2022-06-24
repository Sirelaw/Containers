#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <string>
#include "BSTree.hpp"

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

	template <class T, class less, class Allocator >
	class RBTree : public BSTree<T, less, Allocator >
	{
	private:
		
	public:
		RBTree() : BSTree<T, less, Allocator>(){}
		RBTree(const Node<T>& node) : BSTree<T, less, Allocator>(node){}
		RBTree(const RBTree& to_copy) : BSTree<T, less, Allocator>(to_copy) {} // needs to be implemented
		~RBTree(){}

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

			max = &node;
			if (max->left_child())
				max = node.left_child();
			else
				return node;
			while (max->right_child())
				max = max->right_child();
			return *max;
		}

		Node<T>&	successor(Node<T>& node)
		{
			Node<T>*	min;

			min = &node;
			if (min->right_child())
				min = node.right_child();
			else{
				while(min->parent()->value() < node.value())
					min = min->parent();
				min = min->parent();
				return *min;
			}
			while (min->left_child())
				min = min->left_child();
			return *min;
		}

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

		virtual Node<T>&	new_insert(T val)
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

		Node<T>&	insert(Node<T>& node, T val)
		{
			Node<T>*			temp;
			temp = &node;

			while (temp)
			{
				if (Compare()(temp->value(), val)){
					if (temp->right_child())
						temp = temp->right_child();//
					else if (Compare()(temp->value(), val) == Compare()(val, temp->value()))
						break;
					else{
						temp->set_right_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->right_child(), Node<T>(val));
						temp->right_child()->set_parent(temp);
						temp = temp->right_child();//
						break;
					}
				}
				else{
					if (temp->left_child())
						temp = temp->left_child();//
					else if (Compare()(temp->value(), val) == Compare()(val, temp->value()))
						break;
					else{
						temp->set_left_child(_node_alloc.allocate(1));
						_node_alloc.construct(temp->left_child(), Node<T>(val));
						temp->left_child()->set_parent(temp);
						temp = temp->left_child();//
						break;
					}
				}
			}
			return *temp;
		}

		virtual Node<T>&	insert(T val)
		{
			Node<T>&	inserted = new_insert(val);
			Node<T>*	temp = &inserted;
			int			setup = 0;
				int	i = 0;

			if (inserted.parent_is_black())
				return inserted;
			else if (inserted.uncle_is_black())
			{
				rotate_to_balance(inserted);
				return inserted;
			}
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
			return inserted;
		}

		void	remove(Node<T>& node)
		{
			delete_single_node(node);
			this->_size--;
		}

		virtual void	remove(T value)
		{
			Node<T>*	temp = this->search(value);

			if (temp){
				delete_single_node(*temp);
				this->_size--;
			}
		}

		virtual void	delete_single_node(Node<T>& node)
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

/*
	case 1 & 2: node is red || node is root
	case 3: 	S,D,C are all black
	case 4:		S is red
	case 5:		S,D are black. C is red
	case 6:		D is red
*/

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
			Node<T>*	par = node.parent();
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

		void	delete_node_and_children(Node<T>& node)
		{
			delete_children(node);
			remove(node);
		}

		void	delete_children(Node<T>& node)
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
						remove(*(temp.top()));
					temp.pop();
				}
			}
		}

		int	balance_factor(Node<T>& node)
		{
			return node.balance_factor();
		}

		size_t	size() const { return _size; }

	protected:
		Node<T>						_root_parent;
		size_t						_size;
		node_allocator				_node_alloc;
	};

}

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