/**
 * @file   point.hxx
 * @Author: zie87
 * @Date:   2017-10-19 04:39:39
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-19 04:55:47
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_VIDEO_POINT_HXX
#define SDL2_CXX_VIDEO_POINT_HXX

#include <SDL_rect.h>

namespace sdl2
{

  struct point
  {
    explicit point(int x = 0, int y = 0) noexcept : m_point{x, y} {}

    point(const point& p) noexcept : m_point{p.x(), p.y()} {}
    explicit point(const SDL_Point& p) noexcept : m_point{p.x, p.y} {}

    point& operator=(const point& p) noexcept
    {
      set_coordinates(p.m_point.x, p.m_point.y);
      return *this;
    }

    inline int& x() noexcept { return m_point.x; }
    inline int x() const noexcept { return m_point.x; }

    inline int& y() noexcept { return m_point.y; }
    inline int y() const noexcept { return m_point.y; }

    inline void set_coordinates(int x, int y) noexcept
    {
      m_point.x = x;
      m_point.y = y;
    }

  private:
    SDL_Point m_point;

    friend SDL_Point* to_sdl_type(point&);
    friend const SDL_Point* to_sdl_type(const point&);
  };

  inline SDL_Point* to_sdl_type(point& p) { return (&p.m_point); }
  inline const SDL_Point* to_sdl_type(const point& p) { return (&p.m_point); }

} // namespace sdl2

inline bool operator==(const sdl2::point& lhs, const sdl2::point& rhs) noexcept
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}
inline bool operator!=(const sdl2::point& lhs, const sdl2::point& rhs) noexcept
{
  return !(lhs == rhs);
}

#endif