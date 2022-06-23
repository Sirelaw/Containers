#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
#include "RBTree.hpp"

namespace ft
{
	template< class Key, class T, class Compare = less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{

	};
}

class Map
{
private:
	
public:
	Map();
	Map(const Map& to_copy);
	~Map();
	Map& operator=(const Map& to_assign);
};

#endif


Map::Map()
{
	
}

Map::Map(const Map& to_copy)
{
	
}

Map::~Map()
{
	
}

Map& Map::operator=(const Map& to_assign)
{
	if (this != &to_assign)
	{
		
	}
	return (*this);
}