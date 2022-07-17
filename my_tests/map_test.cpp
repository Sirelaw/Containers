#include <iostream>
#include <string>
#include <deque>
#include "../src/utils/verbose.hpp"

# include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

# ifndef FT
# define FT 1
# endif

#if FT 
	#include "../src/Map.hpp"
#else //CREATE A REAL STL EXAMPLE
	#include <map>
	namespace ft = std;
#endif

#define MAX_RAM 2294967296
#define BUFFER_SIZE 4096

#define COUNT (MAX_RAM / (int)sizeof(S_Class))
#define S_COUNT 50

// #define COUNT 100
// #define S_COUNT 5

struct	S_Class
{
	int 			idx;
	char 			buff[BUFFER_SIZE]; //To fill up space so doesn't get copied to save time.
	std::string		str;
	std::string*	str_ptr;

	S_Class() : idx(-1), str("something"), str_ptr(new std::string("some_ptr")) { }
	S_Class(const S_Class& other) : idx(other.idx), str(other.str), str_ptr(new std::string(*(other.str_ptr))) { }
	~S_Class() { delete str_ptr;  }
	S_Class&	operator=(const S_Class& other)
	{
		if (this != &other)
		{
			idx = other.idx;
			str = other.str;
			*str_ptr = *(other.str_ptr);
		}
		return *this;
	}
	bool		operator<(const S_Class& other) const {return idx < other.idx;}
	bool		operator==(const S_Class& other) const {return idx == other.idx;}
};

void	check()
{
	system("leaks containers");
}

long	time_diff(struct timeval& start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec - start_time.tv_sec) * 1000)
		+ ((current_time.tv_usec - start_time.tv_usec) / 1000));
}

int	main()
{
	struct timeval	start;

	ft::map<S_Class, S_Class>			compile_check;
	ft::map<S_Class, S_Class>			compile_check2;
	ft::map<int, S_Class>				map_S;
	ft::map<int, S_Class>				map_S2;

	//------------------------compile check-----------------------------------//
	{
		S_Class			temp;
		const S_Class	temp2;

		temp = temp2;
		for (int i = 0; i < 10; i++)
		{
			compile_check.insert(ft::make_pair(S_Class(), S_Class()));
		}
		compile_check.get_allocator();
		compile_check.empty();
		compile_check.size();
		compile_check.max_size();
		compile_check.erase(compile_check.begin());
		compile_check.count(temp2);
		compile_check[temp];
		compile_check.find(temp2);
		ft::swap(compile_check2, compile_check);
		compile_check.clear();
	}
	//----------------------compile check successful--------------------------//

	gettimeofday(&start, NULL);
	const int seed = start.tv_sec;
	srand(seed);

	gettimeofday(&start, NULL);  //insert
	for (int i = 0; i < COUNT; i++)
	{
		map_S.insert(ft::make_pair(i, S_Class()));
	}
	std::cout << "map insert:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;


	gettimeofday(&start, NULL); //erase
	map_S.erase(map_S.begin());
	map_S.erase(map_S.begin(), map_S.end());
	std::cout << "map erase:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	for (int i = 0; i < COUNT; i++)
	{
		map_S.insert(ft::make_pair(i, S_Class()));
	}

	gettimeofday(&start, NULL); //random_access
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = (rand() % COUNT) ;
		map_S[idx].idx = 5;
	}
	std::cout << "map random_access:\033[32m\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //swap
	map_S2 = map_S;
	ft::map<int,S_Class>().swap(map_S2);
	std::cout << "map swap:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;
	
	gettimeofday(&start, NULL); //compares and copy
	map_S2 = map_S;
	for (int i = 0; i < COUNT / 2; i++)
	{
		map_S2.erase(--(map_S2.end()));
	}
	PRINT((map_S < map_S2), BLUE);
	PRINT((map_S <= map_S2), BLUE);
	PRINT((map_S > map_S2), BLUE);
	PRINT((map_S >= map_S2), BLUE);
	map_S2 = map_S;
	PRINT((map_S == map_S2), BLUE);
	PRINT((map_S != map_S2), BLUE);
	map_S2.erase(map_S2.begin(), map_S2.end());
	std::cout << "map compares:\033[32m\t" << time_diff(start) << " ms\033[0m" << std::endl;
	std::cout << "Elements inserted:\t"   << RED << map_S.size() << RESET << std::endl;

	// atexit(check);
	return 0;
}
