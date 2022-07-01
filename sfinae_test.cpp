// #include <type_traits>
#include <iostream>

template<bool>
	struct	enable_if {};

template<>
struct	enable_if<true>
{
	using type = void;
};

template <class T, class = typename enable_if<std::is_unsigned<T>::value>::type>
void foo(T){
	std::cout << "T is unsigned" << std::endl;
}

template<class T>
void foo(T){
	std::cout << "T is signed" << std::endl;
}

struct A {};

struct B : A{};

struct D {};

template< class T, class = typename enable_if<std::is_base_of<A, T>::value>::type>
struct C: T{};

int main()
{
	int x = 5;

	foo(x);

	C<B>	c;
	
	return 0;
}