#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <string>
#include "BSTree.hpp"

namespace ft
{
	template <typename T>
	class AVLTree : public BSTree<T>
	{
	private:
		
	public:
		AVLTree() : BSTree<T>(){}
		AVLTree(const Node<T>& node) : BSTree<T>(node){}
		AVLTree(const AVLTree& to_copy) {} // needs to be implemented
		~AVLTree(){}

		virtual Node<T>&	insert(T val)
		{
			Node<T>& temp = BSTree<T>::insert(val);
			std::cout << "Inserted " << temp.value() << "\t" << "balance_factor: " << this->balance_factor(temp) << std::endl;
			return temp;
		}


		AVLTree& operator=(const AVLTree& to_assign);
	};
}

#endif