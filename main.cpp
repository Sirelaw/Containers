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
#include "RBTree.hpp"
#include "Pair.hpp"
#include "Map.hpp"

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
	ft::RBTree<int, ft::less<int>, std::allocator<int> >	temp;
	std::map<int, int, ft::less<int> > test_map;
	// ft::BSTree<int>	temp;

	// ft::Node<int>	test;

	// temp.insert(23);
	// temp.insert(25);
	// temp.insert(30);
	// temp.insert(29);
	// temp.insert(4);
	// temp.insert(3);
	// temp.insert(1);
	// temp.insert(10);
	// temp.insert(7);
	// temp.insert(5);
	// temp.insert(9);
	// temp.insert(20);
	// temp.insert(15);
	// temp.insert(12);
	// temp.insert(18);

	// PRINT(temp.size(), BLUE);


	// temp.insert(10);
	// temp.insert(18);
	// temp.insert(7);
	// temp.insert(15);
	// temp.insert(16);
	// temp.insert(30);
	// temp.insert(25);
	// temp.insert(40);
	// temp.insert(60);
	// temp.insert(2);
	// temp.insert(1);
	// temp.insert(70);

	// temp.delete_node((temp.root())->search(23));

	temp.insert(79);
	temp.insert(18);
	temp.insert(62);
	temp.insert(10);
	temp.insert(4);
	temp.insert(42);
	temp.insert(78);
	temp.insert(74);
	temp.insert(47);
	temp.insert(5);
	temp.insert(28);
	temp.insert(80);
	temp.insert(93);
	temp.insert(65);
	temp.insert(33);
	temp.insert(69);
	temp.insert(99);
	temp.insert(37);
	temp.insert(71);
	temp.insert(36);
	temp.insert(20);
	temp.insert(95);
	temp.insert(48);
	temp.insert(21);
	temp.insert(63);
	temp.insert(73);
	temp.insert(3);
	temp.insert(16);
	temp.insert(7);
	temp.insert(9);
	temp.insert(94);////
	temp.insert(55);
	temp.insert(14);
	temp.insert(6);
	temp.insert(61);
	temp.insert(27);/////
	temp.insert(89);
	temp.insert(49);
	temp.insert(66);
	temp.insert(82);
	temp.insert(26);
	temp.insert(70);///
	temp.insert(68);
	temp.insert(81);
	temp.insert(58);
	temp.insert(35);
	temp.insert(2);
	temp.insert(44);
	temp.insert(88);
	temp.insert(85);

	temp.test_node();
	PRINT(temp.size(), GREEN);
	

	atexit(check);
	return (0);
}