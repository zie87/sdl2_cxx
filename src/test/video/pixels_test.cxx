/**
 *  @file    pixels_test.cxx
 *  @author  zie87
 *  @date    2017-10-23 20:16:54
 *  @version 2017-10-23 20:22:14
 *
 *  @brief Brief description of file.
 *
 *  Detailed description of file.
 *
 **/

#include <sdl2_cxx/video/pixels.hxx>

#include <catch.hpp>

TEST_CASE("check pixels wrapper", "[video]")
{
  sdl2::pixel_format p_format(sdl2::pixel_format_type::argb32);
  REQUIRE(sdl2::pixel_format_type::argb32 == p_format.format());
}