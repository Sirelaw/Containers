#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "../Pair.hpp"

namespace ft
{
	template<class ValueType>
	struct map_equal_compare : binary_function<ValueType, ValueType, bool>
	{
	public:
		bool	operator()( const ValueType& lhs, const ValueType& rhs ) const
		{
			return (lhs.first < rhs.first) == (rhs.first < lhs.first);
		}
	};

	template <class InputIterator1, class InputIterator2>
	ft::pair<InputIterator1, InputIterator2>	mismatch(InputIterator1 first1,
														InputIterator1 last1,
														InputIterator2 first2) {
		while (first1 != last1 && ((*first1 < *first2) == (*first2 < *first1))) 
		{
			++first1;
			++first2;
		}
		return ft::pair<InputIterator1, InputIterator2>(first1, first2);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	ft::pair<InputIterator1, InputIterator2>	mismatch(InputIterator1 first1,
														InputIterator1 last1,
														InputIterator2 first2,
														BinaryPredicate binary_pred) {
		while (first1 != last1 && binary_pred(*first1, *first2))
		{
			++first1;
			++first2;
		}
    	return ft::pair<InputIterator1, InputIterator2>(first1, first2);
	}

	template <class InputIterator1, class InputIterator2>
	bool 										equal(InputIterator1 first1,
													InputIterator1 last1,
													InputIterator2 first2) {
		return mismatch(first1, last1, first2).first == last1;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool 										equal(InputIterator1 first1,
													InputIterator1 last1,
													InputIterator2 first2,
													BinaryPredicate binary_pred) {
    	return mismatch(first1, last1, first2, binary_pred).first == last1;
	}

	template <class InputIterator1, class InputIterator2>
	bool										lexicographical_compare(InputIterator1 first1,
																		InputIterator1 last1,
																		InputIterator2 first2,
																		InputIterator2 last2) {
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2) return true;
			if (*first2++ < *first1++) return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template <class InputIterator1, class InputIterator2, class Compare1>
	bool										lexicographical_compare(InputIterator1 first1,
																		InputIterator1 last1,
																		InputIterator2 first2,
																		InputIterator2 last2,
																		Compare1 comp) {
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2)) return true;
			if (comp(*first2++, *first1++)) return false;
		}
		return first1 == last1 && first2 != last2;
	}

}

#endif