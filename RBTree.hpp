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
	
	template <typename T>
	class RBTree : public BSTree<T>
	{
	private:
		
	public:
		RBTree() : BSTree<T>(){}
		RBTree(const Node<T>& node) : BSTree<T>(node){}
		RBTree(const RBTree& to_copy) : BSTree<T>(to_copy) {} // needs to be implemented
		~RBTree(){}

		void	rotate_to_balance(Node<T>& node)
		{
			Node<T>**	grand_parent_position;
			int			setup = 0;

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

		virtual Node<T>&	insert(T val)
		{
			Node<T>&	inserted = BSTree<T>::insert(val);
			Node<T>*	temp = &inserted;
			int			setup = 0;
				int	i = 0;

			if (inserted.parent_is_black()) // If parent is black
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

		virtual void	remove(T value)
		{
			Node<T>*	temp = this->search(value);

			PRINT("IN RBT", RED);
			if (temp){
				delete_single_node(*temp);
				this->_size--;
			}
		}

		virtual void	delete_single_node(Node<T>& node)
		{
			int			offspring	= node.count_children();

			if (offspring == 1)
				delete_single_node(node.replace_value(node.single_child()));
			else if (offspring == 2)
				delete_single_node(node.replace_value(node.in_order_successor()));
			else{
				resolve_double_black(node);
				*(node.parent_branch()) = nullptr;
				delete &node;
			}
		}

		void	resolve_double_black(Node<T>& node)
		{
			bool	temp = node.parent()->color();

			switch (double_black_case_type(node))
			{
				case 1: // node is red
					PRINT("Case 1", RED);
					break ;
				case 2: // node is root
					PRINT("Case 2", RED);
					break;
				case 3: // S,D,C are all black
					PRINT("Case 3", RED);
					node.sibling()->set_color(red);
					if(node.parent_is_red())
						node.parent()->set_color(black);
					else
						resolve_double_black(*(node.parent()));
					break;
				case 4: // S is red
					PRINT("Case 4", RED);
					node.sibling()->set_color(black);
					node.parent()->set_color(red);
					if (node.is_left())
						node.parent()->left_rotate();
					else
						node.parent()->right_rotate();
					resolve_double_black(node);
					break;
				case 5: // S,D are black. C is red
					PRINT("Case 5", RED);
					node.sibling()->set_color(red);
					node.close_nephew()->set_color(black);
					if (node.is_left())
						node.sibling()->right_rotate();
					else
						node.sibling()->left_rotate();
				case 6: // D is red
					PRINT("Case 6", RED);
					node.parent()->set_color(node.sibling()->color());
					node.sibling()->set_color(temp);
					node.distant_nephew()->set_color(black);
					if (node.is_left())
						node.parent()->left_rotate();
					else
						node.parent()->right_rotate();			
					break;
				default:
					PRINT("Delete case not handled.", RED);
			}
		}

		int	double_black_case_type(Node<T>& node)
		{
			Node<T>*	sib = node.sibling();
			Node<T>*	par = node.parent();
			Node<T>*	close_neph = node.close_nephew();
			Node<T>*	distant_neph = node.distant_nephew();

			if (node.is_red())
				return 1;
			else if (&node == this->root())
				return 2;
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