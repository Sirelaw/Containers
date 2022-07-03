#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <string>
#include "Stack.hpp"
#include "Vector.hpp"
#include "Node.hpp"
#include "utils.hpp"

#define node_PARENT_BRANCH *(node.parent_branch())

namespace ft
{
	template <class T, class Compare = less<T> , class Allocator = std::allocator<T> >
	class BSTree
	{
	public:
		typedef typename Allocator::template rebind< Node<T> >::other	node_allocator;

		BSTree() : _size(0) { }
		BSTree(const Node<T>& node) : _size(node.size()) { *this = node; }
		BSTree(const BSTree& to_copy) : _size(to_copy.size()) { *this = to_copy; }
		virtual ~BSTree() {
			if (root())
				delete_node_and_children(*root());
		}

		BSTree& operator=(const Node<T>& node)
		{
			if (root() != &node)
			{
				vector<const Node<T>*>	ptr_vec;
				int						i = 0;

				if (root())
					delete_node_and_children(*root());
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

		BSTree& operator=(const BSTree& tree)
		{
			if ((this != &tree) && tree.root())
			{
				vector<const Node<T>*>	ptr_vec;
				int						i = 0;

				if (root())
					delete_node_and_children(*root());
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


		Node<T>*	root() const { return _root_parent.left_child(); }
		void		set_root(Node<T>* ptr) { _root_parent.set_left_child(ptr); }

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
			int					i = 0;

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

		Node<T>*	search(T value)
		{
			Node<T>*	node = root();

			while (node != nullptr && node->value() != value)
			{
				if (value < node->value())
					node = node->left_child();
				else
					node = node->right_child();
			}
			return node;
		}

		virtual Node<T>&	insert(T val)
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

		int	balance_factor(Node<T>& node)
		{
			return node.balance_factor();
		}

		virtual void	delete_single_node(Node<T>& node)
		{
			int			offspring	= node.count_children();
			Node<T>*	temp_ptr	= &node;

			if (offspring == 0){
				*(node.parent_branch()) = nullptr;
				_node_alloc.destroy(&node);
				_node_alloc.deallocate(temp_ptr, 1);
			}
			else if (offspring == 1){
				node.single_child().set_parent(node.parent());
				*(node.parent_branch()) = &(node.single_child());
				_node_alloc.destroy(&node);
				_node_alloc.deallocate(temp_ptr, 1);
			}
			else {
				temp_ptr = &(node.in_order_successor());
				node.set_value(temp_ptr->value());
				delete_single_node(*temp_ptr);
			}
		}

		virtual void	delete_node_and_children(Node<T>& node)
		{
			delete_children(node);
			delete_node(node);
		}

		virtual void	delete_node(Node<T>& node)
		{
			delete_single_node(node);
			_size--;
		}

		virtual void	delete_children(Node<T>& node)
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

		virtual void	remove(T value)
		{
			Node<T>*	temp = search(value);

			if (temp)
				delete_node(*temp);
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

		void	test_node()
		{
			PRINT("<<<<<--------->>>>>>", GREEN);
			print_tree_by_level();
		}

		size_t	size() const { return _size; }

	protected:
		Node<T>						_root_parent;
		size_t						_size;
		node_allocator				_node_alloc;
	};
}

#endif