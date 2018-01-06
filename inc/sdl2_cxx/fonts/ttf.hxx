/**
 * @file   ttf.hxx
 * @Author: zie87
 * @Date:   2017-10-22 21:01:52
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-23 17:56:14
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

    ttf_exception() : exception(last_error()) {}
    ttf_exception(const std::string& str) : exception(str) {}
  };

#define SDL2_CXX_TTF_CHECK(condition)                                                                                                                          \
  do                                                                                                                                                           \
  {                                                                                                                                                            \
    if (!(condition)) throw ttf_exception();                                                                                                                   \
  } while (SDL_NULL_WHILE_LOOP_CONDITION);

  /// \todo change struct to namespace
  namespace ttf
  {
    struct init_guard
    {
      explicit init_guard() { SDL2_CXX_TTF_CHECK(TTF_Init() == 0); }

      init_guard(init_guard&&) noexcept = default;
      init_guard& operator=(init_guard&&) noexcept = default;

      ~init_guard() { TTF_Quit(); }
    };

    enum class style : uint8_t
    {
      normal = TTF_STYLE_NORMAL,
      bold = TTF_STYLE_BOLD,
      italic = TTF_STYLE_ITALIC,
      underline = TTF_STYLE_UNDERLINE,
      strikethrough = TTF_STYLE_STRIKETHROUGH
    };

    enum class text_type : uint8_t
    {
      text = 0,
      utf8,
      unicode
    };

    namespace detail
    {
      template <text_type T>
      struct text_generator
      {
      };

      template <>
      struct text_generator<text_type::text>
      {
        static inline SDL_Surface* render_solid(TTF_Font* font, const char* text, const SDL_Color* c)
        {
          SDL_Surface* sf = TTF_RenderText_Solid(font, text, *c);
          SDL2_CXX_TTF_CHECK(sf != nullptr);
          return sf;
        }

        static inline SDL_Surface* render_shaded(TTF_Font* font, const char* text, const SDL_Color* fg, const SDL_Color* bg)
        {
          SDL_Surface* sf = TTF_RenderText_Shaded(font, text, *fg, *bg);
          SDL2_CXX_TTF_CHECK(sf != nullptr);
          return sf;
        }
      };

      template <>
      struct text_generator<text_type::utf8>
      {
        static inline SDL_Surface* render_solid(TTF_Font* font, const char* text, const SDL_Color* c)
        {
          SDL_Surface* sf = TTF_RenderUTF8_Solid(font, text, *c);
          SDL2_CXX_TTF_CHECK(sf != nullptr);
          return sf;
        }

        static inline SDL_Surface* render_shaded(TTF_Font* font, const char* text, const SDL_Color* fg, const SDL_Color* bg)
        {
          SDL_Surface* sf = TTF_RenderUTF8_Shaded(font, text, *fg, *bg);
          SDL2_CXX_TTF_CHECK(sf != nullptr);
          return sf;
        }
      };

      template <>
      struct text_generator<text_type::unicode>
      {
        static inline SDL_Surface* render_solid(TTF_Font* font, const uint16_t* text, const SDL_Color* c)
        {
          SDL_Surface* sf = TTF_RenderUNICODE_Solid(font, text, *c);
          SDL2_CXX_TTF_CHECK(sf != nullptr);
          return sf;
        }

        static inline SDL_Surface* render_shaded(TTF_Font* font, const uint16_t* text, const SDL_Color* fg, const SDL_Color* bg)
        {
          SDL_Surface* sf = TTF_RenderUNICODE_Shaded(font, text, *fg, *bg);
          SDL2_CXX_TTF_CHECK(sf != nullptr);
          return sf;
        }
      };
    }

    class font final : ::sdl2::detail::noncopyable
    {
    private:
    public:
      explicit font(const std::string& file, int ptsize) : ::sdl2::detail::noncopyable(), m_font(TTF_OpenFont(file.c_str(), ptsize))
      {
        SDL2_CXX_TTF_CHECK(m_font != nullptr);
      }

      explicit font(const std::string& file, int ptsize, long idx) : ::sdl2::detail::noncopyable(), m_font(TTF_OpenFontIndex(file.c_str(), ptsize, idx))
      {
        SDL2_CXX_TTF_CHECK(m_font != nullptr);
      }

      font(font&& w) : m_font(std::move(w.m_font)) {}
      font& operator=(font&& w)
      {
        m_font = std::move(w.m_font);
        return *this;
      }

      template <text_type T>
      inline surface render_solid(const std::string& text, const color& c)
      {
        return to_cxx_type(detail::text_generator<T>::render_solid(to_sdl_type(*this), text.c_str(), to_sdl_type(c)));
      }

      inline surface render_solid(const uint16_t* text, const color& c)
      {
        return to_cxx_type(detail::text_generator<text_type::unicode>::render_solid(to_sdl_type(*this), text, to_sdl_type(c)));
      }

      template <text_type T>
      inline surface render_shaded(const std::string& text, const color& fg, const color& bg)
      {
        return to_cxx_type(detail::text_generator<T>::render_shaded(to_sdl_type(*this), text.c_str(), to_sdl_type(fg), to_sdl_type(bg)));
      }

      inline surface render_shaded(const uint16_t* text, const color& fg, const color& bg)
      {
        return to_cxx_type(detail::text_generator<text_type::unicode>::render_shaded(to_sdl_type(*this), text, to_sdl_type(fg), to_sdl_type(bg)));
      }

      friend TTF_Font* to_sdl_type(const font& f) noexcept { return f.m_font.get(); }

    private:
      ::sdl2::detail::sdl_ptr<TTF_Font, TTF_CloseFont> m_font = nullptr;
    };

  }; // namespace ttf

} // namespace sdl2

#endif