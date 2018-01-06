#ifndef SDL2_CXX_PLATFORM_ENDIAN_HXX
#define SDL2_CXX_PLATFORM_ENDIAN_HXX

#include <SDL_endian.h>

#include <type_traits>
#include <utility>

namespace sdl2
{
    enum class byte_order
    {
        little_endian = SDL_LIL_ENDIAN,
        big_endian = SDL_BIG_ENDIAN,
        native = SDL_BYTEORDER
    };

    namespace detail
    {

        template <byte_order From, byte_order To>
        struct endian_swapper
        {
            static_assert(From != To, "Something has gone wrong with endian_swapper specialisation");

            template <typename T>
            typename std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 2, T> operator()(T x) const
            {
                return SDL_Swap16(x);
            }
            template <typename T>
            typename std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 4, T> operator()(T x) const
            {
                return SDL_Swap32(x);
            }
            template <typename T>
            typename std::enable_if_t<std::is_integral<T>::value && sizeof(T) == 8, T> operator()(T x) const
            {
                return SDL_Swap64(x);
            }

            float operator()(float x) const { return SDL_SwapFloat(x); }
        };

        template <byte_order Order>
        struct endian_swapper<Order, Order>
        {
            template <typename T>
            T&& operator()(T&& t) const
            {
                return std::forward<T>(t);
            }
        };

    } // namespace detail

    template <byte_order From, byte_order To = byte_order::native, typename T>
    T byte_swap(T t)
    {
        return detail::endian_swapper<From, To>{}(t);
    }

} // namespace sdl2

#endif
