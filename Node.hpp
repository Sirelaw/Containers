#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include "Stack.hpp"

namespace ft
{
	template <typename T>
	class Node
	{
		enum{
			LEFT,
			RIGHT
		};

	public:
		Node(T value = T(), Node* parent = nullptr, Node* right_child = nullptr, Node* left_child = nullptr)
			: _parent(parent), _right_child(right_child), _left_child(left_child), _value(value) {}
		Node(const Node& to_copy) { *this = to_copy; }
		~Node() {}

		Node& operator=(const Node& to_assign) { 
			if (this != &to_assign){
				_parent = nullptr;
				_right_child = nullptr;
				_left_child = nullptr;
				_parent = (to_assign.parent());
				_right_child = (to_assign.right_child());
				_left_child = (to_assign.left_child());
				_value = to_assign.value();
			}
			return *this;
		}

		void	reset_pointers(){
			_parent = nullptr;
			_right_child = nullptr;
			_left_child = nullptr;
		}


		Node*	search(T value)
		{
			Node*	node = this;

			while (node != nullptr && node->value() != value)
			{
				if (value < node->value())
					node = node->left_child();
				else
					node = node->right_child();
			}
			return node;
		}

		Node&	in_order_predecessor()
		{
			Node*	max = this;

			if (max->left_child())
				max = max->left_child();
			else
				return *this;
			while (max->right_child())
				max = max->right_child();
			return *max;
		}

		Node&	in_order_successor()
		{
			Node*	min = this;

			if (min->right_child())
				min = min->right_child();
			else
				return *this;
			while (min->left_child())
				min = min->left_child();
			return *min;
		}

		Node*	maximum() const
		{
			const Node*	max;

			max = this;
			while (max->right_child()){
				max = max->right_child();
			}
			return max;
		}

		Node*	minimum() const
		{
			const Node*	min;

			min = this;
			while (min->left_child())
				min = min->left_child();
			return min;
		}

		size_t	size() const
		{
			stack<const Node*>	temp;
			const Node*			current = this;
			int					count = 0;
			
			while (current || !(temp.empty()))
			{
				while (current)
				{
					temp.push(current);
					current = current->left_child();
				}
				while (!(temp.empty()) && !current)
				{
					++count;
					current = temp.top()->right_child();
					temp.pop();
				}
			}
			return count;
		}

		bool is_leaf() const { return !right_child() && !left_child(); }

		Node*	parent() const { return _parent; }
		Node*	right_child() const { return _right_child; }
		Node*	left_child() const { return _left_child; }
		T		value() const { return _value; }
		void	set_value(T value) { _value = value; }

		Node&	insert(T val)
		{
			Node*			temp;
			temp = this;
			int		i = 0;

			while (temp)
			{
				if (val > temp->value()){
					if (temp->right_child())
						temp = temp->right_child();//
					else{
						temp->_right_child = new Node(val);
						temp->_right_child->_parent = temp;
						temp = temp->_right_child;//
						break;
					}
				}
				else{
					if (temp->left_child())
						temp = temp->left_child();//
					else{
						temp->_left_child = new Node(val);
						temp->_left_child->_parent = temp;
						temp = temp->_left_child;//
						break;
					}
				}
			}
			return *temp;
		}

		void	right_rotate()
		{
			_left_child->_right_child = _left_child->parent();
			_left_child->_parent = this->_parent();
			this->_parent = this->left_child();
			this->_left_child = nullptr;
		}
		
		void	left_rotate()
		{
			_right_child->_left_child = _right_child->parent();
			_right_child->_parent = this->_parent();
			this->_parent = this->right_child();
			this->_right_child = nullptr;
		}

		void	balance_node()
		{}

		int	balance_factor() const
		{
			int	diff = 0;

			if (left_child())
				diff = _left_child->size();
			if (right_child())
				diff -= _right_child->size();
			return diff;
		}

		void	delete_children()
		{
			stack<Node*>	temp;
			Node*			current = new Node(*this);
			Node*			temp_current = current;

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
					if (temp.top()->value() != value())
						delete temp.top();
					temp.pop();
				}
			}
			_right_child = nullptr;
			_left_child = nullptr;
			delete temp_current;
		}

		void	delete_node_and_children()
		{
			Node*	temp;

			delete_children();
			if (_parent->right_child() && _parent->right_child()->value() == value()){
				temp = _parent->_right_child;
				_parent->_right_child = nullptr;
			}
			else if (_parent->left_child() && _parent->left_child()->value() == value()){
				temp = _parent->_left_child;
				_parent->_left_child = nullptr;
			}
			delete temp;
		}

		int		count_children() const
		{
			return ((bool) right_child() + (bool) left_child());
		}

		Node**	parent_branch()
		{
			if (_parent->left_child() && _parent->left_child()->value() == value())
				return &(_parent->_left_child);
			else if (_parent->right_child() && _parent->right_child()->value() == value())
				return &(_parent->_right_child);
			else
				return nullptr;
		}

		void	delete_node()
		{
			int		offspring = count_children();
			Node*	temp_ptr;

			if (offspring == 0)
				delete_node_and_children();
			else if (offspring == 1){
				temp_ptr = *(parent_branch());
				if (left_child())
					*(parent_branch()) = _left_child;
				else
					*(parent_branch()) = _right_child;
				delete	temp_ptr;
			}
			else {
				temp_ptr = &(in_order_successor());
				_value = temp_ptr->value();
				temp_ptr->delete_node();
			}
		}

	protected:
		Node*					_parent;
		Node*					_right_child;
		Node*					_left_child;
		T						_value;
	};
}

#endif