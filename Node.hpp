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
			: _parent(parent), _right_child(right_child), _left_child(left_child), _value(value), _color(true) {}
		Node(const Node& to_copy) { *this = to_copy; }
		~Node() {}

		Node& operator=(const Node& to_assign) { 
			if (this != &to_assign){
				_parent = (to_assign.parent());
				_right_child = (to_assign.right_child());
				_left_child = (to_assign.left_child());
				_value = to_assign.value();
				_color = to_assign.color();
			}
			return *this;
		}

		void	reset_pointers(){
			_parent = nullptr;
			_right_child = nullptr;
			_left_child = nullptr;
		}


		Node&	search(T value)
		{
			Node*	node = this;

			while (node != nullptr && node->value() != value)
			{
				if (value < node->value())
					node = node->left_child();
				else
					node = node->right_child();
			}
			return *node;
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

		virtual size_t	size() const
		{
			stack<const Node*>	temp;
			Node*				temp_right = nullptr;
			Node*				temp_left = nullptr;
			int					count = 0;

			temp.push(this);
			while (!(temp.empty()))
			{
				temp_right = temp.top()->right_child();
				temp_left = temp.top()->left_child();
				temp.pop();
				if (temp_right)
					temp.push(temp_right);
				if (temp_left)
					temp.push(temp_left);
				++count;
			}
			return count;
		}

		bool is_leaf() const { return !right_child() && !left_child(); }

		Node*	parent() const { return _parent; }
		Node*	right_child() const { return _right_child; }
		Node*	left_child() const { return _left_child; }
		T		value() const { return _value; }
		bool	color() const { return _color; }
		void	set_parent(Node* ptr) { _parent = ptr; }
		void	set_right_child(Node* ptr) { _right_child = ptr; }
		void	set_left_child(Node* ptr) { _left_child = ptr; }
		void	set_value(T value) { _value = value; }
		void	set_color(bool color) { _color = color; }

		void	right_rotate()
		{
			Node*	temp = left_child()->right_child();

			*(parent_branch()) = this->left_child();
			_left_child->_parent = this->parent();
			_left_child->_right_child = this;
			this->_parent = this->left_child();
			this->_left_child = temp;
		}
		
		void	left_rotate()
		{
			Node*	temp = right_child()->left_child();

			*(parent_branch()) = this->right_child();
			_right_child->_parent = this->parent();
			_right_child->_left_child = this;
			this->_parent = this->right_child();
			this->_right_child = temp;
		}

		bool	is_left()
		{
			if (_parent->left_child() == this)
				return true;
			return false;
		}

		bool	parent_is_black() { return !(parent()->color()); }
		bool	parent_is_red() { return (parent()->color()); }

		bool	uncle_is_red()
		{
			if (uncle())
				return uncle()->color();
			return false;
		}

		bool	uncle_is_black() { return !uncle_is_red(); }

		Node*	uncle()
		{
			if (is_left())
				return _parent->right_child();
			return _parent->left_child();
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

		int		count_children() const { return ((bool) right_child() + (bool) left_child()); }

		Node**	parent_branch()
		{
			if (is_left())
				return &(_parent->_left_child);
			return &(_parent->_right_child);
		}

	protected:
		Node*					_parent;
		Node*					_right_child;
		Node*					_left_child;
		T						_value;
		bool					_color;
	};
}

#endif