#ifndef NODE_HPP
#define NODE_HPP

#include "../Stack.hpp"

namespace ft
{
	template <typename T>
	class Node
	{
	public:
		typedef T														value_type;
		typedef Node<T>													node_type;
		typedef Node<T>*												pointer;
		typedef	const Node<T>*											const_pointer;
		typedef Node<T>&												reference;
		typedef	const Node<T>& 											const_reference;
		typedef	std::ptrdiff_t											difference_type;

	public:
		Node(T value = T(), Node* parent = nullptr, Node* right_child = nullptr, Node* left_child = nullptr)
			: _parent(parent), _right_child(right_child), _left_child(left_child), _value(value), _color(true) {}
		Node(const Node& other) : _parent(other.parent()), _right_child(other.right_child()),
									_left_child(other.left_child()) , _value(other.value()), _color(other.color()) { }
		~Node() { }

		Node& operator=(const Node& to_assign) 
		{ 
			if (this != &to_assign) {
				_parent = (to_assign.parent());
				_right_child = (to_assign.right_child());
				_left_child = (to_assign.left_child());
				_value = to_assign.value();
				_color = to_assign.color();
			}
			return *this;
		}

		Node&	swap_node( Node& other)
		{
			Node*	this_parent = this->parent();
			Node*	this_left_child = this->left_child();
			Node*	this_right_child = this->right_child();
			bool	this_color = this->color();
			Node*	other_parent = other.parent();
			Node*	other_left_child = other.left_child();
			Node*	other_right_child = other.right_child();
			bool	other_color = other.color();

			*(this->parent_branch()) = &other;
			if (left_child() == &other || right_child() == &other)
			{
				if (left_child() == &other){
					other.link_left_child(this);
					other.link_right_child(this_right_child);
				}
				else{
					other.link_right_child(this);
					other.link_left_child(this_left_child);
				}
				other.set_parent(this_parent);
				this->set_parent(&other);
				this->link_right_child(other_right_child);
				this->link_left_child(other_left_child);
			}
			else
			{
				*(other.parent_branch()) = this;
				other.set_parent(this_parent);
				other.link_left_child(this_left_child);
				other.link_right_child(this_right_child);
				this->set_parent(other_parent);
				this->link_left_child(other_left_child);
				this->link_right_child(other_right_child);
			}
			this->set_color(other_color);
			other.set_color(this_color);
			return *this;
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

		const Node*	maximum() const
		{
			const Node*	max;

			max = this;
			while (max->right_child()){
				max = max->right_child();
			}
			return max;
		}

		const Node*	minimum() const
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

		bool 		is_leaf() const { return !right_child() && !left_child(); }
		bool		is_red() const {return _color; }
		bool		is_black() const {return !_color; }
		int			count_children() const { return ((bool) right_child() + (bool) left_child()); }
		Node*		parent() const { return _parent; }
		Node*		right_child() const { return _right_child; }
		Node*		left_child() const { return _left_child; }
		T&			value() { return _value; }
		const T&	value() const { return _value; }
		bool		color() const { return _color; }
		bool		color(Node* ptr) const { if(ptr) return ptr->_color; return false; }
		void		set_parent(Node* ptr) { _parent = ptr; }
		void		link_right_child(Node* ptr) { _right_child = ptr; if (ptr) ptr->set_parent(this); }
		void		link_left_child(Node* ptr) { _left_child = ptr; if (ptr) ptr->set_parent(this); }
		void		set_value(T value) { _value = value; }
		void		set_color(bool color) { _color = color; }
		bool		is_right() const { return !is_left(); }
		bool		is_left() const
		{
			if (_parent->left_child() == this)
				return true;
			return false;
		}

		Node*	close_nephew()
		{
			Node*	sib = sibling();
			if (sib)
			{
				if (is_left())
					return sib->left_child();
				return sib->right_child();
			}
			return nullptr;
		}

		Node*	distant_nephew()
		{
			Node*	sib = sibling();
			if (sib)
			{
				if (is_left())
					return sib->right_child();
				return sib->left_child();
			}
			return nullptr;
		}

		bool	close_nephew_color() const { return color(close_nephew()); }
		bool	distant_nephew_color() const { return color(distant_nephew()); }

		Node*	sibling() const
		{
			if (is_left())
				return parent()->right_child();
			return parent()->left_child();
		}
		
		Node*	uncle() const 
		{ 
			if (parent()->is_left()) 
				return _parent->parent()->right_child(); 
			return _parent->parent()->left_child();
		}

		Node**	parent_branch()
		{
			if (is_left())
				return &(_parent->_left_child);
			return &(_parent->_right_child);
		}

		bool	parent_is_black() const { return !(parent()->color()); }
		bool	parent_is_red() const { return (parent()->color()); }
		bool	uncle_is_black() const { return !uncle_is_red(); }
		bool	uncle_is_red() const
		{
			if (uncle())
				return uncle()->color();
			return false;
		}

		Node&	single_child()
		{
			if (left_child())
				return *(left_child());
			return *(right_child());
		}

		void	right_rotate()
		{
			Node*	temp = left_child()->right_child();

			*(parent_branch()) = this->left_child();
			_left_child->_parent = this->parent();
			left_child()->link_right_child(this);
			this->_left_child = temp;
			if (temp)
				temp->_parent = this;
		}
		
		void	left_rotate()
		{
			Node*	temp = right_child()->left_child();

			*(parent_branch()) = this->right_child();
			_right_child->_parent = this->parent();
			right_child()->link_left_child(this);
			this->_right_child = temp;
			if (temp)
				temp->_parent = this;
		}

		int	balance_factor() const
		{
			int	diff = 0;

			if (left_child())
				diff = _left_child->size();
			if (right_child())
				diff -= _right_child->size();
			return diff;
		}

		T	value_pointer() { return &_value; }

	private:
		Node*					_parent;
		Node*					_right_child;
		Node*					_left_child;
		T						_value;
		bool					_color;
	};
}

#endif