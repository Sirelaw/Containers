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
	enum{
		LL,
		LR,
		RL,
		RR
	};

	template <class T, class Compare = less<T> , class _Allocator = std::allocator<T> >
	class BSTree
	{
	public:
		BSTree() : _size(0) { }
		BSTree(const Node<T>& node) {*this = node; _size = node.size(); }
		BSTree(const BSTree& to_copy) { *this = to_copy;  _size = to_copy.size(); }
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
				set_root(new Node<T>(val));
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
						temp->set_right_child(new Node<T>(val));
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

		virtual void	delete_single_node(Node<T>& node)
		{
			int			offspring	= node.count_children();
			Node<T>*	temp_ptr	= &node;

			if (offspring == 0){
				*(node.parent_branch()) = nullptr;
				delete &node;
			}
			else if (offspring == 1){
				node.single_child().set_parent(node.parent());
				*(node.parent_branch()) = &(node.single_child());
				delete &node;
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
						delete temp.top();
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

		void	test_node()
		{
			remove(79);
			remove(18);
			remove(62);
			remove(10);
			remove(4);
			remove(42);
			remove(78);
			remove(28);
			remove(35);/////////
			remove(81);
			remove(99);
			remove(74);
			remove(47);
			remove(5);
			remove(80);
			remove(93);
			remove(65);
			remove(33);
			remove(69);
			remove(37);
			remove(71);
			remove(36);
			remove(20);
			remove(95);
			remove(48);
			remove(21);
			remove(63);
			remove(73);
			remove(3);
			remove(16);
			remove(7);
			remove(9);
			remove(94);////
			remove(55);
			remove(14);
			remove(6);
			remove(61);
			remove(27);/////
			remove(89);
			remove(49);
			remove(66);
			remove(82);
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

		size_t	size() const { return _size; }

	protected:
		Node<T>						_root_parent;
		size_t						_size;
		std::allocator< Node<T> >	_node_alloc;
	};
}

#endif