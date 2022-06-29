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
		//------------------------ Typedefs------------------------------------------//
	public:
		typedef T														value_type;
		typedef Node<T>													node_type;
		typedef Node<T>*														pointer;
		typedef	const Node<T>*											const_pointer;
		typedef Node<T>&												reference;
		typedef	const Node<T>& 											const_reference;
		typedef	std::ptrdiff_t											difference_type;
		typedef	bidirectional_iterator_tag								iterator_category;

		//---------------------------------------------------------------------------//
	

	public:
		treeIterator(Node<T>* ptr = nullptr) : _ptr(ptr)				{ }
		~treeIterator(){}

		Node<T>*	next_node(Node<T>* ptr)
		{
			if (!ptr->parent())
			{
				while (ptr->left_child())
					ptr = ptr->left_child();
				return ptr;
			}
			if (ptr->right_child())
				return (&(ptr->in_order_successor()));
			while (ptr->parent() && ptr->is_right())
				ptr = ptr->parent();
			if (!(ptr->parent()))
				return ptr;
			return ptr->parent();
		}

		Node<T>*	prev_node(Node<T>* ptr)
		{
			if (ptr->left_child())
				return (&(ptr->in_order_predecessor()));
			while (ptr->parent() && ptr->is_left())
				ptr = ptr->parent();
			if (!(ptr->parent()))
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
		Node<const T>&								operator*() const { return *_ptr; }
		Node<T>*										operator->() const { return _ptr; }

		Node<T>*										getPtr() const { return _ptr; }
		Node<const T>*								getConstPtr() const { return _ptr; }

	protected:
		Node<T>*	_ptr;
	};

		//------------------------ Const Iterator ------------------------------------------//
	template<typename T>
	class const_treeIterator
	{
	public:
		typedef T														value_type;
		typedef Node<T>													node_type;
		typedef const Node<T>*												pointer;
		typedef	const Node<T>*											const_pointer;
		typedef const Node<T>&												reference;
		typedef	const Node<T>& 											const_reference;
		typedef	std::ptrdiff_t											difference_type;
		typedef	bidirectional_iterator_tag								iterator_category;

		//---------------------------------------------------------------------------//
	

	public:
		const_treeIterator(const Node<T>* ptr = nullptr) 	: _ptr(ptr)		{ }
		~const_treeIterator(){}

		const Node<T>*	next_node(const Node<T>* ptr)
		{
			if (!ptr->parent())
			{
				while (ptr->left_child())
					ptr = ptr->left_child();
				return ptr;
			}
			if (ptr->right_child())
				return (ptr->right_child()->minimum());
			while (ptr->parent() && ptr->is_right())
				ptr = ptr->parent();
			if (!(ptr->parent()))
				return ptr;
			return ptr->parent();
		}

		const Node<T>*	prev_node(const Node<T>* ptr)
		{
			if (ptr->left_child())
				return (ptr->left_child()->maximum());
			while (ptr->parent() && ptr->is_left())
				ptr = ptr->parent();
			if (!(ptr->parent()))
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

		const_treeIterator<T>&							operator+=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				_ptr = next_node(_ptr); 
			return (*this);
		}
		const_treeIterator<T>&							operator-=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				_ptr = prev_node(_ptr); 
			return (*this);
		}
		const_treeIterator<T>&							operator++() { _ptr = next_node(_ptr); return (*this); }
		const_treeIterator<T>&							operator--() { _ptr = prev_node(_ptr); return (*this); }
		const_treeIterator<T>							operator++(int) {const_treeIterator<T> temp(*this); _ptr = next_node(_ptr); return (temp); }
		const_treeIterator<T>							operator--(int) {const_treeIterator<T> temp(*this); _ptr = prev_node(_ptr); return (temp); }
		const_treeIterator<T>							operator+(const difference_type& movement) const { const_treeIterator<T> temp(*this); temp += movement; return (temp); }
		const_treeIterator<T>							operator-(const difference_type& movement) const { const_treeIterator<T> temp(*this); temp -= movement; return (temp); }

		difference_type							operator-(const const_treeIterator<T>& rawIterator) const {
			difference_type		temp = 0;
			const_treeIterator<T>		temp_iter(*this);
			while (temp_iter.getConstPtr() != rawIterator.getConstPtr()){
				++temp_iter;
				++temp;
			}
			return (temp);
		}

		// Node<T>&										operator*(){ return *_ptr; }
		// Node<const T>&								operator*() const { return *_ptr; }
		const Node<T>*										operator->() const { return _ptr; }

		const Node<T>*										getPtr() const { return _ptr; }
		const Node<T>*								getConstPtr() const { return _ptr; }

	protected:
		const Node<T>*	_ptr;
	};
	//-----------------------------------------------------------------------------//

	template<typename T>
	class treeReverseIterator : public treeIterator<T>
	{
		//------------------ Typedefs------------------------------------------//
	public:
		typedef	typename treeIterator<T>::difference_type							difference_type;

	public:
		treeReverseIterator(const Node<T>* ptr = nullptr) : treeIterator<T>(ptr) {}
		treeReverseIterator(const Node<T>& rawIterator) : treeIterator<T>(rawIterator.getPtr()) { }
		~treeReverseIterator() {};

		treeReverseIterator<T>&					operator=(const Node<T>& rawIterator) { this->_ptr = rawIterator.getPtr(); return (*this); }
		treeReverseIterator<T>&					operator=(Node<T>* ptr) { this->_ptr = ptr; return (*this); }

		treeReverseIterator<T>&							operator+=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				this->_ptr = treeIterator<T>::prev_node(this->_ptr); 
			return (*this);
		}
		treeReverseIterator<T>&							operator-=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				this->_ptr = treeIterator<T>::next_node(this->_ptr); 
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

		//-------------------- Const Reverse Iterators ------------------------------------------//

	template<typename T>
	class const_treeReverseIterator : public const_treeIterator<T>
	{
		//------------------ Typedefs------------------------------------------//
	public:
		typedef	typename const_treeIterator<T>::difference_type							difference_type;

	public:
		const_treeReverseIterator(Node<T>* ptr = nullptr) : const_treeIterator<T>(ptr) {}
		const_treeReverseIterator(const const_treeIterator<T>& rawIterator){ this->_ptr = rawIterator.getPtr(); }
		~const_treeReverseIterator() {};

		const_treeReverseIterator<T>&					operator=(const Node<T>& rawIterator) { this->_ptr = rawIterator.getPtr(); return (*this); }
		const_treeReverseIterator<T>&					operator=(Node<T>* ptr) { this->_ptr = ptr; return (*this); }

		const_treeReverseIterator<T>&							operator+=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				this->_ptr = this->prev_node(this->_ptr); 
			return (*this);
		}
		const_treeReverseIterator<T>&							operator-=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				this->_ptr = this->next_node(this->_ptr); 
			return (*this);
		}

		const_treeReverseIterator<T>&							operator++() { this->_ptr = const_treeIterator<T>::prev_node(this->_ptr); return (*this); }
		const_treeReverseIterator<T>&							operator--() { this->_ptr = const_treeIterator<T>::next_node(this->_ptr); return (*this); }
		const_treeReverseIterator<T>							operator++(int) {const_treeReverseIterator<T> temp(*this); this->_ptr = prev_node(this->_ptr); return (temp); }
		const_treeReverseIterator<T>							operator--(int) {const_treeReverseIterator<T> temp(*this); this->_ptr = next_node(this->_ptr); return (temp); }
		const_treeReverseIterator<T>							operator+(const difference_type& movement) const { const_treeReverseIterator<T> temp(*this); temp -= movement; return (temp); }
		const_treeReverseIterator<T>							operator-(const difference_type& movement) const { const_treeReverseIterator<T> temp(*this); temp += movement; return (temp); }

		difference_type							operator-(const const_treeIterator<T>& rawIterator) const {
			difference_type		temp = 0;
			const_treeIterator<T>		temp_iter(*this);
			while (temp_iter.getConstPtr() != rawIterator.getConstPtr()){
				++temp_iter;
				++temp;
			}
			return (temp);
		}

		const_treeIterator<T>							base() { const_treeIterator<T> forwardIterator(this->_ptr); ++forwardIterator; return (forwardIterator); }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, treeIterator<T> iter) {out << iter.getConstPtr(); return out; }
}


#endif

/*

from: Node<std::__1::basic_string<char> > *const

to:   treeIterator<const std::__1::basic_string<char> >

*/