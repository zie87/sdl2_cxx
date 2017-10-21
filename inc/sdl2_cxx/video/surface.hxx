/**
* @file   surface.hxx
* @Author: zie87
* @Date:   2017-10-19 03:43:23
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 12:28:56
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

namespace sdl2
{
  class surface final
  {
    public:
      static surface load_bmp(const std::string& bmp_path) { return surface(SDL_LoadBMP(bmp_path.c_str())); }

      surface(const surface& sf) noexcept : m_surface(sf.m_surface.get()) { m_surface->refcount += 1; }
      surface& operator=(surface sf) noexcept 
      { 
        m_surface = std::move(sf.m_surface);
        return *this; 
      }

      surface( surface&& sf ) noexcept : m_surface( std::move(sf.m_surface) ) {}
      surface& operator=(surface&& sf) noexcept 
      { 
        m_surface = std::move(sf.m_surface);
        return *this; 
      }


      inline int width() const noexcept { return m_surface->w; }
      inline int height() const noexcept { return m_surface->h; }


    private:
      explicit surface(SDL_Surface* s) : m_surface(s) { SDL2_CXX_CHECK( m_surface != nullptr );}

      detail::sdl_ptr<SDL_Surface, SDL_FreeSurface> m_surface = nullptr;

      friend surface to_cxx_type(SDL_Surface*);
      friend SDL_Surface* to_sdl_type(const surface&) noexcept;
  };

  inline surface to_cxx_type(SDL_Surface* s) { return surface(s); } ;
  inline SDL_Surface* to_sdl_type(const surface& s) noexcept { return s.m_surface.get(); }

} // namespace sdl2

#endif