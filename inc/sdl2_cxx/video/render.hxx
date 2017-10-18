/**
* @file   render.hxx
* @Author: zie87
* @Date:   2017-10-17 05:48:55
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-18 19:21:19
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_RENDER_HXX
#define SDL2_CXX_VIDEO_RENDER_HXX

#include <SDL_render.h>

#include <sdl2_cxx/detail/bitmask.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>
#include <sdl2_cxx/detail/interfaces.hxx>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/core/stdinc.hxx>
#include <sdl2_cxx/video/window.hxx>



namespace sdl2
{

  enum class renderer_flags : std::underlying_type_t<SDL_RendererFlags>
  {
    none           = 0,
    software       = SDL_RENDERER_SOFTWARE,         /**< The renderer is a software fallback */
    accelerated    = SDL_RENDERER_ACCELERATED,      /**< The renderer uses hardware acceleration */
    present_vsync  = SDL_RENDERER_PRESENTVSYNC,     /**< Present is synchronized with the refresh rate */
    target_texture = SDL_RENDERER_TARGETTEXTURE     /**< The renderer supports rendering to texture */
  };

  template<>
  struct enable_bitmask_operators<renderer_flags>{ static const bool enable = true; };


  namespace detail 
  {
    template <typename Derived>
    struct renderer_api 
    {
      inline void set_draw_color( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) { SDL2_CXX_CHECK( (SDL_SetRenderDrawColor(to_sdl_type(*this), r, g, b, a) >= 0 ) ); }
      inline void get_draw_color( uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a ) const { SDL2_CXX_CHECK( (SDL_GetRenderDrawColor(to_sdl_type(*this), &r, &g, &b, &a) >= 0 ) ); }

      inline void clear() { SDL2_CXX_CHECK( (SDL_RenderClear(to_sdl_type(*this))) >= 0 ); }
      inline void present() noexcept { SDL_RenderPresent(to_sdl_type(*this)); }

      explicit operator bool() const noexcept { return to_sdl_type(*this) != nullptr; }

      friend SDL_Renderer* to_sdl_type(const renderer_api& self) noexcept { return to_sdl_type(static_cast<const Derived&>(self)); }

      protected:
        virtual ~renderer_api() = default;
    };
  } // namespace detail

  class renderer : public detail::renderer_api<renderer>, detail::noncopyable
  {
    public:

      explicit renderer(const window& win, renderer_flags flags = renderer_flags::none) : renderer(win, -1, flags) {}
      explicit renderer(const window& win, int idx, renderer_flags flags = renderer_flags::none)
      : detail::renderer_api<renderer>(), detail::noncopyable(), m_renderer( SDL_CreateRenderer(to_sdl_type(win), idx, static_cast<std::underlying_type_t<renderer_flags>>(flags)) )
      {
        SDL2_CXX_CHECK( m_renderer != nullptr );
      }

      renderer(renderer&& w): m_renderer(std::move(w.m_renderer)) {}
      renderer& operator=(renderer&& w) { m_renderer = std::move(w.m_renderer); return *this; }

      private:
        detail::sdl_ptr<SDL_Renderer, SDL_DestroyRenderer> m_renderer = nullptr;

        friend SDL_Renderer* to_sdl_type(const renderer&) noexcept;
    };

    inline SDL_Renderer* to_sdl_type(const renderer& w) noexcept { return w.m_renderer.get(); }

} // namespace sdl2

#endif