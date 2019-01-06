/**
 *  @file    surface.hxx
 *  @author  zie87
 *  @date    2017-10-19 03:43:23
 *  @version 2017-10-23 20:06:16
 *
 *  @brief Brief description of file.
 *
 *  Detailed description of file.
 *
 **/

#ifndef SDL2_CXX_VIDEO_SURFACE_HXX
#define SDL2_CXX_VIDEO_SURFACE_HXX

#include <SDL_surface.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>
#include <sdl2_cxx/video/pixels.hxx>
#include <sdl2_cxx/video/rect.hxx>

namespace sdl2
{
  namespace detail
  {
    template <typename Derived>
    struct surface_api
    {
      inline int width() const noexcept { return to_sdl_type(*this)->w; }
      inline int height() const noexcept { return to_sdl_type(*this)->h; }
      inline int pitch() const noexcept { return to_sdl_type(*this)->pitch; }

      inline int ref_count() const noexcept { return to_sdl_type(*this)->refcount; }
      inline pixel_format_ref format() const noexcept { return pixel_format_ref(to_sdl_type(*this)->format); }
      inline pixel_format_type format_type() const noexcept { return format().format(); }

      inline void fill(uint32_t key) { SDL2_CXX_CHECK(SDL_FillRect(to_sdl_type(*this), nullptr, key) == 0); }
      inline void fill(uint8_t r, uint8_t g, uint8_t b) { fill(SDL_MapRGB(to_sdl_type(*this)->format, r, g, b)); }

      inline void fill(const rect& dst, uint32_t key) { SDL2_CXX_CHECK(SDL_FillRect(to_sdl_type(*this), to_sdl_type(dst), key) == 0); }
      inline void fill(const rect& dst, uint8_t r, uint8_t g, uint8_t b) { fill(dst, SDL_MapRGB(to_sdl_type(*this)->format, r, g, b)); }

      inline void set_color_key(bool enable, uint32_t key) { SDL2_CXX_CHECK(SDL_SetColorKey(to_sdl_type(*this), enable ? SDL_TRUE : SDL_FALSE, key) == 0); }
      inline void set_color_key(bool enable, uint8_t r, uint8_t g, uint8_t b) { set_color_key(enable, SDL_MapRGB(to_sdl_type(*this)->format, r, g, b)); }

      inline uint32_t get_color_key() const
      {
        uint32_t key = 0;
        SDL2_CXX_CHECK(SDL_GetColorKey(to_sdl_type(*this), key) == 0);
        return key;
      }

      template <class T>
      inline void blit(surface_api<T>& dst)
      {
        SDL2_CXX_CHECK(SDL_BlitSurface(to_sdl_type(*this), nullptr, to_sdl_type(dst), nullptr) == 0);
      }

      template <class T>
      inline void blit(surface_api<T>& dst, rect& dstrect)
      {
        SDL2_CXX_CHECK(SDL_BlitSurface(to_sdl_type(*this), nullptr, to_sdl_type(dst), to_sdl_type(dstrect)) == 0);
      }

      template <class T>
      inline void blit(const rect& srcrect, surface_api<T>& dst)
      {
        SDL2_CXX_CHECK(SDL_BlitSurface(to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), nullptr) == 0);
      }

      template <class T>
      inline void blit(const rect& srcrect, surface_api<T>& dst, rect& dstrect)
      {
        SDL2_CXX_CHECK(SDL_BlitSurface(to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), to_sdl_type(dstrect)) == 0);
      }

      template <class T>
      inline void blit_scaled(surface_api<T>& dst)
      {
        SDL2_CXX_CHECK(SDL_BlitScaled(to_sdl_type(*this), nullptr, to_sdl_type(dst), nullptr) == 0);
      }

      template <class T>
      inline void blit_scaled(surface_api<T>& dst, rect& dstrect)
      {
        SDL2_CXX_CHECK(SDL_BlitScaled(to_sdl_type(*this), nullptr, to_sdl_type(dst), to_sdl_type(dstrect)) == 0);
      }

