#ifndef VECITERATOR_HPP
#define VECITERATOR_HPP

#include <iostream>
#include <string>

#include "IteratorTraits.hpp"
#include "verbose.hpp"

namespace ft
{
	template<typename T>
	class vecIterator
	{
		//------------------------- Typedefs-----------------------------------------//
	public:
		typedef	T								value_type;
		typedef	std::ptrdiff_t					difference_type;
		typedef	value_type&						reference;
		typedef	const value_type& 				const_reference;
		typedef	T*								pointer;
		typedef	const T*						const_pointer;
		typedef	bidirectional_iterator_tag		iterator_category;

		//---------------------------------------------------------------------------//

	public:
		vecIterator(T* ptr = nullptr) : _ptr(ptr)						{ }
		vecIterator(const vecIterator& other) : _ptr(other.getPtr())	{ }
		~vecIterator(){}

		vecIterator&							operator=(T* ptr) { _ptr = ptr; return *this; }
		vecIterator&							operator=(vecIterator& other) { _ptr = other.getPtr(); return *this; }
		
		operator								pointer() const { return (_ptr); }

		bool									operator==(const vecIterator& rawIterator)const{return (_ptr == rawIterator.getConstPtr()); }
		bool									operator!=(const vecIterator& rawIterator)const{return (_ptr != rawIterator.getConstPtr()); }
		bool									operator>(const vecIterator& rawIterator)const{ return ( _ptr > rawIterator.getConstPtr()); }
		bool									operator>=(const vecIterator& rawIterator)const{return (_ptr >= rawIterator.getConstPtr()); }
		bool									operator<(const vecIterator& rawIterator)const{return (_ptr < rawIterator.getConstPtr()); }
		bool									operator<=(const vecIterator& rawIterator)const{return (_ptr <= rawIterator.getConstPtr()); }

		vecIterator&							operator+=(const difference_type& movement) { _ptr += movement; return (*this); }
		vecIterator&							operator-=(const difference_type& movement) { _ptr -= movement; return (*this); }
		vecIterator&							operator++() { ++_ptr; return (*this); }
		vecIterator&							operator--() { --_ptr; return (*this); }
		vecIterator								operator++(int) {vecIterator temp(*this); ++_ptr; return (temp); };
		vecIterator								operator--(int) {vecIterator temp(*this); --_ptr; return (temp); }
		vecIterator								operator+(const difference_type& movement) const { vecIterator temp(*this); temp += movement; return (temp); }
		vecIterator								operator-(const difference_type& movement) const { vecIterator temp(*this); temp -= movement; return (temp); }

		difference_type							operator-(const vecIterator& rawIterator) const { return (this->getConstPtr() - rawIterator.getConstPtr()); }

		T&										operator*(){ return *_ptr; }
		const T&								operator*() const { return *_ptr; }
		T*										operator->() const { return _ptr; }

		T*										getPtr() const { return _ptr; }
		const T*								getConstPtr() const { return _ptr; }

	protected:
		T*	_ptr;
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, vecIterator<T> iter) {out << iter.getConstPtr(); return out; }
}



#endif