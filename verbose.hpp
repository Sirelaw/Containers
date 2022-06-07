#ifndef VERBOSE_HPP
#define VERBOSE_HPP

#include <iostream>
#include <string>

#define RED     "\033[31m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

#define PRINT(message, color) \
	std::cout << color << message << RESET << std::endl

#endif
