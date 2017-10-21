/**
* @file   surface_test.cxx
* @Author: zie87
* @Date:   2017-10-19 03:59:33
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 10:28:40
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/video/surface.hxx>

#include "SDL.h"
#include <catch.hpp>

TEST_CASE("check surface wrapper", "[video]") 
{
  SDL_VideoInit(NULL);

  SECTION("Basic construction test") 
  {
    // sdl2::window window("renderer test window", 120, 80);
    // {
    //   try
    //   {
    //     {
    //       sdl2::renderer renderer(window);
    //       renderer.clear();
    //       renderer.present();
    //     }
    //     {
    //       sdl2::renderer renderer(window, sdl2::renderer_flags::software);
    //       renderer.clear();
    //       renderer.present();
    //     }
    //   } catch(...)
    //   {
    //     REQUIRE(false);
    //   }
    // }
  }

  SECTION("load functions")
  {
    try
    {
      {
        sdl2::surface surface = sdl2::load_bmp(TEST_DATA"/rider.bmp");
      }
    } catch(...)
    {
      REQUIRE(false);
    }
  }

  SDL_VideoQuit();
}