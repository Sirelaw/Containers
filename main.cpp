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
	ft::map<int, std::string>	my_map2;

	my_map.insert(ft::make_pair(1, "1: In my map"));
	my_map.insert(ft::make_pair(2, "2: In my map"));
	my_map.insert(ft::make_pair(3, "3: In my map"));
	my_map.insert(ft::make_pair(4, "4: In my map"));
	my_map.insert(ft::make_pair(5, "5: In my map"));
	my_map.insert(ft::make_pair(6, "6: In my map"));

	// my_map2.insert(ft::make_pair(1, "1: In my map2"));
	// my_map2.insert(ft::make_pair(2, "2: In my map2"));
	// my_map2.insert(ft::make_pair(3, "3: In my map2"));
	// my_map2.insert(ft::make_pair(4, "4: In my map2"));
	// my_map2.insert(ft::make_pair(5, "5: In my map2"));
	// my_map2.insert(ft::make_pair(6, "6: In my map2"));

	std_map.insert(std::make_pair(1, "1: In std map"));
	std_map.insert(std::make_pair(2, "2: In std map"));
	std_map.insert(std::make_pair(3, "3: In std map"));
	std_map.insert(std::make_pair(4, "4: In std map"));
	std_map.insert(std::make_pair(5, "5: In std map"));
	std_map.insert(std::make_pair(6, "6: In std map"));
	

	for(ft::map<int, std::string>::iterator iter = my_map.begin(); iter != my_map.end(); ++iter)
	{
		std::cout << "map\tkey: " << iter->first << "\tvalue: " << (&iter)->second << std::endl;
		
	}
	// for(ft::map<int, std::string>::iterator iter = my_map2.begin(); iter != my_map2.end(); ++iter)
	// {
	// 	std::cout << "map2\tkey: " << iter->first << "\tvalue: " << (&iter)->second << std::endl;
		
	// }
	PRINT(my_map.size(), RED);
	PRINT(my_map2.size(), RED);
	my_map.swap(my_map2);
	PRINT(my_map2.count((my_map2.begin() + 1)->first), RED);
	// PRINT(std_map.lower_bound((std_map.begin() + 1)->first), RED);
	PRINT((std_map.upper_bound((++std_map.begin())->first))->first, RED);
	// for(std::map<int, std::string>::iterator iter = std_map.begin(); iter != std_map.end(); ++iter)
	// {
	// 	std::cout << "key------------->: " << iter->first << "\tvalue: " << iter->second << std::endl;
	// }
	// std_map.erase(std_map.cbegin(), std_map.cend());
	// PRINT((my_map.begin() + 2)->first, RED);
	// my_map.erase(my_map.begin(), my_map.begin() + 2);

	// for(ft::map<int, std::string>::iterator iter = my_map.begin(); iter != my_map.end(); ++iter)
	// {
	// 	std::cout << "key: " << iter->first << "\tvalue: " << (&iter)->second << std::endl;
		
	// }

	// for(std::map<int, std::string>::iterator iter = std_map.begin(); iter != std_map.end(); ++iter)
	// {
	// 	std::cout << "key------------>: " << iter->first << "\tvalue: " << iter->second << std::endl;
	// }

	for(ft::map<int, std::string>::iterator iter = my_map.begin(); iter != my_map.end(); ++iter)
	{
		std::cout << "map\tkey: " << iter->first << "\tvalue: " << iter->second << std::endl;
	}
	// for(ft::map<int, std::string>::iterator iter = my_map2.begin(); iter != my_map2.end(); ++iter)
	// {
	// 	std::cout << "map2\tkey: " << iter->first << "\tvalue: " << iter->second << std::endl;
	// }

	// PRINT(std_map[1], RED);
	// PRINT(my_map[1], RED);
}
