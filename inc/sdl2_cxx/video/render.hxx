/**
* @file   render.hxx
* @Author: zie87
* @Date:   2017-10-17 05:48:55
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-22 16:50:21
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_RENDER_HXX
#define SDL2_CXX_VIDEO_RENDER_HXX

#include <SDL_render.h>

#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>
#include <sdl2_cxx/detail/interfaces.hxx>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/core/stdinc.hxx>

#include <sdl2_cxx/video/rect.hxx>
#include <sdl2_cxx/video/window.hxx>
#include <sdl2_cxx/video/surface.hxx>
#include <sdl2_cxx/video/pixels.hxx>

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
;

  enum class renderer_flip : std::underlying_type_t<SDL_RendererFlip>
  {
    none        = SDL_FLIP_NONE,        /**< Do not flip */
    horizontal  = SDL_FLIP_HORIZONTAL,  /**< flip horizontally */
    vertical    = SDL_FLIP_VERTICAL     /**< flip vertically */
  };

  class texture;
  SDL_Texture* to_sdl_type(const texture& w) noexcept;

  namespace detail 
  {
    template <typename Derived>
    struct renderer_api 
    {
      inline void set_draw_color( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) { SDL2_CXX_CHECK( (SDL_SetRenderDrawColor(to_sdl_type(*this), r, g, b, a) >= 0 ) ); }
      inline void get_draw_color( uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a ) const { SDL2_CXX_CHECK( (SDL_GetRenderDrawColor(to_sdl_type(*this), &r, &g, &b, &a) >= 0 ) ); }

      inline void set_viewport( const rect& vp ) { SDL2_CXX_CHECK( (SDL_RenderSetViewport(to_sdl_type(*this), to_sdl_type(vp)) >= 0) ); }
      inline rect get_viewport() const noexcept 
      {
        SDL_Rect r{0,0,0,0};
        SDL_RenderGetViewport( to_sdl_type(*this), &r );
        return rect(r);
      }

      inline void clear() { SDL2_CXX_CHECK( (SDL_RenderClear(to_sdl_type(*this))) >= 0 ); }
      inline void present() noexcept { SDL_RenderPresent(to_sdl_type(*this)); }

      inline void entrie_copy( texture& t) { SDL2_CXX_CHECK( SDL_RenderCopy(to_sdl_type(*this), to_sdl_type(t), nullptr, nullptr) >= 0 ); }
      inline void entrie_copy( texture& t, const rect& dst) { SDL2_CXX_CHECK( SDL_RenderCopy(to_sdl_type(*this), to_sdl_type(t), nullptr, to_sdl_type(dst)) >= 0 ); }

      inline void entrie_copy( texture& t, const double angle, renderer_flip flip = renderer_flip::none ) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), nullptr, nullptr, angle, nullptr, static_cast<SDL_RendererFlip>(flip)) >= 0 ); }
      inline void entrie_copy( texture& t, const double angle, const point& p, renderer_flip flip = renderer_flip::none ) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), nullptr, nullptr, angle, to_sdl_type(p), static_cast<SDL_RendererFlip>(flip)) >= 0 ); }
      inline void entrie_copy( texture& t, const rect& dst, const double angle, renderer_flip flip = renderer_flip::none ) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), nullptr, to_sdl_type(dst), angle, nullptr, static_cast<SDL_RendererFlip>(flip)) >= 0 ); }
      inline void entrie_copy( texture& t, const rect& dst, const double angle, const point& p, renderer_flip flip = renderer_flip::none ) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), nullptr, to_sdl_type(dst), angle, to_sdl_type(p), static_cast<SDL_RendererFlip>(flip)) >= 0 ); }

      inline void copy( texture& t, const rect& src) { SDL2_CXX_CHECK( SDL_RenderCopy(to_sdl_type(*this), to_sdl_type(t), to_sdl_type(src), nullptr) >= 0 ); }
      inline void copy( texture& t, const rect& src, const rect& dst) { SDL2_CXX_CHECK( SDL_RenderCopy(to_sdl_type(*this), to_sdl_type(t), to_sdl_type(src), to_sdl_type(dst)) >= 0 ); }

      inline void copy( texture& t, const rect& src, const double angle, renderer_flip flip = renderer_flip::none) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), to_sdl_type(src), nullptr, angle, nullptr, static_cast<SDL_RendererFlip>(flip)) >= 0 ); }
      inline void copy( texture& t, const rect& src, const double angle, const point& p, renderer_flip flip = renderer_flip::none) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), to_sdl_type(src), nullptr, angle, to_sdl_type(p), static_cast<SDL_RendererFlip>(flip)) >= 0 ); }
      inline void copy( texture& t, const rect& src, const rect& dst, const double angle, renderer_flip flip = renderer_flip::none) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), to_sdl_type(src), to_sdl_type(dst), angle, nullptr, static_cast<SDL_RendererFlip>(flip)) >= 0 ); }
      inline void copy( texture& t, const rect& src, const rect& dst, const double angle, const point& p, renderer_flip flip = renderer_flip::none) { SDL2_CXX_CHECK( SDL_RenderCopyEx(to_sdl_type(*this), to_sdl_type(t), to_sdl_type(src), to_sdl_type(dst), angle, to_sdl_type(p), static_cast<SDL_RendererFlip>(flip)) >= 0 ); }

      inline void fill( const rect& dst ) { SDL2_CXX_CHECK( SDL_RenderFillRect( to_sdl_type(*this), to_sdl_type(dst) ) >= 0 ); }

      inline void draw() { SDL2_CXX_CHECK( SDL_RenderDrawRect( to_sdl_type(*this), nullptr ) >= 0 ); }
      inline void draw( const rect& r ) { SDL2_CXX_CHECK( SDL_RenderDrawRect( to_sdl_type(*this), to_sdl_type(r) ) >= 0 ); }

      inline void draw( const point& p ) { SDL2_CXX_CHECK( SDL_RenderDrawPoint( to_sdl_type(*this), p.x(), p.y() ) >= 0 ); }
      inline void draw( int x, int y ) { SDL2_CXX_CHECK( SDL_RenderDrawPoint( to_sdl_type(*this), x, y ) >= 0 ); }

      inline void draw( const point& p1, const point& p2 ) { SDL2_CXX_CHECK( SDL_RenderDrawLine( to_sdl_type(*this), p1.x(), p1.y(), p2.x(), p2.y() ) >= 0 ); }
      inline void draw( int x1, int y1, int x2, int y2 ) { SDL2_CXX_CHECK( SDL_RenderDrawLine( to_sdl_type(*this), x1, y1, x2, y2 ) >= 0 ); }

      explicit operator bool() const noexcept { return to_sdl_type(*this) != nullptr; }

      friend SDL_Renderer* to_sdl_type(const renderer_api& self) noexcept { return to_sdl_type(static_cast<const Derived&>(self)); }

      protected:
        virtual ~renderer_api() = default;
    };
  } // namespace detail

  class renderer final : public detail::renderer_api<renderer>, detail::noncopyable
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

  enum class texture_access : std::underlying_type_t<SDL_TextureAccess> 
  {
      static_access = SDL_TEXTUREACCESS_STATIC, /**< Changes rarely, not lockable */
      streaming     = SDL_TEXTUREACCESS_STREAMING, /**< Changes frequently, lockable */
      target        = SDL_TEXTUREACCESS_TARGET, /**< Texture can be used as a render target */
  };

  namespace detail 
  {
    template <typename Derived>
    struct texture_api 
    {
      void query_dimension( int& w, int& h) const { SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), NULL, NULL, &w, &h) >= 0 ) ); }
      pixel_format_type query_format() const 
      {
        uint32_t format = SDL_PIXELFORMAT_UNKNOWN;
        SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), &format, NULL, NULL, NULL) >= 0 ) );
        return static_cast<pixel_format_type>(format);
      }

      texture_access query_access() const
      {
        int access = -1;
        SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), NULL, &access, NULL, NULL) >= 0 ) );
        return static_cast<texture_access>(access);
      }

      void query( pixel_format_type& format, texture_access& access, int& w, int& h) const
      {
        uint32_t f = SDL_PIXELFORMAT_UNKNOWN;
        int a = -1;
        SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), &f, &a, &w, &h) >= 0 ) );
        format = static_cast<pixel_format_type>(f);
        access = static_cast<texture_access>(a);
      }

      explicit operator bool() const noexcept { return to_sdl_type(*this) != nullptr; }

      friend SDL_Texture* to_sdl_type(const texture_api& self) noexcept { return to_sdl_type(static_cast<const Derived&>(self)); }

      protected:
        virtual ~texture_api() = default;
    };
  } // namespace detail

  class texture final : public detail::texture_api<texture>, detail::noncopyable
  {
    public:
      explicit texture(const renderer& rend, const surface& s) 
      : detail::texture_api<texture>(), detail::noncopyable()
      , m_texture( SDL_CreateTextureFromSurface(to_sdl_type(rend), to_sdl_type(s)) )
      { SDL2_CXX_CHECK( m_texture != nullptr );}

      texture(texture&& w): m_texture(std::move(w.m_texture)) {}
      texture& operator=(texture&& w) { m_texture = std::move(w.m_texture); return *this; }

      private:
        detail::sdl_ptr<SDL_Texture, SDL_DestroyTexture> m_texture = nullptr;
        friend SDL_Texture* to_sdl_type(const texture&) noexcept;
    };

    inline SDL_Texture* to_sdl_type(const texture& w) noexcept { return w.m_texture.get(); }

} // namespace sdl2

#endif