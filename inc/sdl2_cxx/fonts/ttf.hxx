/**
* @file   ttf.hxx
* @Author: zie87
* @Date:   2017-10-22 21:01:52
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-23 05:36:07
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDl2_CXX_FONTS_TTF_HXX
#define SDl2_CXX_FONTS_TTF_HXX

#include <SDL_ttf.h>

#include <sdl2_cxx/core/error.hxx>

#include <sdl2_cxx/detail/interfaces.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>

#include <sdl2_cxx/video/color.hxx>
#include <sdl2_cxx/video/surface.hxx>

namespace sdl2
{


class ttf_exception : public exception 
{
public:
  static inline std::string last_error() 
  {
      std::string result(TTF_GetError());
      SDL_ClearError();
      return result;
  }

  ttf_exception(): exception(last_error()) {}
  ttf_exception(const std::string& str): exception(str) {}
};

#define SDL2_CXX_TTF_CHECK(condition)                     \
do {                                                      \
    if (!(condition)) throw ttf_exception();                  \
} while (SDL_NULL_WHILE_LOOP_CONDITION);


/// \todo change struct to namespace
struct ttf 
{
  struct init_guard
  {
      explicit init_guard() { SDL2_CXX_TTF_CHECK(TTF_Init() == 0);   }

      init_guard(init_guard&&) noexcept = default;
      init_guard& operator=(init_guard&&) noexcept = default;

      ~init_guard() { TTF_Quit(); }
  };

  enum class style : uint8_t
  {
    normal        = TTF_STYLE_NORMAL,
    bold          = TTF_STYLE_BOLD,
    italic        = TTF_STYLE_ITALIC,
    underline     = TTF_STYLE_UNDERLINE,
    strikethrough = TTF_STYLE_STRIKETHROUGH
  };

  enum class text_type : uint8_t
  {
    text = 0,
    utf8,
    unicode
  };

  class font final : detail::noncopyable
  {
    private:
      /// \todo make generator template based
      struct text_generator
      {
        static inline SDL_Surface* render_solid( TTF_Font* font, const char* text, const SDL_Color* c)
        {
          SDL_Surface* sf = TTF_RenderText_Solid( font, text, *c );
          SDL2_CXX_TTF_CHECK( sf != nullptr );
          return sf;
        }
      };

    public:
      explicit font(const std::string& file, int ptsize) 
      : detail::noncopyable(), m_font( TTF_OpenFont(file.c_str(), ptsize ) )
      {
        SDL2_CXX_TTF_CHECK( m_font != nullptr );
      }

      explicit font(const std::string& file, int ptsize, long idx) 
      : detail::noncopyable(), m_font( TTF_OpenFontIndex(file.c_str(), ptsize, idx ) )
      {
        SDL2_CXX_TTF_CHECK( m_font != nullptr );
      }

      font(font&& w): m_font(std::move(w.m_font)) {}
      font& operator=(font&& w) { m_font = std::move(w.m_font); return *this; }

      /// \todo make generator template based
      inline surface render_solid( const std::string& text, const color& c )
      {
        return to_cxx_type( text_generator::render_solid(to_sdl_type(*this), text.c_str(), to_sdl_type(c)) );
      }


    private:
      detail::sdl_ptr<TTF_Font, TTF_CloseFont> m_font = nullptr;

      friend TTF_Font* to_sdl_type(const font&) noexcept;
  };

}; // struct ttf

inline TTF_Font* to_sdl_type(const ttf::font& w) noexcept { return w.m_font.get(); }

} // namespace sdl2

#endif