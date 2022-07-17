// #include <type_traits>
#include <iostream>
#include "../src/utils/type_traits.hpp"
#include "../src/utils/utils.hpp"

template<class T>
void foo(T) {
	std::cout << "T is integral" << std::endl;
}

template <class T>
void foo(T, typename ft::enable_if<ft::is_integral<T>::value>::type* = nullptr) {
	std::cout << "T is NOT integral" << std::endl;
}


struct A {};

struct B : A{};

struct D {};

template< class T, class = typename ft::enable_if<std::is_base_of<A, T>::value>::type>
struct C: T{};

int main()
{
	// int x = 5;
	// void *ptr = malloc(1);
	
	// foo(x);
	// foo(ptr);

	
	return 0;

}


