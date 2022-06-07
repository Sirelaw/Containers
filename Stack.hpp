#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>

class Stack
{
private:
	
public:
	Stack();
	Stack(const Stack& to_copy);
	~Stack();
	Stack& operator=(const Stack& to_assign);
};

#endif

Stack::Stack()
{
	
}

Stack::Stack(const Stack& to_copy)
{
	
}

Stack::~Stack()
{
	
}

Stack& Stack::operator=(const Stack& to_assign)
{
	if (this != &to_assign)
	{
		
	}
	return (*this);
}