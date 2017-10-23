/**
* @file   surface_test.cxx
* @Author: zie87
* @Date:   2017-10-19 03:59:33
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 17:39:48
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

  SECTION("load and creation functions")
  {
    try
    {
      {
        const std::string test_file( TEST_DATA"/rider.bmp" );
        const int width = 123;
        const int height = 87;

        sdl2::surface bmp_sf = sdl2::surface::load_bmp(test_file);
        REQUIRE( bmp_sf );
        REQUIRE( width  == bmp_sf.width() );
        REQUIRE( height == bmp_sf.height() );
      
        REQUIRE( 1 == bmp_sf.ref_count()  );
        {
          sdl2::surface copy_sf( bmp_sf );
          REQUIRE( 2 == bmp_sf.ref_count()  );
        }
        REQUIRE( 1 == bmp_sf.ref_count()  );

        sdl2::surface color_sf( 30, 40, 1, 100, 110, 120, 255 );
        REQUIRE( color_sf );
        REQUIRE( 30  == color_sf.width() );
        REQUIRE( 40 == color_sf.height() );

        color_sf = bmp_sf;
        REQUIRE( color_sf );
        REQUIRE( 2 == bmp_sf.ref_count()  );
      }
    } catch(...)
    {
      REQUIRE(false);
    }
  }

  SECTION("blit functions")
  {
      const std::string test_file( TEST_DATA"/rider.bmp" );
      sdl2::surface bmp_sf = sdl2::surface::load_bmp(test_file);
      const int width = bmp_sf.width();
      const int height = bmp_sf.height();

      const int depth = 32;
      const uint32_t rmask = 0xff000000;
      const uint32_t gmask = 0x00ff0000;
      const uint32_t bmask = 0x0000ff00;
      const uint32_t amask = 0x000000ff;

      sdl2::surface dest( 200, 200, depth, rmask, gmask, bmask, amask );
      bmp_sf.blit( dest );

      {
        sdl2::rect destrect(10,10,0,0);
        bmp_sf.blit( dest, destrect );
        REQUIRE(width == destrect.width());
        REQUIRE(height == destrect.height());

        sdl2::rect srcrect(0,0,20,20);
        bmp_sf.blit(srcrect, dest, destrect );
        REQUIRE(srcrect.width() == destrect.width());
        REQUIRE(srcrect.height() == destrect.height());
      }
      {
        sdl2::surface dest( 200, 200, depth, rmask, gmask, bmask, amask );
        bmp_sf.blit_scaled( dest );

        sdl2::rect destrect(10,10,200,200);
        bmp_sf.blit_scaled( dest, destrect );
        REQUIRE(190 == destrect.width());
        REQUIRE(190 == destrect.height());

        sdl2::rect srcrect(0,0,20,20);
        bmp_sf.blit_scaled(srcrect, dest, destrect );
        REQUIRE(190 == destrect.width());
        REQUIRE(190 == destrect.height());
      }
  }

  SDL_VideoQuit();
}