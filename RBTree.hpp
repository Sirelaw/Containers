#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <string>
#include "BSTree.hpp"

namespace ft
{
	template <typename T>
	class RBTree : public BSTree<T>
	{
	private:
		
	public:
		RBTree() : BSTree<T>(){}
		RBTree(const Node<T>& node) : BSTree<T>(node){}
		RBTree(const RBTree& to_copy) : BSTree<T>(to_copy) {} // needs to be implemented
		~RBTree(){}

		virtual Node<T>&	insert(T val)
		{
			Node<T>& temp = BSTree<T>::insert(val);
			if (temp.parent_is_black()) // If parent is black
				return temp;
			if (temp.uncle_is_red())
			{
				temp.uncle()->set_color(false);
				temp.parent()->set_color(false);
			}
			else
			{

			}
			return temp;
		}


		RBTree& operator=(const RBTree& to_assign);
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
*/

#endif