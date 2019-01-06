/**
 * @file   image.hxx
 * @Author: zie87
 * @Date:   2017-10-19 17:35:02
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-23 05:25:31
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_IMAGE_IMAGE_HXX
#define SDL2_CXX_IMAGE_IMAGE_HXX

#include <SDL_image.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/video/surface.hxx>

namespace sdl2
{

  enum class img_flags : std::underlying_type_t<IMG_InitFlags>
  {
    jpg = IMG_INIT_JPG,
    png = IMG_INIT_PNG,
    tif = IMG_INIT_TIF,
    webp = IMG_INIT_WEBP
  };

  template <>
  struct enable_bitmask_operators<img_flags>
  {
    static const bool enable = true;
  };

  class img_exception : public exception
  {
  public:
    static inline std::string last_error()
    {
      std::string result(IMG_GetError());
      SDL_ClearError();
      return result;
    }

    img_exception() : exception(last_error()) {}
    img_exception(const std::string& str) : exception(str) {}
    virtual ~img_exception() = default;
  };

#define SDL2_CXX_IMG_CHECK(condition)                                                                                                                          \
  do                                                                                                                                                           \
  {                                                                                                                                                            \
    if (!(condition)) throw img_exception();                                                                                                                   \
  } while (SDL_NULL_WHILE_LOOP_CONDITION);

  namespace img
  {
    inline surface load(const std::string& img_path) { return to_cxx_type(IMG_Load(img_path.c_str())); }

    inline void save_png(surface& surface, const std::string& img_path) { SDL2_CXX_IMG_CHECK(::IMG_SavePNG(to_sdl_type(surface), img_path.c_str())); }
    inline void save_jpg(surface& surface, const std::string& img_path, int quality)
    {
      SDL2_CXX_IMG_CHECK(::IMG_SaveJPG(to_sdl_type(surface), img_path.c_str(), quality));
    }

    struct init_guard
    {
      explicit init_guard(img_flags flag) { SDL2_CXX_IMG_CHECK(::IMG_Init(static_cast<std::underlying_type_t<img_flags>>(flag)) > 0); }
      explicit init_guard(std::initializer_list<img_flags> flags) { SDL2_CXX_IMG_CHECK(::IMG_Init(combine(flags)) > 0); }

      init_guard(init_guard&&) noexcept = default;
      init_guard& operator=(init_guard&&) noexcept = default;

      ~init_guard() { ::IMG_Quit(); }
    };

  } // namespace img
} // namespace sdl2

#endif