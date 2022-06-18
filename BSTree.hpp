#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <string>
#include "Stack.hpp"
#include "Vector.hpp"
#include "Node.hpp"

#define node_PARENT_BRANCH *(node.parent_branch())

namespace ft
{
	template <typename T>
	class BSTree : public Node<T>
	{
	public:
		BSTree() : _size(0) { }
		BSTree(const Node<T>& node) {*this = node; _size = node.size(); }
		BSTree(const BSTree& to_copy) { *this = to_copy;  _size = to_copy.size(); }
		virtual ~BSTree() {
			if (root())
				delete_node_and_children(*root());
		}

		BSTree& operator=(const Node<T>& to_assign)
		{
			if (root() != &to_assign)
			{
				vector<const Node<T>*>	ptr_vec;
				int						i = 0;

				if (root())
					delete_node_and_children(*root());
				ptr_vec.push_back(&to_assign);
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

		BSTree& operator=(const BSTree& to_assign)
		{
			if ((this != &to_assign) && to_assign.root())
			{
				vector<const Node<T>*>	ptr_vec;
				int						i = 0;

				if (root())
					delete_node_and_children(*root());
				ptr_vec.push_back(to_assign.root());
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


		void	level_order_transverse() 
		{

			if (!root())
				return;
			vector<Node<T>*>	ptr_vec;
			int					i = 0;

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


		Node<T>*	root() const { return this->left_child(); }
		void		set_root(Node<T>* ptr) { this->set_left_child(ptr); }

		void	print_tree() const
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
					std::cout << " ->" << temp.top()->value() << " bf: " << temp.top()->balance_factor();
					current = temp.top()->right_child();
					temp.pop();
				}
			}
			std::cout << std::endl;
		}

		virtual Node<T>&	insert(T val)
		{
			_size++;
			if (_size == 1)
			{
				set_root(new Node<T>(val));
				root()->set_parent(this);
				root()->set_color(false);
				this->set_color(false);
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
				if (val > temp->value()){
					if (temp->right_child())
						temp = temp->right_child();//
					else{
						temp->set_right_child(new Node<T>(val));
						temp->right_child()->set_parent(temp);
						temp = temp->right_child();//
						break;
					}
				}
				else{
					if (temp->left_child())
						temp = temp->left_child();//
					else{
						temp->set_left_child(new Node<T>(val));
						temp->left_child()->set_parent(temp);
						temp = temp->left_child();//
						break;
					}
				}
			}
			return *temp;
		}

		int	balance_factor(Node<T>& node)
		{
			return node.balance_factor();
		}


		void	delete_single_node(Node<T>& node)
		{
			int			offspring	= node.count_children();
			Node<T>*	temp_ptr	= &node;

			if (offspring == 0){
				*(node.parent_branch()) = nullptr;
				delete &node;
			}
			else if (offspring == 1){
				temp_ptr = *(node.parent_branch());
				if (node.left_child())
					*(node.parent_branch()) = node.left_child();
				else
					*(node.parent_branch()) = node.right_child();
				delete temp_ptr;
			}
			else {
				temp_ptr = &(node.in_order_successor());
				node.set_value(temp_ptr->value());
				delete_single_node(*temp_ptr);
			}
		}

		void	delete_node_and_children(Node<T>& node)
		{
			delete_children(node);
			delete_node(node);
		}

		void	delete_node(Node<T>& node)
		{
			delete_single_node(node);
			_size--;
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
						delete temp.top();
					temp.pop();
				}
			}
			node.set_right_child(nullptr);
			node.set_left_child(nullptr);
			_size = root()->size();
		}

		void	test_node()
		{
			// (root()->search(23)).left_rotate();
			// (root()->search(25)).right_rotate();
			// (root()->search(18)).right_rotate();
			// delete_node(root()->search(23));
			// print_tree();
			// level_order_transverse();
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

		size_t	size() const { return _size; }

	private:
		size_t						_size;
		std::allocator< Node<T> >	_node_alloc;
	};
}

#endif