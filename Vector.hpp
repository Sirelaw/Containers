#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>

#include "verbose.hpp"

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
		typedef	std::random_access_iterator_tag	iterator_category;

	public:
		vecIterator(T* ptr = nullptr) 			{_ptr = ptr;}
		~vecIterator(){}

		vecIterator<T>&							operator=(T* ptr) { _ptr = ptr; return *this; }
		
		operator								bool() const { return (_ptr ? true : false); }
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
		typedef	std::ptrdiff_t							difference_type;

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

	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		//------------------ Typedefs------------------------------------------//
		typedef	T								value_type;
		typedef	Allocator						allocator_type;
		typedef	std::size_t						size_type;
		typedef	std::ptrdiff_t					difference_type;
		typedef	value_type&						reference;
		typedef	const value_type& 				const_reference;
		typedef	typename Allocator::pointer		pointer;
		typedef	std::random_access_iterator_tag	iterator_category;
		typedef	vecIterator<T>					iterator;
		typedef	vecIterator<const T>			const_iterator;
		typedef	vecReverseIterator<T>			reverse_iterator;
		typedef	vecReverseIterator<const T>		const_reverse_iterator;

		//------------------ Iterator Member Functions ------------------------//
	public:
		iterator								begin(){ return iterator(&_vec[0]); }
		iterator								end(){ return iterator(&_vec[_size]); }
		const_iterator							cbegin() const { return const_iterator(&_vec[0]); }
		const_iterator							cend() const { return const_iterator(&_vec[_size]); }
		reverse_iterator						rbegin(){ return reverse_iterator(_vec[_size - 1]); }
		reverse_iterator						rend(){ return reverse_iterator(_vec[-1]); }
		const_reverse_iterator					crbegin() const { return const_reverse_iterator(&_vec[_size - 1]); }
		const_reverse_iterator					crend() const { return const_reverse_iterator(&_vec[-1]); }

		//----------------------- Member Functions ----------------------------//
	public:
		vector() : _capacity(0), _size(0) {
			_vec = _alloc.allocate(capacity());
		}

		explicit vector( const Allocator& alloc ) : _capacity(0), _size(0) {
			_alloc = alloc;
			_vec = _alloc.allocate(capacity());
		}

		explicit vector ( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) 
			: _capacity(count), _size(count) {
			_alloc = alloc;
			_vec = _alloc.allocate(capacity());
			for (iterator iter = begin(); iter < end(); iter++)
				_alloc.construct(iter, T(value));
		}
		
		template <class InputIt >
		explicit vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) 
			: _capacity(0), _size(0){
			_alloc = alloc;
			_vec = _alloc.allocate(0);
			assign(first, last);
		}

		vector(const vector& to_copy) : _capacity(0), _size(0) {
			_vec = _alloc.allocate(capacity());
			*this = to_copy;
		}

		~vector() {
			_alloc.deallocate(_vec, capacity());
		}

		vector& 								operator=(const vector& other){
			if (this != &other)
			{
				iterator	temp;

				this->clear();
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
				_alloc.deallocate(_vec, capacity());
				_vec = _alloc.allocate(count);
				_capacity = count;
			}
			for(iterator iter = begin(); iter != end() ; ++iter)
				_alloc.construct(iter, T(value));
		}

		// template< class InputIt >
		// void assign( InputIt first, InputIt last )
		// {
		// 	size_type	count = last - first;
		//
		// 	this->clear();
		// 	_size = count;
		// 	if (count > capacity()){
		// 		_alloc.deallocate(_vec, capacity());
		// 		_vec = _alloc.allocate(count);
		// 		_capacity = count;
		// 	}
		// 	for(iterator iter = begin(); iter != end() ; ++iter, ++first)
		// 		_alloc.construct(iter, T(*first));
		// }

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
		bool									empty() const { return size() ? false : true; }
		size_type								max_size() const { return std::min<size_type>(_alloc.max_size(), 
																			std::numeric_limits<difference_type>::max());}
		void									clear(){
			for (iterator iter = begin(); iter != end(); ++iter)
				_alloc.destroy(iter);
			_size = 0;
		}
		// iterator 								insert( iterator pos, const T& value ){
		// 	difference_type	step = pos - begin();
		// 	T				temp;

		// 	reserve(size() + 1);
		// 	pos = begin() + step;
		// 	for ()
		// }
		// void 									insert( iterator pos, size_type count, const T& value );
		// template< class InputIt >
		// void 									insert( iterator pos, InputIt first, InputIt last );
		void									push_back(const T& value)
		{
			if (_size == _capacity)
				reserve(_capacity ? _capacity * 2 : 1);
			_alloc.construct(_vec + _size++, T(value));
		}

		void									reserve(size_type new_cap)
		{
			if (new_cap > capacity())
			{
				iterator	temp, ret;

				temp = _alloc.allocate(new_cap);
				ret = temp;
				for (iterator iter = begin(); iter != end(); ++iter, ++temp){
					_alloc.construct(temp, T(*iter));
					_alloc.destroy(iter);
				}
				_alloc.deallocate(_vec, capacity());
				_vec = ret;
				_capacity = new_cap;
			}
		}

		Allocator								get_allocator() const { return _alloc; }
		size_type								size() const { return _size; }
		size_type								capacity() const { return _capacity; }

	
	private:
		T*				_vec;
		Allocator		_alloc;
		size_type		_capacity;
		size_type		_size;

	};
}

#endif


/*
vector();	// Default constructor. Constructs an empty container with a default-constructed allocator.

explicit vector( const Allocator& alloc ); 
	(until C++17) // Constructs an empty container with the given allocator alloc.


explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
	(until C++11) // Constructs the container with count copies of elements with value value

template< class InputIt >
vector( InputIt first, InputIt last,
        const Allocator& alloc = Allocator() );
	(until C++20) // Constructs the container with the contents of the range [first, last)

vector( const vector& other );
	(until C++20) // Copy constructor. Constructs the container with the copy of the contents of other. 

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