/**
* @file   stdinc.hxx
* @Author: zie87
* @Date:   2017-10-18 18:50:32
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-18 18:59:08
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_CORE_STDINC_HXX
#define SDL2_CXX_CORE_STDINC_HXX

#include <SDL_stdinc.h>

namespace sdl2
{

  using int8_t = Sint8;
  using uint8_t = Uint8;
  using int16_t = Sint16;
  using uint16_t = Uint16;
  using int32_t = Sint32;
  using uint32_t = Uint32;
  using int64_t = Sint64;
  using uint64_t = Uint64;
  using size_t = ::size_t;

} // namespace sdl

#endif