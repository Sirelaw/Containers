#include "Vector.hpp"
#include <vector>
#include <iostream>

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
	// // std::vector<int>	stdvec(3, 37);

	countvec.push_back(2);
	stdvec.push_back(3);
	countvec.push_back(7);
	stdvec.push_back(3);
	countvec.push_back(2);
	stdvec.push_back(3);
	// countvec.insert(countvec.begin(), 17);
	// countvec = vect;
	// stdvec.push_back(7);
	// stdvec.assign(7, 22);
	for (ft::vector<int>::iterator iter = countvec.begin(); iter != countvec.end(); ++iter)
		std::cout << *iter << std::endl;
	PRINT(countvec.size(), GREEN);
	PRINT(countvec.capacity(), GREEN);
	// atexit(check);
	return (0);
}

