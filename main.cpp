#include "Vector.hpp"
#include "Stack.hpp"
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
#include "verbose.hpp"
#include "Node.hpp"
#include "BSTree.hpp"
#include "AVLTree.hpp"

// template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
//     os << "{";
//     for (typename Co::const_iterator iter = co.cbegin(); iter < co.cend(); ++iter) { os << ' ' << *iter; }
//     return os << " } ";
// }

void	check()
{
	system("leaks containers");
}

int main()
{
	ft::AVLTree<int>	temp;
	// ft::BSTree<int>	temp;
	// ft::Node<int>	test;

	temp.insert(23);
	temp.insert(25);
	temp.insert(30);
	temp.insert(29);
	temp.insert(4);
	temp.insert(3);
	temp.insert(1);
	temp.insert(10);
	temp.insert(7);
	temp.insert(5);
	temp.insert(9);
	temp.insert(20);
	temp.insert(15);
	temp.insert(12);
	temp.insert(18);
	temp.insert(40);
	
	temp.test_node();
	PRINT(temp.size(), GREEN);
	

	atexit(check);
	return (0);
}