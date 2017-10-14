/**
* @file   timer.hxx
* @Author: zie87
* @Date:   2017-10-14 23:58:53
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-15 00:05:05
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_TIME_TIMER_HXX
#define SDL2_CXX_TIME_TIMER_HXX

#include "SDL_timer.h"
#include <chrono>

namespace sdl2
{

struct clock
{
    using rep = uint32_t;
    using period = std::milli;
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<clock>;

    constexpr static bool is_steady = true;

    static time_point now() noexcept { return time_point{duration{SDL_GetTicks()}}; }
};

using time_point = clock::time_point;
using duration = clock::duration;

inline uint64_t performance_counter() { return ::SDL_GetPerformanceCounter(); }
inline uint64_t performance_frequency() { return ::SDL_GetPerformanceFrequency(); }

inline void delay(duration interval) { ::SDL_Delay(interval.count()); }

} // namespace sdl2

#endif
