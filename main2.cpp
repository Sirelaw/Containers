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
	// ft::RBTree<std::string, ft::less<std::string>, std::allocator<std::string> >	temp;
	ft::RBTree<int, ft::less<int>, std::allocator<int> >	temp_int;
	std::map<int, int, ft::less<int> > test_map;
	ft::vector<std::string> test_vec;
	ft::vector<int> int_vec;
	test_vec.push_back("hello");
	test_vec.push_back("there");
	test_vec.push_back("you");
	int_vec.push_back(2);
	int_vec.push_back(24);
	int_vec.push_back(52);
	ft::vector<std::string> new_vec(test_vec.begin(), test_vec.end());
	ft::vector<std::string> latest_vec(5, "15");
	ft::vector<int>			new_int_vec(int_vec.begin(), int_vec.end());
	ft::vector<int>			latest_int_vec(10, 42);
	PRINT(new_vec.size(), BLUE);
	PRINT(latest_vec.size(), BLUE);
	PRINT(new_vec[1], BLUE);
	PRINT(latest_vec[1], BLUE);
	PRINT(int_vec[1], BLUE);
	PRINT(latest_int_vec[1], BLUE);
	// ft::BSTree<int>	temp;

	// ft::Node<int>	test;

	// temp_int.insert(23);
	// temp_int.insert(25);
	// temp_int.insert(30);
	// temp_int.insert(29);
	// temp_int.insert(4);
	// temp_int.insert(3);
	// temp_int.insert(1);
	// temp_int.insert(10);
	// temp_int.insert(7);
	// temp_int.insert(5);
	// temp_int.insert(9);
	// temp_int.insert(20);
	// temp_int.insert(15);
	// temp_int.insert(12);
	// temp_int.insert(18);

	PRINT(temp_int.size(), BLUE);


	temp_int.insert(10);
	temp_int.insert(18);
	temp_int.insert(7);
	temp_int.insert(15);
	temp_int.insert(16);
	temp_int.insert(30);
	temp_int.insert(25);
	temp_int.insert(40);
	temp_int.insert(60);
	temp_int.insert(2);
	temp_int.insert(1);
	temp_int.insert(70);
	temp_int.insert(79);
	temp_int.insert(18);
	temp_int.insert(62);
	temp_int.insert(4);
	temp_int.insert(42);
	temp_int.insert(78);
	temp_int.insert(74);
	temp_int.insert(47);
	temp_int.insert(5);
	temp_int.insert(28);
	temp_int.insert(80);
	temp_int.insert(93);
	temp_int.insert(65);
	temp_int.insert(33);
	temp_int.insert(69);
	temp_int.insert(99);
	temp_int.insert(37);
	temp_int.insert(71);
	temp_int.insert(36);
	temp_int.insert(20);
	temp_int.insert(95);
	temp_int.insert(48);
	temp_int.insert(21);
	temp_int.insert(63);
	temp_int.insert(73);
	temp_int.insert(3);
	temp_int.insert(16);
	temp_int.insert(7);
	temp_int.insert(9);
	temp_int.insert(94);////
	temp_int.insert(55);
	temp_int.insert(14);
	temp_int.insert(6);
	temp_int.insert(61);
	temp_int.insert(27);/////
	temp_int.insert(89);
	temp_int.insert(49);
	temp_int.insert(66);
	temp_int.insert(82);
	temp_int.insert(26);
	temp_int.insert(70);///
	temp_int.insert(68);
	temp_int.insert(81);
	temp_int.insert(58);
	temp_int.insert(35);
	temp_int.insert(2);
	temp_int.insert(44);
	temp_int.insert(88);
	temp_int.insert(85);
	temp_int.insert(1);
	temp_int.insert(1);

	temp_int.remove(10);
	temp_int.remove(2);
	temp_int.remove(44);
	temp_int.remove(88);
	temp_int.remove(85);
	temp_int.remove(1);
	temp_int.remove(1);
	temp_int.remove(48);
	temp_int.remove(21);
	temp_int.remove(63);
	temp_int.remove(73);
	temp_int.remove(3);
	temp_int.remove(16);
	temp_int.remove(7);
	temp_int.remove(9);
	temp_int.remove(94);////
	temp_int.remove(55);
	temp_int.remove(14);
	temp_int.remove(6);
	temp_int.remove(61);
	temp_int.remove(27);/////
	temp_int.remove(89);
	temp_int.remove(49);
	temp_int.remove(66);
	temp_int.remove(82);
	temp_int.remove(26);
	temp_int.remove(70);///
	temp_int.remove(68);

	// temp.insert("A");
	// temp.insert("B");
	// temp.insert("C");
	// temp.insert("D");
	// temp.insert("E");
	// temp.insert("F");

	temp_int.test_node();
	// temp.test_node();

	// for (ft::RBTree<std::string>::const_reverse_iterator iter = temp.crbegin(); iter != temp.crend(); ++iter)
	// {
	// 	PRINT(iter->value(), RED);
	// 	PRINT((iter + 4)->value(), GREEN);
	// }
	// for (ft::RBTree<int>::const_reverse_iterator iter = temp_int.crbegin(); iter != temp_int.crend(); ++iter)
	// {
	// 	PRINT(iter->value(), RED);
	// }
	// PRINT(temp.size(), GREEN);
	// PRINT(temp.confirm_size(), GREEN);
	// atexit(check);
	return (0);
}


// iterator_traits example
// #include <iostream>     // std::cout
// #include <iterator>     // std::iterator_traits
// #include <typeinfo>     // typeid

// int main() {
//   typedef ft::iterator_traits<int*> traits;
//   if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
//     std::cout << "int* is a random-access iterator";
//   return 0;
// }




