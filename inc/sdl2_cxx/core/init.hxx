/**
* @file   init.hxx
* @Author: zie87
* @Date:   2017-10-09 21:28:25
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-18 21:19:09
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_CORE_INIT_HXX
#define SDL2_CXX_CORE_INIT_HXX

#include <SDL.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>

#include <iostream>

namespace sdl2
{
    enum class init_flags : std::uint32_t
    {
        null           = 0,                       /**< Equivalent to NULL */
        timer          = SDL_INIT_TIMER,          /**< Timer subsystem */
        audio          = SDL_INIT_AUDIO,          /**< Audio subsystem */
        video          = SDL_INIT_VIDEO,          /**< Video subsystem. Automatically initializes the vents subsystem */
        joystick       = SDL_INIT_JOYSTICK,       /**< Joystick subsystem. Automatically initializes the vents subsystem */
        haptic         = SDL_INIT_HAPTIC,         /**< Haptic (force feedback) subsystem */
        gamecontroller = SDL_INIT_GAMECONTROLLER, /**< Controller subsystem. Automatically initializes the joystick subsystem */
        events         = SDL_INIT_EVENTS,         /**< Events subsystem */
        noparachute    = SDL_INIT_NOPARACHUTE,    /** Compatibility. This flag is ignored */
        everything     = SDL_INIT_EVERYTHING      /**< All subsystems */
    };

    template<>
    struct enable_bitmask_operators<init_flags>{ static const bool enable = true; };

    struct init_guard
    {
        init_guard() : init_guard(init_flags::everything) {}
        explicit init_guard(init_flags flag) { SDL2_CXX_CHECK(::SDL_Init( static_cast<std::underlying_type_t<init_flags>>(flag) ) == 0);   }
        explicit init_guard(std::initializer_list<init_flags> flags) { SDL2_CXX_CHECK(::SDL_Init( combine(flags) ) == 0);  }

        ~init_guard() { ::SDL_Quit(); }
    };
}

#endif