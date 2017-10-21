/**
* @file   surface_test.cxx
* @Author: zie87
* @Date:   2017-10-19 03:59:33
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 12:29:19
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

  SECTION("load functions")
  {
    try
    {
      {
        const std::string test_file( TEST_DATA"/rider.bmp" );
        const int width = 123;
        const int height = 87;

        sdl2::surface bmp_sf = sdl2::surface::load_bmp(test_file);
        REQUIRE( width  == bmp_sf.width() );
        REQUIRE( height == bmp_sf.height() );
      }
    } catch(...)
    {
      REQUIRE(false);
    }
  }

  SDL_VideoQuit();
}