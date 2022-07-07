#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>
#include "VecIterator.hpp"
#include "IteratorTraits.hpp"
#include "utils.hpp"

#include "verbose.hpp"

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		//------------------ Typedefs------------------------------------------//
		typedef	T										value_type;
		typedef	Allocator								allocator_type;
		typedef	std::size_t								size_type;
		typedef	std::ptrdiff_t							difference_type;
		typedef	value_type&								reference;
		typedef	const value_type& 						const_reference;
		typedef	typename Allocator::pointer				pointer;
		typedef	typename Allocator::const_pointer		const_pointer;
		typedef	vecIterator<T>							iterator;
		typedef	vecIterator<const T>					const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		//------------------ Iterator Member Functions ------------------------//
	public:
		iterator								begin(){ return iterator(_vec); }
		iterator								end(){ return iterator(_vec + _size); }
		const_iterator							cbegin() const { return const_iterator(_vec); }
		const_iterator							cend() const { return const_iterator(_vec + _size); }
		reverse_iterator						rbegin(){ return reverse_iterator(end()); }
		reverse_iterator						rend(){ return reverse_iterator(begin()); }
		const_reverse_iterator					crbegin() const { return const_reverse_iterator(cend()); }
		const_reverse_iterator					crend() const { return const_reverse_iterator(cbegin()); }

		//----------------------- Member Functions ----------------------------//
	public:
		vector() : _capacity(0), _size(0), _vec(nullptr) { }

		explicit vector( const Allocator& alloc ) : _capacity(0), _size(0), _vec(nullptr) 
		{
			_alloc = alloc;
		}

		explicit vector ( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) 
			: _capacity(count), _size(count), _vec(nullptr) {
			_alloc = alloc;
			if (_capacity)
				_vec = _alloc.allocate(capacity());
			for (iterator iter = begin(); iter < end(); iter++)
				_alloc.construct(iter, T(value));
		}
		
		template <class InputIt>
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = nullptr)
			: _capacity(0), _size(0), _vec(nullptr) 
		{
			_alloc = alloc;
			assign(first, last);
		}

		vector(const vector& to_copy) : _capacity(0), _size(0), _vec(nullptr) 
		{
			*this = to_copy;
		}

		~vector() 
		{
			clear();
			if (_vec)
				_alloc.deallocate(_vec, capacity());
			_vec = nullptr;
		}

		vector& 								operator=(const vector& other){
			if (this != &other)
			{
				iterator	temp;

				this->clear();
				if (_vec)
					_alloc.deallocate(_vec, capacity());
				_size = other.size();
				_capacity = other.capacity();
				_alloc = Allocator(other.get_allocator());
				_vec = _alloc.allocate(capacity());
				temp = begin();
				for (const_iterator iter = other.cbegin(); iter < other.cend(); iter++, temp++)
					_alloc.construct(temp, T(*iter));
			}
			return (*this);
		}
		reference								operator[](size_type pos){ return *(begin().getPtr() + pos); }
		const_reference							operator[](size_type pos) const { return *(cbegin().getConstPtr() + pos); }

		void 									assign( size_type count, const T& value )
		{
			this->clear();
			_size = count;
			if (count > capacity()){
				if (_vec)
					_alloc.deallocate(_vec, capacity());
				_vec = _alloc.allocate(count);
				_capacity = count;
			}
			for(iterator iter = begin(); iter != end() ; ++iter)
				_alloc.construct(iter, T(value));
		}

		template< class InputIt >
		void assign( InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = nullptr )
		{
			size_type	count = last - first;
		
			this->clear();
			_size = count;
			if (count > capacity()){
				if (_vec)
					_alloc.deallocate(_vec, capacity());
				_vec = _alloc.allocate(count);
				_capacity = count;
			}
			for(iterator iter = begin(); iter != end() ; ++iter, ++first)
				_alloc.construct(iter, T(*first));
		}

		reference 								at( size_type pos ){
			if (pos >= size())
				throw std::out_of_range("ft::vector::out_of_range");
			return *(begin().getPtr() + pos);	
		}

		const_reference 						at( size_type pos ) const {
			if (pos >= size())
				throw std::out_of_range("ft::vector::out_of_range");
			return *(cbegin().getConstPtr() + pos);	
		}

		reference								front(){ return *(begin()); }
		const_reference							front() const { return *(cbegin()); }
		reference								back(){ return *(end() - 1); }
		const_reference							back() const { return *(cbegin() - 1); }
		T*										data(){ return begin().getPtr(); }
		const T*								data() const { return cbegin().getConstPtr(); }
		bool									empty() const { return size() == 0; }
		size_type								max_size() const { return std::min<size_type>(_alloc.max_size(), 
																			std::numeric_limits<difference_type>::max());}
		void									clear()
		{
			for (iterator iter = begin(); iter != end(); ++iter)
				_alloc.destroy(iter);
			_size = 0;
		}

		iterator 								insert( iterator pos, const T& value ){

			difference_type	step = pos - begin();

			reserve(size() + 1);
			pos = begin() + step;
			for (reverse_iterator r_iter = rbegin(); pos <= r_iter; ++r_iter)
				_alloc.construct(r_iter + 1, T(*r_iter));
			_alloc.construct(pos, T(value));
			++_size;
			return (pos);
		}

		void 									insert( iterator pos, size_type count, const T& value )
		{
			difference_type	step = pos - begin();

			reserve(size() + count);
			pos = begin() + step;
			for (reverse_iterator r_iter = rbegin(); pos <= r_iter; ++r_iter)
				_alloc.construct(r_iter + count, T(*r_iter));
			for(size_type i = count; i; --i)
				_alloc.construct(pos + i - 1, T(value));
			_size += count;
		}

		template< class InputIt >
		void 									insert( iterator pos, InputIt first, InputIt last,
												typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = nullptr )
		{
			difference_type	step = pos - begin();
			size_type		count = last - first;

			reserve(size() + count);
			pos = begin() + step;
			for (reverse_iterator r_iter = rbegin(); pos <= r_iter; ++r_iter)
				_alloc.construct(r_iter + count, T(*r_iter));
			for(size_type i = count; i; --i)
				_alloc.construct(pos + i - 1, T(*(--last)));
			_size += count;
		}

		iterator erase( iterator pos )
		{
			for (iterator iter = pos; iter < end(); ++iter)
				*iter = *(iter + 1);
			_alloc.destroy((end() - 1).getPtr());
			--_size;
			return pos;
		}
		iterator erase( iterator first, iterator last )
		{
			difference_type	count = last - first;

			for (iterator iter = first; iter < last; ++iter)
				*iter = *(iter + count);
			for (reverse_iterator r_iter = rbegin(); r_iter >= end() - count; ++r_iter)
				_alloc.destroy(r_iter.getPtr());
			_size -= count;
			return first;
		}

		void									push_back(const T& value)
		{
			if (_size == _capacity)
				reserve(_capacity ? _capacity * 2 : 1);
			_alloc.construct(begin() + _size++, T(value));
		}

		void									pop_back() { _alloc.destroy(rbegin()); --_size; }

		void									resize( size_type count )
		{
			if (count > size()){ reserve(count); while (size() < count) push_back(T()); }
			else{ while (size() != count) pop_back(); }
		}

		void									swap(vector& other)
		{
			T*			temp_ptr = begin().getPtr();
			Allocator	temp_alloc = get_allocator();
			size_type	temp_size = size();
			size_type	temp_capacity = capacity();

			_vec = other.begin().getPtr();
			_alloc = other.get_allocator();
			_size = other.size();
			_capacity = other.capacity();

			other._vec = temp_ptr;
			other._alloc = temp_alloc;
			other._size = temp_size;
			other._capacity = temp_capacity;
		}

		void									reserve(size_type new_cap)
		{
			if (new_cap > capacity())
			{
				iterator	temp, ret;

				temp = _alloc.allocate(new_cap);
				ret = temp;
				for (iterator iter = begin(); iter != end(); ++iter, ++temp){
					_alloc.construct(temp.getPtr(), T(*iter));
					_alloc.destroy(iter.getPtr());
				}
				_alloc.deallocate(_vec, capacity());
				_vec = ret.getPtr();
				_capacity = new_cap;
			}
		}

		Allocator								get_allocator() const { return _alloc; }
		size_type								size() const { return _size; }
		size_type								capacity() const { return _capacity; }
	
	protected:
		size_type		_capacity;
		size_type		_size;
		T*				_vec;
		Allocator		_alloc;

	};

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		for (typename vector<T,Alloc>::const_iterator iter1 = lhs.cbegin(), iter2 = rhs.cbegin(); iter1 < lhs.cend(); iter1++, iter2++)
		{
			if (*iter1 != *iter2)
				return false;
		}
		return true;
	}
	
	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}
	
	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		for (typename vector<T,Alloc>::const_iterator iter1 = lhs.cbegin(), iter2 = rhs.cbegin() ; iter1 < lhs.cend() && iter2 < rhs.cend(); iter1++, iter2++)
		{
			if (*iter1 != *iter2)
				return (*iter1 < *iter2);
		}
		return lhs.size() < rhs.size();
	}
	
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		for (typename vector<T,Alloc>::const_iterator iter1 = lhs.cbegin(), iter2 = rhs.cbegin() ; iter1 < lhs.cend() && iter2 < rhs.cend(); iter1++, iter2++)
		{
			if (*iter1 != *iter2)
				return (*iter1 < *iter2);
		}
		return lhs.size() <= rhs.size();
	}
	
	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		for (typename vector<T,Alloc>::const_iterator iter1 = lhs.cbegin(), iter2 = rhs.cbegin() ; iter1 < lhs.cend() && iter2 < rhs.cend(); iter1++, iter2++)
		{
			if (*iter1 != *iter2)
				return (*iter1 > *iter2);
		}
		return lhs.size() > rhs.size();
	}
	
	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		for (typename vector<T,Alloc>::const_iterator iter1 = lhs.cbegin(), iter2 = rhs.cbegin() ; iter1 < lhs.cend() && iter2 < rhs.cend(); iter1++, iter2++)
		{
			if (*iter1 != *iter2)
				return (*iter1 > *iter2);
		}
		return lhs.size() >= rhs.size();
	}
	
	template< class T, class Alloc >
	void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif

/*

• iterators_traits
• reverse_iterator
• enable_if
Yes, it is C++11 but you will be able to implement it in a C++98 manner.
This is asked so you can discover SFINAE.
• is_integral
• equal and/or lexicographical_compare
• std::pair
• std::make_pair

*/