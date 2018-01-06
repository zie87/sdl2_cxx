/**
 *  @file    color_test.cxx
 *  @author  zie87
 *  @date    2017-10-23 20:16:54
 *  @version 2017-10-23 20:20:16
 *
 *  @brief Brief description of file.
 *
 *  Detailed description of file.
 *
 **/

#include <sdl2_cxx/video/color.hxx>

#include <catch.hpp>

TEST_CASE("check color wrapper", "[video]")
{
  sdl2::color color(100, 110, 120, 140);
  REQUIRE(100 == color.red());
  REQUIRE(110 == color.green());
  REQUIRE(120 == color.blue());
  REQUIRE(140 == color.alpha());
}