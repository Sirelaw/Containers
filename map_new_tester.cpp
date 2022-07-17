#include <list>
#include <iostream>
#include <string>

# ifndef FT
# define FT 1
# endif

	#include <map>
#if FT 
	#include "Map.hpp"
#  define TESTED_NAMESPACE ft
#else //CREATE A REAL STL EXAMPLE
	#include <map>
#  define TESTED_NAMESPACE std
	namespace ft = std;
#endif


#define _pair TESTED_NAMESPACE::pair

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
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
	typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}
//////////////////////////// ////// bounds

// typedef TESTED_NAMESPACE::map<int, foo<int> >::value_type T3;
// typedef TESTED_NAMESPACE::map<int, foo<int> >::iterator ft_iterator;
// typedef TESTED_NAMESPACE::map<int, foo<int> >::const_iterator ft_const_iterator;

// static int iter = 0;

// template <typename MAP>
// void	ft_bound(MAP &mp, const int &param)
// {
// 	ft_iterator ite = mp.end(), it[2];
// 	_pair<ft_iterator, ft_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
// 	ft_range = mp.equal_range(param);
// 	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
// 	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

// template <typename MAP>
// void	ft_const_bound(const MAP &mp, const int &param)
// {
// 	ft_const_iterator ite = mp.end(), it[2];
// 	_pair<ft_const_iterator, ft_const_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
// 	ft_range = mp.equal_range(param);
// 	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
// 	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

// int		main(void)
// {
// 	// std::map<int, foo<int> > T3;
// 	std::list<T3> lst;
// 	unsigned int lst_size = 10;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(i + 1, (i + 1) * 3));
// 	TESTED_NAMESPACE::map<int, foo<int> > mp(lst.begin(), lst.end());
// 	printSize(mp);

// 	ft_const_bound(mp, -10);
// 	ft_const_bound(mp, 1);
// 	ft_const_bound(mp, 5);
// 	ft_const_bound(mp, 10);
// 	ft_const_bound(mp, 50);

// 	printSize(mp);

// 	mp.lower_bound(3)->second = 404;
// 	mp.upper_bound(7)->second = 842;
// 	ft_bound(mp, 5);
// 	ft_bound(mp, 7);

// 	printSize(mp);
// 	return (0);
// }

//////////////////////////// ////// comp

// typedef TESTED_NAMESPACE::map<char, foo<float> > _map;
// typedef _map::const_iterator const_it;

// static unsigned int i = 0;

// void	ft_comp(const _map &mp, const const_it &it1, const const_it &it2)
// {
// 	bool res[2];

// 	std::cout << "\t-- [" << ++i << "] --" << std::endl;
// 	res[0] = mp.key_comp()(it1->first, it2->first);
// 	res[1] = mp.value_comp()(*it1, *it2);
// 	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
// 	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
// }

// int		main(void)
// {
// 	_map	mp;

// 	mp['a'] = 2.3;
// 	mp['b'] = 1.4;
// 	mp['c'] = 0.3;
// 	mp['d'] = 4.2;
// 	printSize(mp);

// 	for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
// 		for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
// 			ft_comp(mp, it1, it2);

// 	printSize(mp);
// 	return (0);
// }

//////////////////////////// ////// copy_construct

// typedef _pair<const int, int> T3;

// int		main(void)
// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 7;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(lst_size - i, i));

// 	TESTED_NAMESPACE::map<int, int> mp(lst.begin(), lst.end());
// 	TESTED_NAMESPACE::map<int, int>::iterator it = mp.begin(), ite = mp.end();

// 	TESTED_NAMESPACE::map<int, int> mp_range(it, --(--ite));
// 	for (int i = 0; it != ite; ++it)
// 		it->second = ++i * 5;

// 	it = mp.begin(); ite = --(--mp.end());
// 	TESTED_NAMESPACE::map<int, int> mp_copy(mp);
// 	for (int i = 0; it != ite; ++it)
// 		it->second = ++i * 7;

// 	std::cout << "\t-- PART ONE --" << std::endl;
// 	printSize(mp);
// 	printSize(mp_range);
// 	printSize(mp_copy);

// 	mp = mp_copy;
// 	mp_copy = mp_range;
// 	mp_range.clear();

// 	std::cout << "\t-- PART TWO --" << std::endl;
// 	printSize(mp);
// 	printSize(mp_range);
// 	printSize(mp_copy);
// 	return (0);
// }

//////////////////////////// ////// erase

// typedef _pair<const int, std::string> T3;

// static int iter = 0;

// template <typename MAP, typename U>
// void	ft_erase(MAP &mp, U param)
// {
// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	mp.erase(param);
// 	printSize(mp);
// }

// template <typename MAP, typename U, typename V>
// void	ft_erase(MAP &mp, U param, V param2)
// {
// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	mp.erase(param, param2);
// 	printSize(mp);
// }

// int		main(void)
// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 10;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
// 	TESTED_NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
// 	printSize(mp);

// 	ft_erase(mp, ++mp.begin());

// 	ft_erase(mp, mp.begin());
// 	ft_erase(mp, --mp.end());

// 	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
// 	ft_erase(mp, --(--(--mp.end())), --mp.end());

// 	mp[10] = "Hello";
// 	mp[11] = "Hi there";
// 	printSize(mp);
// 	ft_erase(mp, --(--(--mp.end())), mp.end());

