/**
* @file   pixels.hxx
* @Author: zie87
* @Date:   2017-10-19 06:00:07
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-19 06:04:59
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_PIXELS_HXX
#define SDL2_CXX_VIDEO_PIXELS_HXX

#include <SDL_pixels.h>
#include <sdl2_cxx/core/stdinc.hxx>

namespace sdl2
{
  enum class pixel_format_type : uint32_t
  {
    unknown     = SDL_PIXELFORMAT_UNKNOWN,
    index1_lsb  = SDL_PIXELFORMAT_INDEX1LSB,
    index1_msb  = SDL_PIXELFORMAT_INDEX1MSB,
    index4_lsb  = SDL_PIXELFORMAT_INDEX4LSB,
    index4_msb  = SDL_PIXELFORMAT_INDEX4MSB,
    index8      = SDL_PIXELFORMAT_INDEX8,
    rgb332      = SDL_PIXELFORMAT_RGB332,
    rgb444      = SDL_PIXELFORMAT_RGB444,
    rgb555      = SDL_PIXELFORMAT_RGB555,
    bgr555      = SDL_PIXELFORMAT_BGR555,
    argb4444    = SDL_PIXELFORMAT_ARGB4444,
    rgba4444    = SDL_PIXELFORMAT_RGBA4444,
    abgr4444    = SDL_PIXELFORMAT_ABGR4444,
    bgra4444    = SDL_PIXELFORMAT_BGRA4444,
    argb1555    = SDL_PIXELFORMAT_ARGB1555,
    rgba5551    = SDL_PIXELFORMAT_RGBA5551,
    abgr1555    = SDL_PIXELFORMAT_ABGR1555,
    bgra5551    = SDL_PIXELFORMAT_BGRA5551,
    rgb565      = SDL_PIXELFORMAT_RGB565,
    bgr565      = SDL_PIXELFORMAT_BGR565,
    rgb24       = SDL_PIXELFORMAT_RGB24,
    bgr24       = SDL_PIXELFORMAT_BGR24,
    rgb888      = SDL_PIXELFORMAT_RGB888,
    rgbx8888    = SDL_PIXELFORMAT_RGBX8888,
    bgr888      = SDL_PIXELFORMAT_BGR888,
    bgrx8888    = SDL_PIXELFORMAT_BGRX8888,
    argb8888    = SDL_PIXELFORMAT_ARGB8888,
    rgba8888    = SDL_PIXELFORMAT_RGBA8888,
    abgr8888    = SDL_PIXELFORMAT_ABGR8888,
    bgra8888    = SDL_PIXELFORMAT_BGRA8888,
    argb2101010 = SDL_PIXELFORMAT_ARGB2101010,
    rgba32      = SDL_PIXELFORMAT_RGBA32,
    argb32      = SDL_PIXELFORMAT_ARGB32,
    bgra32      = SDL_PIXELFORMAT_BGRA32,
    abgr32      = SDL_PIXELFORMAT_ABGR32,
    yv12        = SDL_PIXELFORMAT_YV12,
    iyuv        = SDL_PIXELFORMAT_IYUV,
    yuy2        = SDL_PIXELFORMAT_YUY2,
    uyvy        = SDL_PIXELFORMAT_UYVY,
    yvyu        = SDL_PIXELFORMAT_YVYU,
    nv12        = SDL_PIXELFORMAT_NV12,
    nv21        = SDL_PIXELFORMAT_NV21
  };
} // namespace sdl2;

#endif