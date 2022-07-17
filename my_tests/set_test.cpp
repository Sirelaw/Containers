# include <iostream>
# include <string>
#include <list>

# ifndef FT
# define FT 1
# endif

#if FT 
	#include "../src/Set.hpp"
#  define TESTED_NAMESPACE ft
#else //CREATE A REAL STL EXAMPLE
	#include <set>
#  define TESTED_NAMESPACE std
	namespace ft = std;
#endif

#define _pair TESTED_NAMESPACE::pair

void	check()
{
	system("leaks containers");
}

// --- Class foo
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

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << *iterator;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_SET>
void	printSize(T_SET const &st, bool print_content = 1)
{
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "max_size: " << st.max_size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = st.begin(), ite = st.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1>
void	printReverse(TESTED_NAMESPACE::set<T1> &st)
{
	typename TESTED_NAMESPACE::set<T1>::iterator it = st.end(), ite = st.begin();

	std::cout << "printReverse:" << std::endl;
	while (it-- != ite)
		std::cout << "-> " << printPair(it, false) << std::endl;
	std::cout << "_______________________________________________" << std::endl;
}
/////////////////////////////////// bounds

typedef TESTED_NAMESPACE::set<int>::iterator ft_iterator;
typedef TESTED_NAMESPACE::set<int>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename SET>
void	ft_bound(SET &st, const int &param)
{
	ft_iterator ite = st.end(), it[2];
	_pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = st.lower_bound(param); it[1] = st.upper_bound(param);
	ft_range = st.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename SET>
void	ft_const_bound(const SET &st, const int &param)
{
	ft_const_iterator ite = st.end(), it[2];
	_pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = st.lower_bound(param); it[1] = st.upper_bound(param);
	ft_range = st.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		main(void)
{
	std::list<int> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back((i + 1) * 3);
	TESTED_NAMESPACE::set<int> st(lst.begin(), lst.end());
	printSize(st);

	ft_const_bound(st, -10);
	ft_const_bound(st, 1);
	ft_const_bound(st, 5);
	ft_const_bound(st, 10);
	ft_const_bound(st, 50);

	printSize(st);

	ft_bound(st, 5);
	ft_bound(st, 7);

	printSize(st);
	// atexit(check);
	return (0);
}
