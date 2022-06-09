#include "Vector.hpp"
#include <vector>
#include <iostream>

#include "verbose.hpp"


void	check()
{
	system("leaks containers");
}

int main()
{
	std::allocator<int>	alloc;
	ft::vector<int>		vect(alloc);
	ft::vector<int>		countvec;
	std::vector<int>	stdvec;
	ft::vector<int>::iterator	iterate;
	
	// // std::vector<int>	stdvec(3, 37);

	countvec.push_back(-2);
	countvec.push_back(7);
	countvec.push_back(39);
	countvec.push_back(54);
	countvec.push_back(7454);

	// for (ft::vector<int>::iterator iter = countvec.begin(); iter != countvec.end(); ++iter)
	// 	std::cout << *iter << std::endl;

	// countvec.erase(countvec.begin() + 2, countvec.begin() + 4);
	// countvec.pop_back();
	countvec.resize(6);
	for (ft::vector<int>::iterator iter = countvec.begin(); iter < countvec.end(); ++iter)
		std::cout << *iter << std::endl;
	// atexit(check);
	return (0);
}

