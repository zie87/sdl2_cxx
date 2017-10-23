/**
* @file   color.hxx
* @Author: zie87
* @Date:   2017-10-22 22:04:14
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-22 22:07:03
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_COLOR_HXX
#define SDL2_CXX_VIDEO_COLOR_HXX

#include <SDL_pixels.h>
#include <utility>

namespace sdl2
{
  
  namespace detail
  {
    /**
     * @brief      help structure to provied the color_api to different subclasse
     * @tparam     Derived concret color class
     */
    template <typename Derived>
    struct color_api
    {
      inline uint8_t& red() noexcept { return to_sdl_type(*this)->r; }
      inline uint8_t red() const noexcept { return to_sdl_type(*this)->r; }

      inline uint8_t& green() noexcept { return to_sdl_type(*this)->g; }
      inline uint8_t green() const noexcept { return to_sdl_type(*this)->g; }
  
      inline uint8_t& blue() noexcept { return to_sdl_type(*this)->b; }
      inline uint8_t blue() const noexcept { return to_sdl_type(*this)->b; }
  
      inline uint8_t& alpha() noexcept { return to_sdl_type(*this)->a; }
      inline uint8_t alpha() const noexcept { return to_sdl_type(*this)->a; }

      inline friend SDL_Color* to_sdl_type(color_api& c) { return to_sdl_type(static_cast<Derived&>(c)); }
      inline friend const SDL_Color* to_sdl_type(const color_api& c) { return to_sdl_type(static_cast<const Derived&>(c)); }
      ///@{
      protected:
        virtual ~color_api() = default;
    };

  } // detail


  struct color : public detail::color_api<color>
  {
    explicit color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0 ) : m_color{ r, g, b, a } {}
    color( const color& c) noexcept : m_color{ c.red(), c.green(), c.blue(), c.alpha() } {}

    inline color& operator=(color c) noexcept
    {
      swap(c);
      return *this;
    }

    inline void swap( color& c )
    {
      std::swap( m_color, c.m_color );
    }

  private:
    explicit color(const SDL_Color& c) : m_color{ c.r, c.g, c.b, c.a } {}

    SDL_Color m_color;

    friend       SDL_Color* to_sdl_type(color&);
    friend const SDL_Color* to_sdl_type(const color&);
  };


  inline       SDL_Color* to_sdl_type(color& c) { return (&c.m_color); }
  inline const SDL_Color* to_sdl_type(const color& c) { return (&c.m_color); }

} // namespace sdl2

#endif