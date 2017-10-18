/**
* @file   render_test.cxx
* @Author: zie87
* @Date:   2017-10-17 05:07:32
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-18 19:22:12
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
          renderer.clear();
          renderer.present();
        }
        {
          sdl2::renderer renderer(window, sdl2::renderer_flags::software);
          renderer.clear();
          renderer.present();
        }
      } catch(...)
      {
        REQUIRE(false);
      }
    }
  }

  SECTION("draw functions")
  {
    sdl2::window window("renderer test window", 120, 80);
    sdl2::renderer renderer(window);

    sdl2::uint8_t r = 1;
    sdl2::uint8_t g = 2;
    sdl2::uint8_t b = 3;
    sdl2::uint8_t a = 4;

    renderer.set_draw_color(r,g,b,a);

    sdl2::uint8_t r_tmp = 0;
    sdl2::uint8_t g_tmp = 0;
    sdl2::uint8_t b_tmp = 0;
    sdl2::uint8_t a_tmp = 0;
  
    SDL_GetRenderDrawColor( sdl2::to_sdl_type(renderer), &r_tmp, &g_tmp, &b_tmp, &a_tmp );

    REQUIRE( r == r_tmp );
    REQUIRE( g == g_tmp );
    REQUIRE( b == b_tmp );
    REQUIRE( a == a_tmp );

    r = 0;
    g = 0;
    b = 0;
    a = 0;

    renderer.get_draw_color(r,g,b,a);
    REQUIRE( r == r_tmp );
    REQUIRE( g == g_tmp );
    REQUIRE( b == b_tmp );
    REQUIRE( a == a_tmp );
  }

  SDL_VideoQuit();
}