#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP

#include <iostream>
#include <string>

#include "IteratorTraits.hpp"
#include "Node.hpp"

namespace ft
{

	template<typename T>
	class treeIterator
	{
		//------------------ Typedefs------------------------------------------//
	public:
		typedef Node<T>													value_type;
		typedef Node<T>													node_type;
		typedef Node<T>*												node_pointer;
		typedef	std::ptrdiff_t											difference_type;
		typedef node_type&												reference;
		typedef	const node_type& 										const_reference;
		typedef node_type*												pointer;
		typedef	const node_type* 										const_pointer;
		typedef	bidirectional_iterator_tag								iterator_category;
	

	public:
		treeIterator(Node<T>* ptr = nullptr) 			{_ptr = ptr;}
		~treeIterator(){}

		Node<T>*	next_node(Node<T>* ptr)
		{
			if (ptr->right_child())
				return (&(ptr->in_order_successor()));
			while (ptr->is_right())
				ptr = ptr->parent();
			return ptr->parent();
		}

		Node<T>*	prev_node(Node<T>* ptr)
		{
			if (ptr->left_child())
				return (&(ptr->in_order_predecessor()));
			while (ptr->is_left() && ptr->parent())
				ptr = ptr->parent();
			if (ptr->parent() == nullptr)
				return ptr;
			return ptr->parent();
		}

		Node<T>&							operator=(Node<T>* ptr) { _ptr = ptr; return *this; }
		
		operator								pointer() const { return (_ptr); }

		bool									operator==(const Node<T>& rawIterator)const{return (_ptr == rawIterator.getConstPtr()); }
		bool									operator!=(const Node<T>& rawIterator)const{return (_ptr != rawIterator.getConstPtr()); }
		bool									operator<(const Node<T>& rawIterator)const{return (_ptr->value() < rawIterator.getConstPtr()->value()); }
		bool									operator<=(const Node<T>& rawIterator)const{return (_ptr->value() <= rawIterator.getConstPtr()->value()); }
		bool									operator>(const Node<T>& rawIterator)const{return (_ptr->value() > rawIterator.getConstPtr()->value()); }
		bool									operator>=(const Node<T>& rawIterator)const{return (_ptr->value() >= rawIterator.getConstPtr()->value()); }

		treeIterator<T>&							operator+=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				_ptr = next_node(_ptr); 
			return (*this);
		}
		treeIterator<T>&							operator-=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				_ptr = prev_node(_ptr); 
			return (*this);
		}
		treeIterator<T>&							operator++() { _ptr = next_node(_ptr); return (*this); }
		treeIterator<T>&							operator--() { _ptr = prev_node(_ptr); return (*this); }
		treeIterator<T>							operator++(int) {treeIterator<T> temp(*this); _ptr = next_node(_ptr); return (temp); }
		treeIterator<T>							operator--(int) {treeIterator<T> temp(*this); _ptr = prev_node(_ptr); return (temp); }
		treeIterator<T>							operator+(const difference_type& movement) const { treeIterator<T> temp(*this); temp += movement; return (temp); }
		treeIterator<T>							operator-(const difference_type& movement) const { treeIterator<T> temp(*this); temp -= movement; return (temp); }

		difference_type							operator-(const treeIterator<T>& rawIterator) const {
			difference_type		temp = 0;
			treeIterator<T>		temp_iter(*this);
			while (temp_iter.getConstPtr() != rawIterator.getConstPtr()){
				++temp_iter;
				++temp;
			}
			return (temp);
		}

		Node<T>&										operator*(){ return *_ptr; }
		const Node<T>&								operator*() const { return *_ptr; }
		Node<T>*										operator->() const { return _ptr; }

		Node<T>*										getPtr() const { return _ptr; }
		const Node<T>*								getConstPtr() const { return _ptr; }

	protected:
		Node<T>*	_ptr;
	};

	template<typename T>
	class treeReverseIterator : public treeIterator<T>
	{
		//------------------ Typedefs------------------------------------------//
	public:
		typedef	typename treeIterator<T>::difference_type							difference_type;

	public:
		treeReverseIterator(Node<T>* ptr = nullptr) : treeIterator<T>(ptr) {}
		treeReverseIterator(const Node<T>& rawIterator){ this->_ptr = rawIterator.getPtr(); }
		~treeReverseIterator() {};

		treeReverseIterator<T>&					operator=(const Node<T>& rawIterator) { this->_ptr = rawIterator.getPtr(); return (*this); }
		treeReverseIterator<T>&					operator=(Node<T>* ptr) { this->_ptr = ptr; return (*this); }

		treeReverseIterator<T>&							operator+=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				this->_ptr = prev_node(this->_ptr); 
			return (*this);
		}
		treeReverseIterator<T>&							operator-=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				this->_ptr = next_node(this->_ptr); 
			return (*this);
		}
		treeReverseIterator<T>&							operator++() { this->_ptr = treeIterator<T>::prev_node(this->_ptr); return (*this); }
		treeReverseIterator<T>&							operator--() { this->_ptr = treeIterator<T>::next_node(this->_ptr); return (*this); }
		treeReverseIterator<T>							operator++(int) {treeReverseIterator<T> temp(*this); this->_ptr = prev_node(this->_ptr); return (temp); }
		treeReverseIterator<T>							operator--(int) {treeReverseIterator<T> temp(*this); this->_ptr = next_node(this->_ptr); return (temp); }
		treeReverseIterator<T>							operator+(const difference_type& movement) const { treeReverseIterator<T> temp(*this); temp -= movement; return (temp); }
		treeReverseIterator<T>							operator-(const difference_type& movement) const { treeReverseIterator<T> temp(*this); temp += movement; return (temp); }

		difference_type							operator-(const treeIterator<T>& rawIterator) const {
			difference_type		temp = 0;
			treeIterator<T>		temp_iter(*this);
			while (temp_iter.getConstPtr() != rawIterator.getConstPtr()){
				++temp_iter;
				++temp;
			}
			return (temp);
		}

		treeIterator<T>							base() { treeIterator<T> forwardIterator(this->_ptr); ++forwardIterator; return (forwardIterator); }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, treeIterator<T> iter) {out << iter.getConstPtr(); return out; }
}


#endif