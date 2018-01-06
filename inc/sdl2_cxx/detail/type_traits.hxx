/**
 * @file   type_traits.hxx
 * @Author: zie87
 * @Date:   2017-10-09 19:52:46
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-18 21:50:52
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_DETAIL_BITMASK_HXX
#define SDL2_CXX_DETAIL_BITMASK_HXX

#include <bitset>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <numeric>

namespace sdl2
{
  template <bool B>
  using meta_if = std::conditional_t<B, std::true_type, std::false_type>;

  template <typename...>
  using void_t = void;

  template <typename T>
  using concept = std::enable_if<T::value, std::nullptr_t>;

  template <typename T>
  using concept_t = typename concept<T>::type;

  template <typename T, typename U>
  using concept_is_same = concept_t<std::is_same<T, U>>;

  template <typename E, typename = typename std::is_enum<E>::type>
  struct safe_underlying_type
  {
    using type = E;
  };

  template <typename E>
  struct safe_underlying_type<E, std::true_type>
  {
    using type = std::underlying_type_t<E>;
  };

  template <typename E>
  using safe_underlying_type_t = typename safe_underlying_type<E>::type;

  template <typename E>
  constexpr safe_underlying_type_t<E> underlying_cast(E e) noexcept
  {
    return static_cast<safe_underlying_type_t<E>>(e);
  }

  template <typename E>
  struct enable_bitmask_operators
  {
    static const bool enable = false;
  };

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator|(E lhs, E rhs)
  {
    return static_cast<E>(underlying_cast(lhs) | underlying_cast(rhs));
  }

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator&(E lhs, E rhs)
  {
    return static_cast<E>(underlying_cast(lhs) & underlying_cast(rhs));
  }

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator^(E lhs, E rhs)
  {
    return static_cast<E>(underlying_cast(lhs) ^ underlying_cast(rhs));
  }

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator~(E lhs)
  {
    return static_cast<E>(~underlying_cast(lhs));
  }

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator|=(E& lhs, E rhs)
  {
    lhs = static_cast<E>(underlying_cast(lhs) | underlying_cast(rhs));
    return lhs;
  }

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator&=(E& lhs, E rhs)
  {
    lhs = static_cast<E>(underlying_cast(lhs) & underlying_cast(rhs));
    return lhs;
  }

  template <typename E>
  typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator^=(E& lhs, E rhs)
  {
    lhs = static_cast<E>(underlying_cast(lhs) ^ underlying_cast(rhs));
    return lhs;
  }

  template <typename E, typename = std::enable_if<std::is_enum<E>::value>>
  std::underlying_type_t<E> combine(std::initializer_list<E> ilist)
  {
    return static_cast<std::underlying_type_t<E>>(accumulate(std::begin(ilist), std::end(ilist), static_cast<E>(0), std::bit_or<>{}));
  }

} // namespace sdl2

#endif