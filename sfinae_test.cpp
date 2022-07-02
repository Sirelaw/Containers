// #include <type_traits>
#include <iostream>
#include "utils.hpp"

template<bool>
	struct	enable_if {};

template<>
struct	enable_if<true>
{
	typedef	void type;
};

template <class T, class = typename enable_if<ft::is_integral<T>::value>::type>
void foo(T){
	std::cout << "T is NOT integral" << std::endl;
}

template<class T>
void foo(T){
	std::cout << "T is integral" << std::endl;
}

struct A {};

struct B : A{};

struct D {};

template< class T, class = typename enable_if<std::is_base_of<A, T>::value>::type>
struct C: T{};

int main()
{
	int x = 5;
	void *ptr = malloc(1);
	
	foo(x);
	foo(ptr);

	C<B>	c;
	
	return 0;
}