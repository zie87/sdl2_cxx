/**
* @file   image.hxx
* @Author: zie87
* @Date:   2017-10-19 17:35:02
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-19 17:38:53
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_IMAGE_IMAGE_HXX
#define SDL2_CXX_IMAGE_IMAGE_HXX

#include <SDL_image.h>

#include <sdl2_cxx/video/surface.hxx> 

namespace sdl2 {
namespace image {
 
  static surface load(const std::string& img_path) { return to_cxx_type(IMG_Load(img_path.c_str())); }

} // namespace image
} // namespace sdl2

#endif