      template <class T>
      inline void blit_scaled(const rect& srcrect, surface_api<T>& dst)
      {
        SDL2_CXX_CHECK(SDL_BlitScaled(to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), nullptr) == 0);
      }

      template <class T>
      inline void blit_scaled(const rect& srcrect, surface_api<T>& dst, rect& dstrect)
      {
        SDL2_CXX_CHECK(SDL_BlitScaled(to_sdl_type(*this), to_sdl_type(srcrect), to_sdl_type(dst), to_sdl_type(dstrect)) == 0);
      }

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
    surface(surface&& sf) noexcept : m_surface(std::move(sf.m_surface)) {}
    surface& operator=(surface sf) noexcept
    {
      m_surface = std::move(sf.m_surface);
      return *this;
    }

    surface(int width, int height, int depth, uint32_t r_mask, uint32_t g_mask, uint32_t b_mask, uint32_t a_mask)
        : m_surface(SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask))
    {
      SDL2_CXX_CHECK(m_surface != nullptr);
    }

    template <typename P>
    surface(int width, int height, const detail::pixel_format_api<P>& fmt)
        : surface(width, height, fmt.bits_per_pixel(), fmt.r_mask(), fmt.g_mask(), fmt.b_mask(), fmt.a_mask())
    {
    }

    template <typename S, typename P>
    surface(const detail::surface_api<S>& src, const detail::pixel_format_api<P>& fmt) : m_surface(SDL_ConvertSurface(to_sdl_type(src), to_sdl_type(fmt), 0))
    {
      SDL2_CXX_CHECK(m_surface != nullptr);
    }

    template <typename S>
    surface(const detail::surface_api<S>& src, pixel_format_type type) : m_surface(SDL_ConvertSurfaceFormat(to_sdl_type(src), underlying_cast(type), 0))
    {
      SDL2_CXX_CHECK(m_surface != nullptr);
    }

    ~surface() = default;

  private:
    explicit surface(SDL_Surface* s) : m_surface(s) { SDL2_CXX_CHECK(m_surface != nullptr); }

    detail::sdl_ptr<SDL_Surface, SDL_FreeSurface> m_surface = nullptr;

    friend surface to_cxx_type(SDL_Surface*);
    friend SDL_Surface* to_sdl_type(const surface&) noexcept;
  };

  inline surface to_cxx_type(SDL_Surface* s) { return surface(s); };
  inline SDL_Surface* to_sdl_type(const surface& s) noexcept { return s.m_surface.get(); }

  class surface_ref final : public detail::surface_api<surface_ref>
  {
  public:
    explicit surface_ref(SDL_Surface* sf) noexcept : m_surface(sf) {}
    explicit surface_ref(const surface& sf) noexcept : m_surface(to_sdl_type(sf)) {}

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

  // inline void
  // convert_pixels(int width, int height, pixel_format_type src_format, const void* src, int src_pitch, pixel_format_type dst_format, void* dst, int dst_pitch)

  template <typename S>
  inline void convert_pixels(const detail::surface_api<surface>& surface, const rect& src_rect, pixel_format_type dst_format, void* dst, int dst_pitch)
  {
    const auto width = src_rect.width();
    const auto height = src_rect.height();
    const auto pitch = surface.pitch();
    const auto bytes_per_pixel = surface.format().bytes_per_pixel();
    const auto format = surface.format_type();

    const char* pixel_data = static_cast<const char*>(to_sdl_type(surface)->pixels);
    const auto* pixel_ptr = pixel_data + (pitch * src_rect.y()) + src_rect.x() * bytes_per_pixel;

    convert_pixels(width, height, format, static_cast<const void*>(pixel_ptr), pitch, dst_format, dst, dst_pitch);
  }

  template <typename S>
  inline void convert_pixels(const detail::surface_api<surface>& surface, pixel_format_type dst_format, void* dst, int dst_pitch)
  {
    const rect src_rect(0, 0, surface.width(), surface.height());
    convert_pixels<S>(surface, src_rect, dst_format, dst, dst_pitch);
  }

} // namespace sdl2

#endif