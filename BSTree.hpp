#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <string>
#include "Stack.hpp"
#include "Node.hpp"

namespace ft
{
	template <typename T>
	class BSTree : public Node<T>
	{
	public:
		BSTree() : _root(nullptr), _size(0) {
			_root = new Node<T>();
		}
		BSTree(const Node<T>& node) : _root(nullptr), _size(0){
			_root = new Node<T>(node);
			_size = node.size();
		}

		BSTree(const BSTree& to_copy) { // deep copy
			// stack<Node<T>*>	temp;
			// Node<T>*			current = new Node<T>(*this);
			// Node<T>*			temp_current = current;

			// while (current || !(temp.empty()))
			// {
			// 	while (current)
			// 	{
			// 		temp.push(current);
			// 		current = current->left_child();
			// 	}
			// 	while (!(temp.empty()) && !current)
			// 	{
			// 		current = temp.top()->right_child();
			// 		if (temp.top()->value() != value())
			// 			delete temp.top();
			// 		temp.pop();
			// 	}
			// }
			// _right_child = nullptr;
			// _left_child = nullptr;
			// delete temp_current;
		}

		void	print_tree() const
		{
			stack<const Node<T>*>	temp;
			const Node<T>*			current = this;

			while (current || !(temp.empty()))
			{
				while (current)
				{
					temp.push(current);
					current = current->left_child();
				}
				while (!(temp.empty()) && !current)
				{
					std::cout << " v: " << temp.top()->value() << " bf: " << temp.top()->balance_factor();
					current = temp.top()->right_child();
					temp.pop();
				}
			}
			std::cout << std::endl;
		}

		int	balance_factor(Node<T>& node)
		{
			return node.balance_factor();
		}

		virtual ~BSTree() {
			_root->delete_children();
			delete _root;
		}

		void	delete_node_and_children(Node<T>& node)
		{
			node.delete_node_and_children();
			_size = _root->size();
		}

		void	delete_node(Node<T>& node)
		{
			node.delete_node();
			_size--;
		}

		void	delete_children(Node<T>& node)
		{
			node.delete_children();
			_size = _root->size();
		}

		void	test_node()
		{
			print_tree();
		}

		BSTree& operator=(const BSTree& to_assign);

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

		virtual Node<T>&	insert(T val)
		{
			_size++;
			// if (_size == 1)
			// {
			// 	this->reset_pointers();
			// 	this->set_value(val);
			// 	return *this;
			// }
			return (Node<T>::insert(val));
		}

		size_t	size() const { return _size; }

	private:
		Node<T>*					_root;
		size_t						_size;
		std::allocator< Node<T> >	_node_alloc;
	};
}

#endif