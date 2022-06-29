#ifndef VECITERATOR_HPP
#define VECITERATOR_HPP

#include <iostream>
#include <string>

#include "IteratorTraits.hpp"

namespace ft
{
	template<typename T>
	class vecIterator
	{
		//------------------ Typedefs------------------------------------------//
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
		vecIterator(T* ptr = nullptr) 			{_ptr = ptr;}
		~vecIterator(){}

		vecIterator<T>&							operator=(T* ptr) { _ptr = ptr; return *this; }
		
		operator								pointer() const { return (_ptr); }

		bool									operator==(const vecIterator<T>& rawIterator)const{return (_ptr == rawIterator.getConstPtr()); }
		bool									operator!=(const vecIterator<T>& rawIterator)const{return (_ptr != rawIterator.getConstPtr()); }
		bool									operator<(const vecIterator<T>& rawIterator)const{return (_ptr < rawIterator.getConstPtr()); }
		bool									operator<=(const vecIterator<T>& rawIterator)const{return (_ptr <= rawIterator.getConstPtr()); }
		bool									operator>(const vecIterator<T>& rawIterator)const{return (_ptr > rawIterator.getConstPtr()); }
		bool									operator>=(const vecIterator<T>& rawIterator)const{return (_ptr >= rawIterator.getConstPtr()); }

		vecIterator<T>&							operator+=(const difference_type& movement) { _ptr += movement; return (*this); }
		vecIterator<T>&							operator-=(const difference_type& movement) { _ptr -= movement; return (*this); }
		vecIterator<T>&							operator++() { ++_ptr; return (*this); }
		vecIterator<T>&							operator--() { --_ptr; return (*this); }
		vecIterator<T>							operator++(int) {vecIterator<T> temp(*this); ++_ptr; return (temp); };
		vecIterator<T>							operator--(int) {vecIterator<T> temp(*this); --_ptr; return (temp); }
		vecIterator<T>							operator+(const difference_type& movement) const { vecIterator<T> temp(*this); temp += movement; return (temp); }
		vecIterator<T>							operator-(const difference_type& movement) const { vecIterator<T> temp(*this); temp -= movement; return (temp); }

		difference_type							operator-(const vecIterator<T>& rawIterator) const { return (this->getPtr() - rawIterator.getPtr()); }

		T&										operator*(){ return *_ptr; }
		const T&								operator*() const { return *_ptr; }
		T*										operator->() const { return _ptr; }

		T*										getPtr() const { return _ptr; }
		const T*								getConstPtr() const { return _ptr; }

	protected:
		T*	_ptr;
	};

	template<typename T>
	class vecReverseIterator : public vecIterator<T>
	{
		//------------------ Typedefs------------------------------------------//
	public:
		typedef	typename vecIterator<T>::difference_type							difference_type;

	public:
		vecReverseIterator(T* ptr = nullptr) : vecIterator<T>(ptr) {}
		vecReverseIterator(const vecIterator<T>& rawIterator){ this->_ptr = rawIterator.getPtr(); }
		~vecReverseIterator() {};

		vecReverseIterator<T>&					operator=(const vecIterator<T>& rawIterator) { this->_ptr = rawIterator.getPtr(); return (*this); }
		vecReverseIterator<T>&					operator=(T* ptr) { this->_ptr = ptr; return (*this); }

		vecReverseIterator<T>&					operator+=(const difference_type& movement) { this->_ptr -= movement; return (*this); }
		vecReverseIterator<T>&					operator-=(const difference_type& movement) { this->_ptr += movement; return (*this); }
		vecReverseIterator<T>&					operator++() { --(this->_ptr); return (*this); }
		vecReverseIterator<T>&					operator--() { ++(this->_ptr); return (*this); }
		vecReverseIterator<T>					operator++(int) {vecReverseIterator<T> temp(*this); --this->_ptr; return (temp); }
		vecReverseIterator<T>					operator--(int) {vecReverseIterator<T> temp(*this); ++this->_ptr; return (temp); }
		vecReverseIterator<T>					operator+(const difference_type& movement) const { vecReverseIterator<T> temp(*this); temp -= movement; return (temp); }
		vecReverseIterator<T>					operator-(const difference_type& movement) const { vecReverseIterator<T> temp(*this); temp += movement; return (temp); }

		difference_type							operator-(const vecIterator<T>& rawIterator) const { return (rawIterator.getPtr() - this->getPtr()); }

		vecIterator<T>							base() { vecIterator<T> forwardIterator(this->_ptr); ++forwardIterator; return (forwardIterator); }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, vecIterator<T> iter) {out << iter.getConstPtr(); return out; }
}


#endif