#include <iostream>
#include <string>
#include <deque>
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

#define PRINT(message, color) \
	std::cout << color << message << RESET << std::endl

# include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <list>

# ifndef FT
# define FT 1
# endif

#if FT 
	#include "../src/Stack.hpp"
	#include "../src/Vector.hpp"
#else //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <stack>
	namespace ft = std;
#endif

#define MAX_RAM 2294967296
#define BUFFER_SIZE 4096

#define COUNT (MAX_RAM / (int)sizeof(S_Class))
#define S_COUNT 50

#define T_SIZE_TYPE typename ft::vector<T>::size_type

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

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

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
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

void	checkErase(ft::vector<std::string> const &vct,
					ft::vector<std::string>::const_iterator const &it)
	{
		static int i = 0;
		std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
		printSize(vct);
	}

void bar(int* ptr)
{
	(void)ptr;
}

void	is_empty(ft::vector<int> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

int	main()
{
	struct timeval	start;

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<S_Class> vec_S;
	ft::vector<S_Class> vec_S2;
	ft::stack<S_Class, std::deque<S_Class> > stack_deq_S_Class;
	MutantStack<char> iterable_stack;

	gettimeofday(&start, NULL);
	const int seed = start.tv_sec;
	srand(seed);

	gettimeofday(&start, NULL);  //push_back
	for (int i = 0; i < COUNT; i++)
	{
		vec_S.push_back(S_Class());
		vec_S[i].idx = i;
	}
	std::cout << "vector push_back:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //insert
	for (int i = 0; i < S_COUNT; i++)
	{
		vec_S.insert(vec_S.begin() + (COUNT / 3), S_Class());
	}
	std::cout << "vector insert:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //assign
	vec_S2.assign(COUNT/5, S_Class());
	vec_S2.assign(vec_S.begin(), vec_S.end());
	vec_S2.erase(vec_S2.begin(), vec_S2.end());
	std::cout << "vector assign:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //erase
	vec_S.erase(vec_S.begin() + (COUNT / 3) - 1);
	vec_S.erase(vec_S.begin() + (COUNT / 3) - 1, vec_S.end() - (COUNT / 3));
	std::cout << "vector erase:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;
	for (int i = vec_S.size(); i < COUNT; i++)
	{
		vec_S.push_back(S_Class());
		vec_S[i].idx = i;
	}
	gettimeofday(&start, NULL); //pop_back
	for (int i = 0; i < COUNT/2; i++)
	{
		vec_S.pop_back();
	}
	std::cout << "vector pop_back:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //random_access
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vec_S[idx].idx = 5;
	}
	std::cout << "vector random_access:\033[32m\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //resize
	vec_S.resize(COUNT / 2);
	vec_S.resize(COUNT);
	std::cout << "vector resize:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //swap
	vec_S2 = vec_S;
	ft::vector<S_Class>().swap(vec_S2);
	std::cout << "vector swap:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //compares and copy
	vec_S2 = vec_S;
	vec_S2.resize(COUNT / 2);
	PRINT((vec_S < vec_S2), BLUE);
	PRINT((vec_S <= vec_S2), BLUE);
	PRINT((vec_S > vec_S2), BLUE);
	PRINT((vec_S >= vec_S2), BLUE);
	vec_S2 = vec_S;
	PRINT((vec_S == vec_S2), BLUE);
	PRINT((vec_S != vec_S2), BLUE);
	vec_S2.erase(vec_S2.begin(), vec_S2.end());
	std::cout << "vector compares:\033[32m\t\t" << time_diff(start) << " ms\033[0m" << std::endl;

	gettimeofday(&start, NULL); //stack operations
	for(ft::vector<S_Class>::const_iterator iter = vec_S.begin(); iter < vec_S.end(); ++iter)
	{
		stack_deq_S_Class.push(*iter);
	}
	std::cout << "Elements inserted:\t"   << RED << stack_deq_S_Class.size() << RESET << std::endl;
	PRINT("------------------------------", BLUE);
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	std::cout << "\033[34m| \033[0m";
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << "\033[34m |\033[0m" << std::endl;
	std::cout << "\033[34m| \033[0m";
	while(!iterable_stack.empty())
	{
		std::cout << iterable_stack.top();
		iterable_stack.pop();
	}
	std::cout << "\033[34m |\033[0m" << std::endl;
	PRINT("------------------------------", BLUE);
	std::cout << "stack operations:\033[32m\t" << time_diff(start) << " ms\033[0m" << std::endl;
	

	
{
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct, true);
}

	// atexit(check);
	return 0;
}
