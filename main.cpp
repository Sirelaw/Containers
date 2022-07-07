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

#include <string>
#include <string_view>
 
void	check()
{
	system("leaks containers");
}

int	main()
{
	std::map<int, std::string>	std_map;
	ft::map<int, std::string>	my_map;

	my_map.insert(ft::make_pair(1, "1: In my map"));
	my_map.insert(ft::make_pair(2, "2: In my map"));
	my_map.insert(ft::make_pair(3, "3: In my map"));
	my_map.insert(ft::make_pair(4, "4: In my map"));
	my_map.insert(ft::make_pair(5, "5: In my map"));
	my_map.insert(ft::make_pair(6, "6: In my map"));
	std_map.insert(std::make_pair(1, "In std map"));

	PRINT(my_map.at(1), RED);
	PRINT(my_map.at(6), RED);
	PRINT(my_map[6], RED);
	PRINT(my_map[30], RED);
	PRINT(my_map[350], RED);
	my_map.erase(my_map.begin() + 2);

	for(ft::map<int, std::string>::iterator iter = my_map.begin(); iter != my_map.end(); ++iter)
	{
		std::cout << "key: " << iter->first << "\tvalue: " << (&iter)->second << std::endl;
		
	}
	for(std::map<int, std::string>::iterator iter = std_map.begin(); iter != std_map.end(); ++iter)
	{
		std::cout << "key: " << iter->first << "\tvalue: " << iter->second << std::endl;
	}

	my_map.testpoint();
	PRINT(std_map[1], RED);
}