// 	mp[12] = "ONE";
// 	mp[13] = "TWO";
// 	mp[14] = "THREE";
// 	mp[15] = "FOUR";
// 	printSize(mp);
// 	ft_erase(mp, mp.begin(), mp.end());

// 	return (0);
// }

//////////////////////////// ////// erase2

// typedef _pair<const int, std::string> T3;

// static int iter = 0;

// template <typename MAP, typename U>
// void	ft_erase(MAP &mp, U param)
// {
// 	printSize(mp);
// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	std::cout << "ret: " << mp.erase(param) << std::endl;
// 	printSize(mp);
// }

// int		main(void)
// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 6;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
// 	TESTED_NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
// 	printSize(mp);

// 	for (int i = 2; i < 4; ++i)
// 		ft_erase(mp, i);

// 	ft_erase(mp, mp.begin()->first);
// 	ft_erase(mp, (--mp.end())->first);

// 	mp[-1] = "Hello";
// 	mp[10] = "Hi there";
// 	mp[10] = "Hi there";
// 	printSize(mp);

// 	ft_erase(mp, 0);
// 	ft_erase(mp, 1);

// 	return (0);
// }

//////////////////////////// ////// insert

// typedef TESTED_NAMESPACE::map<int, std::string>::value_type T3;
// typedef TESTED_NAMESPACE::map<int, std::string>::iterator iterator;

// static int iter = 0;

// template <typename MAP, typename U>
// void	ft_insert(MAP &mp, U param)
// {
// 	_pair<iterator, bool> tmp;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	tmp = mp.insert(param);
// 	std::cout << "insert return: " << printPair(tmp.first);
// 	std::cout << "Created new node: " << tmp.second << std::endl;
// 	printSize(mp);
// }

// template <typename MAP, typename U, typename V>
// void	ft_insert(MAP &mp, U param, V param2)
// {
// 	iterator tmp;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	tmp = mp.insert(param, param2);
// 	std::cout << "insert return: " << printPair(tmp);
// 	printSize(mp);
// }

// int		main(void)
// {
// 	TESTED_NAMESPACE::map<int, std::string> mp, mp2;

// 	ft_insert(mp, T3(42, "lol"));
// 	ft_insert(mp, T3(42, "mdr"));

// 	ft_insert(mp, T3(50, "mdr"));
// 	ft_insert(mp, T3(35, "funny"));

// 	ft_insert(mp, T3(45, "bunny"));
// 	ft_insert(mp, T3(21, "fizz"));
// 	ft_insert(mp, T3(38, "buzz"));

// 	ft_insert(mp, mp.begin(), T3(55, "fuzzy"));

// 	ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
// 	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
// 	ft_insert(mp2, mp2.end(), T3(1500, "World"));

// 	return (0);
// }

//////////////////////////// ////// insert

// typedef _pair<const char, int> T3;

// template <class MAP>
// void	cmp(const MAP &lhs, const MAP &rhs)
// {
// 	static int i = 0;

// 	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
// 	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
// 	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
// 	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
// }

// int		main(void)
// {
// 	TESTED_NAMESPACE::map<char, int> mp1;
// 	TESTED_NAMESPACE::map<char, int> mp2;

// 	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
// 	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

// 	cmp(mp1, mp1); // 0
// 	cmp(mp1, mp2); // 1

// 	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

// 	cmp(mp1, mp2); // 2
// 	cmp(mp2, mp1); // 3

// 	(++(++mp1.begin()))->second = 42;

// 	// cmp(mp1, mp2); // 4
// 	// cmp(mp2, mp1); // 5

// 	// swap(mp1, mp2);

// 	// cmp(mp1, mp2); // 6
// 	// cmp(mp2, mp1); // 7

// 	return (0);
// }

//////////////////////////// ////// rite

// typedef _pair<const char, int> T3;

// int		main(void)
// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 5;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3('a' + i, (i + 1) * 7));

// 	TESTED_NAMESPACE::map<char, int> mp(lst.begin(), lst.end());
// 	TESTED_NAMESPACE::map<char, int>::iterator it_ = mp.begin();
// 	TESTED_NAMESPACE::map<char, int>::reverse_iterator it(it_), ite;
// 	printSize(mp);

// 	std::cout << (it_ == it.base()) << std::endl;
// 	std::cout << (it_ == dec(it, 3).base()) << std::endl;

// 	printPair(it.base());
// 	printPair(inc(it.base(), 1));

// 	std::cout << "TEST OFFSET" << std::endl;
// 	--it;
// 	printPair(it);
// 	printPair(it.base());

// 	it = mp.rbegin(); ite = mp.rend();
// 	while (it != ite)
// 		std::cout << "[rev] " << printPair(it++, false) << std::endl;
// 	printReverse(mp);

// 	return (0);
// }

//////////////////////////// ////// rite_arrow

typedef _pair<const float, foo<int> > T3;

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 - i, (i + 1) * 7));

	TESTED_NAMESPACE::map<float, foo<int> > mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<float, foo<int> >::reverse_iterator it(mp.rbegin());
	TESTED_NAMESPACE::map<float, foo<int> >::const_reverse_iterator ite(mp.rbegin());
	printSize(mp);

	printPair(++ite);
	printPair(ite++);
	printPair(ite++);
	printPair(++ite);

	it->second.m();
	ite->second.m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	(*it).second.m();
	(*ite).second.m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);

	return (0);
}