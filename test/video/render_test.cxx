/**
* @file   render_test.cxx
* @Author: zie87
* @Date:   2017-10-17 05:07:32
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-17 06:37:40
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/video/render.hxx>

#include "SDL.h"
#include <catch.hpp>

TEST_CASE("check renderer wrapper", "[video]") 
{
  SDL_VideoInit(NULL);

  SECTION("Basic construction test") 
  {
    sdl2::window window("renderer test window", 120, 80);
    {
      try
      {
        {
          sdl2::renderer renderer(window);
        }
        {
          sdl2::renderer renderer(window, sdl2::renderer_flags::software);
        }
      } catch(...)
      {
        REQUIRE(false);
      }
    }
  }

  SDL_VideoQuit();
}