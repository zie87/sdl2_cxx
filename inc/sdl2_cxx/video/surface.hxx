/**
* @file   surface.hxx
* @Author: zie87
* @Date:   2017-10-19 03:43:23
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 17:42:05
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_SURFACE_HXX
#define SDL2_CXX_VIDEO_SURFACE_HXX

#include <SDL_surface.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/video/rect.hxx>
#include <sdl2_cxx/video/pixels.hxx>

namespace sdl2
{
  namespace detail 
  {
    template <typename Derived>
    struct surface_api 
    {
      inline int width() const noexcept { return to_sdl_type(*this)->w; }
      inline int height() const noexcept { return to_sdl_type(*this)->h; }

      inline int ref_count() const noexcept { return to_sdl_type(*this)->refcount; }
      inline pixel_format_ref format() const noexcept { return pixel_format_ref( to_sdl_type(*this)->format ); }
      inline pixel_format_type format_type() const noexcept { return format().format(); }

      inline void fill( uint8_t r, uint8_t g, uint8_t b ) { SDL2_CXX_CHECK( SDL_FillRect( to_sdl_type(*this), nullptr, SDL_MapRGB( to_sdl_type(*this)->format, r, g, b) ) == 0 ); }
      inline void fill( const rect& dst, uint8_t r, uint8_t g, uint8_t b ) { SDL2_CXX_CHECK( SDL_FillRect( to_sdl_type(*this), to_sdl_type(dst), SDL_MapRGB( to_sdl_type(*this)->format, r, g, b) ) >= 0 ); }

      template<class T>
      inline void blit( surface_api<T>& dst) { SDL2_CXX_CHECK( SDL_BlitSurface( to_sdl_type(*this), nullptr, to_sdl_type(dst), nullptr ) == 0 ); }

      template<class T>
      inline void blit( surface_api<T>& dst, rect& dstrect) { SDL2_CXX_CHECK( SDL_BlitSurface( to_sdl_type(*this), nullptr, to_sdl_type(dst), to_sdl_type(dstrect) ) == 0 ); }

      template<class T>
      inline void blit( const rect& srcrect, surface_api<T>& dst) { SDL2_CXX_CHECK( SDL_BlitSurface( to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), nullptr ) == 0 ); }

      template<class T>
      inline void blit( const rect& srcrect, surface_api<T>& dst, rect& dstrect) { SDL2_CXX_CHECK( SDL_BlitSurface( to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), to_sdl_type(dstrect) ) == 0 ); }

      template<class T>
      inline void blit_scaled( surface_api<T>& dst) { SDL2_CXX_CHECK( SDL_BlitScaled( to_sdl_type(*this), nullptr, to_sdl_type(dst), nullptr ) == 0 ); }

      template<class T>
      inline void blit_scaled( surface_api<T>& dst, rect& dstrect) { SDL2_CXX_CHECK( SDL_BlitScaled( to_sdl_type(*this), nullptr, to_sdl_type(dst), to_sdl_type(dstrect) ) == 0 ); }

      template<class T>
      inline void blit_scaled( const rect& srcrect, surface_api<T>& dst) { SDL2_CXX_CHECK( SDL_BlitScaled( to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), nullptr ) == 0 ); }

      template<class T>
      inline void blit_scaled( const rect& srcrect, surface_api<T>& dst, rect& dstrect) { SDL2_CXX_CHECK( SDL_BlitScaled( to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), to_sdl_type(dstrect) ) == 0 ); }


      explicit operator bool() const { return to_sdl_type(*this) != nullptr; }

      friend SDL_Surface* to_sdl_type(const surface_api& self) { return to_sdl_type(static_cast<const Derived&>(self)); }

      protected:
        virtual ~surface_api() = default;
    };
  } // namespace detail

  class surface final : public detail::surface_api<surface>
  {
    public:
      static surface load_bmp(const std::string& bmp_path) { return surface(SDL_LoadBMP(bmp_path.c_str())); }

      surface(const surface& sf) noexcept : m_surface(sf.m_surface.get()) { m_surface->refcount += 1; }
      surface( surface&& sf ) noexcept : m_surface( std::move(sf.m_surface) ) {}
      surface& operator=(surface sf) noexcept 
      { 
        m_surface = std::move(sf.m_surface);
        return *this; 
      }

      surface(int width, int height, int depth, uint32_t r_mask, uint32_t g_mask, uint32_t b_mask, uint32_t a_mask )
      : m_surface(SDL_CreateRGBSurface( 0, width, height, depth, r_mask, g_mask, b_mask, a_mask ))
      {
        SDL2_CXX_CHECK( m_surface != nullptr );
      }

      template <typename S, typename P>
      surface(const detail::surface_api<S>& src, const detail::pixel_format_api<P>& fmt)
      : m_surface( SDL_ConvertSurface( to_sdl_type(src), to_sdl_type(fmt), 0 ) )
      {
        SDL2_CXX_CHECK( m_surface != nullptr );
      }

      template <typename S>
      surface(const detail::surface_api<S>& src, pixel_format_type type)
      : m_surface( SDL_ConvertSurfaceFormat( to_sdl_type(src), underlying_cast(type), 0 ) )
      {
        SDL2_CXX_CHECK( m_surface != nullptr );
      }

      ~surface() = default;
    private:
      explicit surface(SDL_Surface* s) : m_surface(s) { SDL2_CXX_CHECK( m_surface != nullptr );}

      detail::sdl_ptr<SDL_Surface, SDL_FreeSurface> m_surface = nullptr;

      friend surface to_cxx_type(SDL_Surface*);
      friend SDL_Surface* to_sdl_type(const surface&) noexcept;
  };

  inline surface to_cxx_type(SDL_Surface* s) { return surface(s); } ;
  inline SDL_Surface* to_sdl_type(const surface& s) noexcept { return s.m_surface.get(); }

  class surface_ref final : public detail::surface_api<surface_ref>
  {
    public:
      explicit surface_ref(SDL_Surface* sf) noexcept : m_surface(sf) {}
      explicit surface_ref(const surface& sf) noexcept : m_surface( to_sdl_type(sf) ) {}

      surface_ref& operator=(SDL_Surface* other) noexcept
      {
          m_surface = other;
          return *this;
      }

      surface_ref& operator=(const surface& other) noexcept
      {
          m_surface = to_sdl_type(other);
          return *this;
      }

      friend bool operator==(const surface_ref& lhs, const surface_ref& rhs) { return lhs.m_surface == rhs.m_surface; }
    
    private:
      SDL_Surface* m_surface = nullptr;

      friend SDL_Surface* to_sdl_type(const surface_ref&) noexcept;
  };

  inline SDL_Surface* to_sdl_type(const surface_ref& s) noexcept { return s.m_surface; }
} // namespace sdl2

#endif