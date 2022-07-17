#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	template<bool>
	struct	enable_if {};

	template<>
	struct	enable_if<true>
	{
		typedef	void type;
	};

	template<class T, T v>
	struct	integral_constant
	{
		static const T	value = v;
		typedef T		value_type;
		typedef integral_constant	type;
		operator	value_type() const { return value; }
		value_type	operator()() const { return value; }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;


	template <class T>	struct is_integral						: public false_type {};
	template <>			struct is_integral<bool>				: public true_type {};
	template <>			struct is_integral<char>				: public true_type {};
	template <>			struct is_integral<signed char>			: public true_type {};
	template <>			struct is_integral<unsigned char>		: public true_type {};
	template <>			struct is_integral<wchar_t>				: public true_type {};
	#if __cplusplus > 201703L || defined(__cpp_char8_t)
	template <>			struct is_integral<char8_t>				: public true_type {};
	#endif
	#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
	template <>			struct is_integral<char16_t>			: public true_type {};
	template <>			struct is_integral<char32_t>			: public true_type {};
	#endif
	template <>			struct is_integral<short>				: public true_type {};
	template <>			struct is_integral<unsigned short>		: public true_type {};
	template <>			struct is_integral<int>					: public true_type {};
	template <>			struct is_integral<unsigned int>		: public true_type {};
	template <>			struct is_integral<long>				: public true_type {};
	template <>			struct is_integral<unsigned long>		: public true_type {};
	template <>			struct is_integral<long long>			: public true_type {};
	template <>			struct is_integral<unsigned long long>	: public true_type {};
	#ifdef __SIZEOF_INT128__
	template <>			struct is_integral<__int128_t>			: public true_type {};
	template <>			struct is_integral<__uint128_t>			: public true_type {};		
	#endif // sizeof_int128_
}

#endif
