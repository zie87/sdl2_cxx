/**
 * @file   pixels.hxx
 * @Author: zie87
 * @Date:   2017-10-19 06:00:07
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-21 16:43:13
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_VIDEO_PIXELS_HXX
#define SDL2_CXX_VIDEO_PIXELS_HXX

#include <SDL_pixels.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/core/stdinc.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>

namespace sdl2
{
  enum class pixel_format_type : uint32_t
  {
    unknown = SDL_PIXELFORMAT_UNKNOWN,
    index1_lsb = SDL_PIXELFORMAT_INDEX1LSB,
    index1_msb = SDL_PIXELFORMAT_INDEX1MSB,
    index4_lsb = SDL_PIXELFORMAT_INDEX4LSB,
    index4_msb = SDL_PIXELFORMAT_INDEX4MSB,
    index8 = SDL_PIXELFORMAT_INDEX8,
    rgb332 = SDL_PIXELFORMAT_RGB332,
    rgb444 = SDL_PIXELFORMAT_RGB444,
    rgb555 = SDL_PIXELFORMAT_RGB555,
    bgr555 = SDL_PIXELFORMAT_BGR555,
    argb4444 = SDL_PIXELFORMAT_ARGB4444,
    rgba4444 = SDL_PIXELFORMAT_RGBA4444,
    abgr4444 = SDL_PIXELFORMAT_ABGR4444,
    bgra4444 = SDL_PIXELFORMAT_BGRA4444,
    argb1555 = SDL_PIXELFORMAT_ARGB1555,
    rgba5551 = SDL_PIXELFORMAT_RGBA5551,
    abgr1555 = SDL_PIXELFORMAT_ABGR1555,
    bgra5551 = SDL_PIXELFORMAT_BGRA5551,
    rgb565 = SDL_PIXELFORMAT_RGB565,
    bgr565 = SDL_PIXELFORMAT_BGR565,
    rgb24 = SDL_PIXELFORMAT_RGB24,
    bgr24 = SDL_PIXELFORMAT_BGR24,
    rgb888 = SDL_PIXELFORMAT_RGB888,
    rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
    bgr888 = SDL_PIXELFORMAT_BGR888,
    bgrx8888 = SDL_PIXELFORMAT_BGRX8888,
    argb8888 = SDL_PIXELFORMAT_ARGB8888,
    rgba8888 = SDL_PIXELFORMAT_RGBA8888,
    abgr8888 = SDL_PIXELFORMAT_ABGR8888,
    bgra8888 = SDL_PIXELFORMAT_BGRA8888,
    argb2101010 = SDL_PIXELFORMAT_ARGB2101010,
    rgba32 = SDL_PIXELFORMAT_RGBA32,
    argb32 = SDL_PIXELFORMAT_ARGB32,
    bgra32 = SDL_PIXELFORMAT_BGRA32,
    abgr32 = SDL_PIXELFORMAT_ABGR32,
    yv12 = SDL_PIXELFORMAT_YV12,
    iyuv = SDL_PIXELFORMAT_IYUV,
    yuy2 = SDL_PIXELFORMAT_YUY2,
    uyvy = SDL_PIXELFORMAT_UYVY,
    yvyu = SDL_PIXELFORMAT_YVYU,
    nv12 = SDL_PIXELFORMAT_NV12,
    nv21 = SDL_PIXELFORMAT_NV21
  };

  namespace detail
  {

    template <typename Derived>
    struct pixel_format_api
    {
      inline pixel_format_type format() const noexcept { return static_cast<pixel_format_type>(to_sdl_type(*this)->format); }

      inline uint8_t bits_per_pixel() const noexcept { return to_sdl_type(*this)->BitsPerPixel; }
      inline uint8_t bytes_per_pixel() const noexcept { return to_sdl_type(*this)->BytesPerPixel; }

      inline uint32_t r_mask() const noexcept { return to_sdl_type(*this)->Rmask; }
      inline uint32_t g_mask() const noexcept { return to_sdl_type(*this)->Gmask; }
      inline uint32_t b_mask() const noexcept { return to_sdl_type(*this)->Bmask; }
      inline uint32_t a_mask() const noexcept { return to_sdl_type(*this)->Amask; }

      inline uint32_t map_rgb(uint8_t r, uint8_t g, uint8_t b) { return SDL_MapRGB(to_sdl_type(*this), r, g, b); }
      inline uint32_t map_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return SDL_MapRGBA(to_sdl_type(*this), r, g, b, a); }

      inline void get_rgb(uint32_t pixel, uint8_t& r, uint8_t& g, uint8_t& b) { return SDL_GetRGB(pixel, to_sdl_type(*this), &r, &g, &b); }
      inline void get_rgba(uint32_t pixel, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) { return SDL_GetRGBA(pixel, to_sdl_type(*this), &r, &g, &b, &a); }

      inline friend SDL_PixelFormat* to_sdl_type(const pixel_format_api& f) { return to_sdl_type(static_cast<const Derived&>(f)); }

    protected:
      virtual ~pixel_format_api() = default;
    };
  } // namespace detail

  class pixel_format : public detail::pixel_format_api<pixel_format>
  {
  public:
    explicit pixel_format(pixel_format_type format) : m_format(SDL_AllocFormat(static_cast<uint32_t>(format))) { SDL2_CXX_CHECK(m_format != nullptr); }

    pixel_format(const pixel_format& f) noexcept : m_format(f.m_format.get()) { m_format->refcount += 1; }

    pixel_format& operator=(const pixel_format& f) noexcept
    {
      m_format.reset(f.m_format.get());
      m_format->refcount += 1;

      return *this;
    }

    ~pixel_format() = default;

  private:
    detail::sdl_ptr<SDL_PixelFormat, SDL_FreeFormat> m_format;

    friend SDL_PixelFormat* to_sdl_type(const pixel_format&);
  };

  inline SDL_PixelFormat* to_sdl_type(const pixel_format& f) { return f.m_format.get(); }

  class pixel_format_ref : public detail::pixel_format_api<pixel_format_ref>
  {
  public:
    explicit pixel_format_ref(SDL_PixelFormat* format) noexcept : m_format(format) {}

    pixel_format_ref& operator=(SDL_PixelFormat* other) noexcept
    {
      m_format = other;
      return *this;
    }

    virtual ~pixel_format_ref() = default;

  private:
    SDL_PixelFormat* m_format = nullptr;

    friend SDL_PixelFormat* to_sdl_type(const pixel_format_ref&);

    friend bool operator==(const pixel_format_ref& lhs, const pixel_format_ref& rhs) { return lhs.m_format == rhs.m_format; }
    friend bool operator!=(const pixel_format_ref& lhs, const pixel_format_ref& rhs) { return lhs.m_format != rhs.m_format; }
  };

  inline SDL_PixelFormat* to_sdl_type(const pixel_format_ref& f) { return f.m_format; }

  inline void
  convert_pixels(int width, int height, pixel_format_type src_format, const void* src, int src_pitch, pixel_format_type dst_format, void* dst, int dst_pitch)
  {
    SDL2_CXX_CHECK(SDL_ConvertPixels(width, height, static_cast<uint32_t>(src_format), src, src_pitch, static_cast<uint32_t>(dst_format), dst, dst_pitch) == 0);
  }
} // namespace sdl2

#endif