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
		typedef node_type*												pointer;
		typedef	const pointer											const_pointer;
		typedef node_type&												reference;
		typedef	const node_type& 										const_reference;
		typedef	std::ptrdiff_t											difference_type;
		typedef	bidirectional_iterator_tag								iterator_category;

		//---------------------------------------------------------------------------//
	

	public:
		treeIterator(pointer ptr = nullptr) : _ptr(ptr)				{ }
		treeIterator(const treeIterator& other) : _ptr(other.getPtr())	{ }
		~treeIterator(){}
protected:
		pointer	next_node(pointer ptr)
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

		pointer	prev_node(pointer ptr)
		{
			if (ptr->left_child())
				return (&(ptr->in_order_predecessor()));
			while (ptr->parent() && ptr->is_left())
				ptr = ptr->parent();
			if (!(ptr->parent()))
				return ptr;
			return ptr->parent();
		}
public:
		treeIterator&							operator=(const treeIterator& other) { _ptr = other.getPtr(); return *this; }

		operator								pointer() const { return (_ptr); }

		bool									operator==(const treeIterator& other)const{return (_ptr == other.getConstPtr()); }
		bool									operator!=(const treeIterator& other)const{return (_ptr != other.getConstPtr()); }
		// bool									operator<(const treeIterator& other)const{return (_ptr->value() < other.getConstPtr()->value()); }
		// bool									operator<=(const treeIterator& other)const{ return !(other < *this); }
		// bool									operator>=(const treeIterator& other)const{ return !(*this < other); }
		// bool									operator>(const treeIterator& other)const{ return (other < *this); }

		treeIterator&							operator+=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				_ptr = next_node(_ptr); 
			return (*this);
		}
		treeIterator&							operator-=(const difference_type& movement) {
			difference_type temp = movement;
			while (temp--)
				_ptr = prev_node(_ptr); 
			return (*this);
		}
		treeIterator&							operator++() { _ptr = next_node(_ptr); return (*this); }
		treeIterator&							operator--() { _ptr = prev_node(_ptr); return (*this); }
		treeIterator							operator++(int) {treeIterator temp(*this); _ptr = next_node(_ptr); return (temp); }
		treeIterator							operator--(int) {treeIterator temp(*this); _ptr = prev_node(_ptr); return (temp); }
		treeIterator							operator+(const difference_type& movement) const { treeIterator temp(*this); temp += movement; return (temp); }
		treeIterator							operator-(const difference_type& movement) const { treeIterator temp(*this); temp -= movement; return (temp); }

		difference_type							operator-(const treeIterator& rawIterator) const {
			difference_type		temp = 0;
			treeIterator		temp_iter(*this);
			while (temp_iter.getConstPtr() != rawIterator.getConstPtr()){
				++temp_iter;
				++temp;
			}
			return (temp);
		}

		pointer										operator*(){ return this->_ptr; }
		const_pointer								operator*() const { return this->_ptr; }
		value_type*										operator->() const { return &(this->_ptr->value()); }
		value_type*										operator&() const { return &(this->_ptr->value()); }

		pointer											getPtr() const { return _ptr; }
		const pointer									getConstPtr() const { return _ptr; }

	protected:
		pointer	_ptr;
	};

		//------------------------ Const Iterator ------------------------------------------//
	template<typename T>
	class const_treeIterator
	{
	public:
		typedef T														value_type;
		typedef Node<T>													node_type;
		typedef treeIterator<T>											treeIterator;
		typedef const node_type*										const_pointer;
		typedef	const_pointer											pointer;
		typedef	const node_type& 										const_reference;
		typedef const_reference											reference;
		typedef	std::ptrdiff_t											difference_type;
		typedef	bidirectional_iterator_tag								iterator_category;

		//---------------------------------------------------------------------------//
	

	public:
		const_treeIterator(const pointer ptr = nullptr)	: _ptr(ptr)		{ }
		const_treeIterator(const const_treeIterator& other) : _ptr(other.getPtr())	{ }
		const_treeIterator(const treeIterator& other) : _ptr(other.getConstPtr()) { }
		~const_treeIterator(){}
	protected:
		const pointer	next_node(pointer ptr)
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

		const pointer	prev_node(pointer ptr)
		{
			if (ptr->left_child())
				return (ptr->left_child()->maximum());
			while (ptr->parent() && ptr->is_left())
				ptr = ptr->parent();
			if (!(ptr->parent()))
				return ptr;
			return ptr->parent();
		}
public:
		const_treeIterator&								operator=(const const_treeIterator& other) { _ptr = other.getPtr(); return *this; } /////////

		operator										pointer() const { return (_ptr); }

		bool											operator==(const Node<T>& rawIterator)const{return (_ptr == rawIterator.getConstPtr()); }
		bool											operator!=(const Node<T>& rawIterator)const{return (_ptr != rawIterator.getConstPtr()); }
		// bool											operator<(const Node<T>& rawIterator)const{return (_ptr->value() < rawIterator.getConstPtr()->value()); }
		// bool											operator<=(const Node<T>& rawIterator)const{return (_ptr->value() <= rawIterator.getConstPtr()->value()); }
		// bool											operator>(const Node<T>& rawIterator)const{return (_ptr->value() > rawIterator.getConstPtr()->value()); }
		// bool											operator>=(const Node<T>& rawIterator)const{return (_ptr->value() >= rawIterator.getConstPtr()->value()); }

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

		difference_type									operator-(const const_treeIterator<T>& rawIterator) const {
			difference_type		temp = 0;
			const_treeIterator<T>		temp_iter(*this);
			while (temp_iter.getConstPtr() != rawIterator.getConstPtr()){
				++temp_iter;
				++temp;
			}
			return (temp);
		}

		const_pointer									operator*() const { return _ptr; }
		const value_type*								operator->() const { return &(this->_ptr->value()); }
		const pointer									getPtr() const { return _ptr; }
		const pointer									getConstPtr() const { return _ptr; }

	protected:
		pointer	_ptr;
	};

	//-----------------------------------------------------------------------------//

	template<typename T>
	std::ostream& operator<<(std::ostream& out, treeIterator<T> iter) {out << iter.getConstPtr(); return out; }
}


#endif
