#include "../src/Vector.hpp"
#include "../src/utils/verbose.hpp"
#include <vector>

int main()
{
    ft::vector<int> ft_first;
    ft::vector<int> ft_first2;
    std::vector<int> std_first;
    std::vector<int> std_first2;
    ft_first.push_back(1);
    ft_first.push_back(2);
    ft_first.push_back(3);
    ft_first.push_back(4);
    std_first.push_back(1);
    std_first.push_back(2);
    std_first.push_back(3);
    std_first.push_back(4);

    ft::vector<int>::reverse_iterator rit = ft_first.rbegin();
    ft::vector<int>::reverse_iterator rit2 = ft_first2.rbegin();
    std::vector<int>::reverse_iterator rits = std_first.rbegin();
    std::vector<int>::reverse_iterator rits2 = std_first2.rbegin();
    if(!(((rit == rit2) == (rits == rits2)) && ((rit != rit2) == (rits != rits2)) && ((rit <= rit2) == (rits <= rits2)) &&  ((rit < rit2) == (rits < rits2)) && ((rit >= rit2) == (rits >= rits2)) && ((rit > rit2) == (rits > rits2))))
    {
        std::cout << "std " << (rits > rits2) << " (>) ft " << (rit > rit2) << std::endl;
        std::cout << "std " << (rits < rits2) << " (<) ft "  << (rit < rit2) << std::endl;
        std::cout << "std " << (rits >= rits2) << " (>=) ft " << (rit >= rit2) << std::endl;
        std::cout << "std " << (rits <= rits2) << " (<=) ft " << (rit <= rit2) << std::endl;
        std::cout << "std " << (rits != rits2) << " (!=) ft " << (rit != rit2) << std::endl;
        std::cout << "std " << (rits == rits2) << " (==) ft " << (rit == rit2) << std::endl;
        std::cout << "Reverse iterator is inaccurate\n" << std::endl;
    }
	else { std::cout << "Reverse iterator: \t"   << GREEN << "OK" << RESET << std::endl; }
    ft_first2.push_back(2);
    std_first2.push_back(2);
    if(!(((rit == rit2) == (rits == rits2)) && ((rit != rit2) == (rits != rits2)) && ((rit <= rit2) == (rits <= rits2)) && ((rit < rit2) == (rits < rits2)) && ((rit >= rit2) == (rits >= rits2)) && ((rit > rit2) == (rits > rits2))))
    {
        std::cout << "std " << (rits > rits2) << " (>) ft " << (rit > rit2) << std::endl;
        std::cout << "std " << (rits < rits2) << " (<) ft "  << (rit < rit2) << std::endl;
        std::cout << "std " << (rits >= rits2) << " (>=) ft " << (rit >= rit2) << std::endl;
        std::cout << "std " << (rits <= rits2) << " (<=) ft " << (rit <= rit2) << std::endl;
        std::cout << "std " << (rits != rits2) << " (!=) ft " << (rit != rit2) << std::endl;
        std::cout << "std " << (rits == rits2) << " (==) ft " << (rit == rit2) << std::endl;
        std::cout << "Reverse iterator is inaccurate after push_back\n" << std::endl;
    }
	else { std::cout << "Reverse iterator, after push_back: "   << GREEN << "OK" << RESET << std::endl; }
    ft::vector<int> ft_second;
    ft::vector<int> ft_second2;
    ft_second.push_back(1);
    ft_second2.push_back(1);
    std::vector<int> std_second;
    std::vector<int> std_second2;
    std_second.push_back(1);
    std_second2.push_back(1);
    ft::vector<int>::iterator it = ft_second.begin();
    ft::vector<int>::iterator it2 = ft_second2.begin();
    std::vector<int>::iterator its = std_second.begin();
    std::vector<int>::iterator its2 = std_second2.begin();
    if(!(((it == it2) == (its == its2)) && ((it != it2) == (its != its2)) && ((it <= it2) == (its <= its2)) && ((it < it2) == (its < its2)) && ((it >= it2) == (its >= its2)) && ((it > it2) == (its > its2))))
    {
        std::cout << "std " << (its > its2) << " (>) ft " << (it > it2) << std::endl;
        std::cout << "std " << (its < its2) << " (<) ft "  << (it < it2) << std::endl;
        std::cout << "std " << (its >= its2) << " (>=) ft " << (it >= it2) << std::endl;
        std::cout << "std " << (its <= its2) << " (<=) ft " << (it <= it2) << std::endl;
        std::cout << "std " << (its != its2) << " (!=) ft " << (it != it2) << std::endl;
        std::cout << "std " << (its == its2) << " (==) ft " << (it == it2) << std::endl;
        std::cout << "Iterator is inaccurate\n" << std::endl;
    }
	else { std::cout << "Iterator:\t\t"   << GREEN << "OK" << RESET << std::endl; }
    ft_second2.push_back(2);
    std_second2.push_back(2);
    if(!(((it == it2) == (its == its2)) && ((it != it2) == (its != its2)) && ((it <= it2) == (its <= its2)) && ((it < it2) == (its < its2)) && ((it >= it2) == (its >= its2)) && ((it > it2) == (its > its2))))
    {
        std::cout << "std " << (its > its2) << " (>)  ft " << (it > it2) << std::endl;
        std::cout << "std " << (its < its2) << " (<) ft "  << (it < it2) << std::endl;
        std::cout << "std " << (its >= its2) << " (>=) ft " << (it >= it2) << std::endl;
        std::cout << "std " << (its <= its2) << " (<=) ft " << (it <= it2) << std::endl;
        std::cout << "std " << (its != its2) << " (!=) ft " << (it != it2) << std::endl;
        std::cout << "std " << (its == its2) << " (==) ft " << (it == it2) << std::endl;
        std::cout << "Iterator is inaccurate after push_back\n" << std::endl;
    }
	else { std::cout << "Iterator, after push_back: "   << GREEN << "OK" << RESET << std::endl; }
    return (0);
}