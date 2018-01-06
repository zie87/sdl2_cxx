/**
 * @file   blendmode.hxx
 * @Author: zie87
 * @Date:   2017-10-22 19:02:22
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-22 19:16:07
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_VIDEO_BLENDMODE_HXX
#define SDL2_CXX_VIDEO_BLENDMODE_HXX

#include <SDL_blendmode.h>
#include <sdl2_cxx/detail/type_traits.hxx>

namespace sdl2
{

  struct blend
  {
    enum class mode : std::underlying_type_t<SDL_BlendMode>
    {
      none = SDL_BLENDMODE_NONE,
      blend = SDL_BLENDMODE_BLEND,
      add = SDL_BLENDMODE_ADD,
      mod = SDL_BLENDMODE_MOD,
      invalid = SDL_BLENDMODE_INVALID
    };

    enum class operation : std::underlying_type_t<SDL_BlendOperation>
    {
      add = SDL_BLENDOPERATION_ADD,
      substract = SDL_BLENDOPERATION_SUBTRACT,
      rev_substract = SDL_BLENDOPERATION_REV_SUBTRACT,
      minimum = SDL_BLENDOPERATION_MINIMUM,
      maximum = SDL_BLENDOPERATION_MAXIMUM
    };

    enum class factor : std::underlying_type_t<SDL_BlendFactor>
    {
      zero = SDL_BLENDFACTOR_ZERO,
      one = SDL_BLENDFACTOR_ONE,
      src_color = SDL_BLENDFACTOR_SRC_COLOR,
      one_minus_src_color = SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,
      src_alpha = SDL_BLENDFACTOR_SRC_ALPHA,
      one_minus_src_alpha = SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
      dst_color = SDL_BLENDFACTOR_DST_COLOR,
      one_minus_dst_color = SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,
      dst_alpha = SDL_BLENDFACTOR_DST_ALPHA,
      one_minus_dst_alpha = SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA
    };
  };

} // namespace sdl

#endif