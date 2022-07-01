#include <experimental/__config>

#include <initializer_list>
#include <type_traits>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_LFTS

// 3.3.2, Other type transformations
/*
template <class>
class _LIBCPP_TEMPLATE_VIS raw_invocation_type;

template <class _Fn, class ..._Args>
class _LIBCPP_TEMPLATE_VIS raw_invocation_type<_Fn(_Args...)>;

template <class>
class _LIBCPP_TEMPLATE_VIS invokation_type;

template <class _Fn, class ..._Args>
class _LIBCPP_TEMPLATE_VIS invokation_type<_Fn(_Args...)>;

template <class _Tp>
using invokation_type_t = typename invokation_type<_Tp>::type;

template <class _Tp>
using raw_invocation_type_t = typename raw_invocation_type<_Tp>::type;
*/

// 3.3.4, Detection idiom
template <class...> using void_t = void;

struct nonesuch : private _VSTD::__nat { // make nonesuch "not an aggregate"
  ~nonesuch() = delete;
  nonesuch      (nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
  };

template <class _Default, class _AlwaysVoid, template <class...> class _Op, class... _Args>
struct _DETECTOR {
   using value_t = false_type;
   using type = _Default;
   };

template <class _Default, template <class...> class _Op, class... _Args>
struct _DETECTOR<_Default, void_t<_Op<_Args...>>, _Op, _Args...> {
   using value_t = true_type;
   using type = _Op<_Args...>;
   };


template <template<class...> class _Op, class... _Args>
  using is_detected = typename _DETECTOR<nonesuch, void, _Op, _Args...>::value_t;
template <template<class...> class _Op, class... _Args>
  using detected_t = typename _DETECTOR<nonesuch, void, _Op, _Args...>::type;
template <template<class...> class _Op, class... _Args>
  _LIBCPP_CONSTEXPR bool is_detected_v = is_detected<_Op, _Args...>::value;

template <class Default, template<class...> class _Op, class... _Args>
  using detected_or = _DETECTOR<Default, void, _Op, _Args...>;
template <class Default, template<class...> class _Op, class... _Args>
  using detected_or_t = typename detected_or<Default, _Op, _Args...>::type;

template <class Expected, template<class...> class _Op, class... _Args>
  using is_detected_exact = is_same<Expected, detected_t<_Op, _Args...>>;
template <class Expected, template<class...> class _Op, class... _Args>
  _LIBCPP_CONSTEXPR bool is_detected_exact_v = is_detected_exact<Expected, _Op, _Args...>::value;

template <class To, template<class...> class _Op, class... _Args>
  using is_detected_convertible = is_convertible<detected_t<_Op, _Args...>, To>;
template <class To, template<class...> class _Op, class... _Args>
  _LIBCPP_CONSTEXPR bool is_detected_convertible_v = is_detected_convertible<To, _Op, _Args...>::value;


_LIBCPP_END_NAMESPACE_LFTS

#endif /* _LIBCPP_STD_VER > 11 */

#endif /* _LIBCPP_EXPERIMENTAL_TYPE_TRAITS */