/**
* @file   image.hxx
* @Author: zie87
* @Date:   2017-10-19 17:35:02
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-22 14:22:17
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_IMAGE_IMAGE_HXX
#define SDL2_CXX_IMAGE_IMAGE_HXX

#include <SDL_image.h>

#include <sdl2_cxx/video/surface.hxx> 
#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>

namespace sdl2 
{

struct image
{
  static surface load(const std::string& img_path) { return to_cxx_type(IMG_Load(img_path.c_str())); }
};

enum class img_flags : std::underlying_type_t<IMG_InitFlags>
{
  jpg  = IMG_INIT_JPG,
  png  = IMG_INIT_PNG,
  tif  = IMG_INIT_TIF,
  webp = IMG_INIT_WEBP 
};

template<>
struct enable_bitmask_operators<img_flags>{ static const bool enable = true; };

namespace img
{
  inline std::string last_error() 
  {
      std::string result(IMG_GetError());
      SDL_ClearError();
      return result;
  }
} // img

class img_exception : public exception 
{
public:
    img_exception(): exception(img::last_error()) {}
    img_exception(const std::string& str): exception(str) {}
};

#define SDL2_CXX_IMG_CHECK(condition)                     \
do {                                                      \
    if (!(condition)) throw exception();                  \
} while (SDL_NULL_WHILE_LOOP_CONDITION);

namespace img 
{
  struct init_guard
  {
      explicit init_guard(img_flags flag) { SDL2_CXX_IMG_CHECK(::IMG_Init( static_cast<std::underlying_type_t<img_flags>>(flag) ) > 0);   }
      explicit init_guard(std::initializer_list<img_flags> flags) { SDL2_CXX_IMG_CHECK(::IMG_Init( combine(flags) ) > 0);  }

      init_guard(init_guard&&) noexcept = default;
      init_guard& operator=(init_guard&&) noexcept = default;

      ~init_guard() { ::IMG_Quit(); }
  };

} // namespace img
} // namespace sdl2

#endif