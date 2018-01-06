/**
 * @file   mouse.hxx
 * @Author: zie87
 * @Date:   2017-10-20 16:56:08
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-20 17:00:31
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_EVENTS_MOUSE_HXX
#define SDL2_CXX_EVENTS_MOUSE_HXX

#include <SDL_mouse.h>
#include <sdl2_cxx/core/stdinc.hxx>

namespace sdl2
{
  struct mouse
  {
    enum class button : uint8_t
    {
      left = SDL_BUTTON_LEFT,
      middle = SDL_BUTTON_MIDDLE,
      right = SDL_BUTTON_RIGHT,
      x1 = SDL_BUTTON_X1,
      x2 = SDL_BUTTON_X2
    };
  };
} // namespace sdl2

#endif