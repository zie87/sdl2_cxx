/**
* @file   bitmask.hxx
* @Author: zie87
* @Date:   2017-10-09 19:52:46
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-09 21:07:33
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_DETAIL_BITMASK_HXX
#define SDL2_CXX_DETAIL_BITMASK_HXX

#include <bitset>

namespace sdl2
{

template<typename E>
struct enable_bitmask_operators{ static const bool enable=false; };

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E>::type operator|(E lhs,E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>( static_cast<underlying>(lhs) | static_cast<underlying>(rhs) );
}

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E>::type operator&(E lhs,E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E>::type operator^(E lhs,E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E>::type operator~(E lhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(~static_cast<underlying>(lhs));
}

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E&>::type operator|=(E& lhs,E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    lhs=static_cast<E>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E&>::type operator&=(E& lhs,E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    lhs=static_cast<E>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

template<typename E>
typename std::enable_if<enable_bitmask_operators<E>::enable,E&>::type operator^=(E& lhs,E rhs)
{
    typedef typename std::underlying_type<E>::type underlying;
    lhs=static_cast<E>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}

} // namespace sdl2

#endif