#include "Vector.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include "verbose.hpp"

template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
    os << "{";
    for (typename Co::const_iterator iter = co.cbegin(); iter < co.cend(); ++iter) { os << ' ' << *iter; }
    return os << " } ";
}

void	check()
{
	system("leaks containers");
}

int main()
{
	// std::allocator<int>	alloc;
	// ft::vector<int>		vect(alloc);
	// ft::vector<int>		countvec;
	// std::vector<int>	stdvec;
	// ft::vector<int>::iterator	iterate;
	
	// // // std::vector<int>	stdvec(3, 37);

	// countvec.push_back(-2);
	// countvec.push_back(7);
	// countvec.push_back(39);
	// countvec.push_back(54);
	// countvec.push_back(7454);

	// // for (ft::vector<int>::iterator iter = countvec.begin(); iter != countvec.end(); ++iter)
	// // 	std::cout << *iter << std::endl;

	// // countvec.erase(countvec.begin() + 2, countvec.begin() + 4);
	// // countvec.pop_back();
	// countvec.resize(6);
	// for (ft::vector<int>::iterator iter = countvec.begin(); iter < countvec.end(); ++iter)
	// 	std::cout << *iter << std::endl;

	ft::vector<int> a1, a2;

	a1.push_back(2); a1.push_back(1); a1.push_back(3);
	a2.push_back(4); a2.push_back(5); a2.push_back(6);
 
    ft::vector<int>::iterator it1 = std::next(a1.begin());
    ft::vector<int>::iterator it2 = std::next(a2.begin());
 
    int& ref1 = a1.front();
    int& ref2 = a2.front();
 
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
	a1.insert(a1.begin(), 4, 4);
	ft::swap(a1,a2);
	std::reverse(a1.begin(), a1.end());
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
	for (ft::vector<int>::iterator iter = a1.begin(); iter < a1.end(); iter++)
		PRINT(*iter, BLUE);
	// atexit(check);
	return (0);
}