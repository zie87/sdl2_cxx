/**
* @file   image_test.cxx
* @Author: zie87
* @Date:   2017-10-21 10:27:14
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 10:33:35
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
        sdl2::surface surface = sdl2::image::load(TEST_DATA"/rider.png");
      }
    } catch(...)
    {
      REQUIRE(false);
    }
  }
}