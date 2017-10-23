/**
* @file   image_test.cxx
* @Author: zie87
* @Date:   2017-10-21 10:27:14
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-23 05:36:45
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/image/image.hxx>

#include <catch.hpp>

TEST_CASE("test image extension for sdl2", "[image]") 
{
  SECTION("general load function")
  {
    try
    {
      {
        const std::string test_file( TEST_DATA"/rider.bmp" );
        const int width = 123;
        const int height = 87;
        sdl2::surface png_sf = sdl2::img::load(test_file);

        REQUIRE( width  == png_sf.width() );
        REQUIRE( height == png_sf.height() );
      }
    } catch(...)
    {
      REQUIRE(false);
    }
  }
}