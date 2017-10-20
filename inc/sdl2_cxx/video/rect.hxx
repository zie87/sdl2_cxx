/**
* @file   rect.hxx
* @Author: zie87
* @Date:   2017-10-19 04:15:49
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-20 11:00:47
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_RECT_HXX
#define SDL2_CXX_VIDEO_RECT_HXX

#include <SDL_rect.h> 

#include <sdl2_cxx/video/point.hxx>
#include <sdl2_cxx/core/stdinc.hxx>

#include <utility>

namespace sdl2
{
  class rect final
  {
    public:

      explicit rect(int x = 0, int y = 0, int width = 0, int height = 0) noexcept : m_rect{ x, y, width, height } {}
      rect( const rect& r ) noexcept : rect( r.m_rect ) {}

      explicit rect(const SDL_Rect& r) noexcept : m_rect{ r.x, r.y, r.w, r.h } {}
      ~rect() = default;

      rect& operator=( rect r) noexcept
      {
        swap(*this, r);
        return *this;
      }

      inline int& x()       noexcept { return m_rect.x; }
      inline int  x() const noexcept { return m_rect.x; }

      inline int& y()       noexcept { return m_rect.y; }
      inline int  y() const noexcept { return m_rect.y; }

      inline int& width()       noexcept { return m_rect.w; }
      inline int  width() const noexcept { return m_rect.w; }

      inline int& height()       noexcept { return m_rect.h; }
      inline int  height() const noexcept { return m_rect.h; }

      inline void set_coordinates( int x, int y) noexcept 
      {
        m_rect.x = x;
        m_rect.y = y;
      }

      inline void set_dimension( int w, int h) noexcept 
      {
        m_rect.w = w;
        m_rect.h = h;
      }

      inline void set( int x, int y, int w, int h ) noexcept
      {
        set_coordinates(x, y);
        set_dimension(w, h);
      }

      inline bool empty() const noexcept { return ::SDL_RectEmpty( &m_rect ); }

      inline bool point_in( const point& p ) const noexcept { return SDL_TRUE == ::SDL_PointInRect( to_sdl_type(p), &m_rect ); }
      inline bool has_intersection(const rect& r) const noexcept { return SDL_TRUE == ::SDL_HasIntersection( &m_rect, to_sdl_type(r) ); }

      inline rect intersection_rectangle( const rect& r ) const noexcept
      {
        rect out;
        if(SDL_FALSE == SDL_IntersectRect( &m_rect, to_sdl_type(r), to_sdl_type(out) ) ) { out.set(0,0,0,0); }
        return out;
      }

      inline bool intersection_line(int& x1, int& y1, int& x2, int& y2 ) const noexcept { return SDL_TRUE == ::SDL_IntersectRectAndLine( &m_rect, &x1, &y1, &x2, &y2 ); }
      inline bool intersection_line(point& start, point& end ) const noexcept { return SDL_TRUE == ::SDL_IntersectRectAndLine( &m_rect, &(start.x()), &(start.y()), &(end.x()), &(end.y()) ); }
     inline rect union_rectangel( const rect& r ) const noexcept
     {
       rect out;
       SDL_UnionRect( &m_rect, to_sdl_type(r), to_sdl_type(out) );
       return out;
     }

      friend void swap( rect& lhs, rect& rhs ) noexcept
      {
        using std::swap;
        swap( lhs.m_rect.x, rhs.m_rect.x );
        swap( lhs.m_rect.y, rhs.m_rect.y );
        swap( lhs.m_rect.w, rhs.m_rect.w );
        swap( lhs.m_rect.h, rhs.m_rect.h );
      }

    private:
      SDL_Rect m_rect;

      friend       SDL_Rect* to_sdl_type(rect&);
      friend const SDL_Rect* to_sdl_type(const rect&);
  };

  inline       SDL_Rect* to_sdl_type(      rect& r) { return (&r.m_rect); }
  inline const SDL_Rect* to_sdl_type(const rect& r) { return (&r.m_rect); }
}

inline bool operator==(const sdl2::rect& lhs, const sdl2::rect& rhs) noexcept { return SDL_TRUE == ::SDL_RectEquals( sdl2::to_sdl_type(lhs), sdl2::to_sdl_type(rhs)); }
inline bool operator!=(const sdl2::rect& lhs, const sdl2::rect& rhs) noexcept { return !(lhs == rhs); }

#endif