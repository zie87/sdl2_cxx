/**
 * @file   point_test.cxx
 * @Author: zie87
 * @Date:   2017-10-19 04:51:08
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-19 04:57:35
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#include <sdl2_cxx/video/point.hxx>

#include <catch.hpp>

TEST_CASE("check point wrapper", "[video]")
{
  SECTION("point construction test")
  {
    // default values
    sdl2::point p1;
    REQUIRE(0 == p1.x());
    REQUIRE(0 == p1.y());

    // value construction
    sdl2::point p2(10, 20);
    REQUIRE(10 == p2.x());
    REQUIRE(20 == p2.y());

    // copy construction
    sdl2::point p3(p2);
    REQUIRE(10 == p3.x());
    REQUIRE(20 == p3.y());

    // check comparsion operators
    REQUIRE(p2 == p3);
    REQUIRE(!(p2 != p3));
  }

  SECTION("point assignment test")
  {
    sdl2::point p1(15, 25);
    sdl2::point p2(35, 45);
    REQUIRE(p1 != p2);

    // assignment operator
    p1 = p2;
    REQUIRE(p1 == p2);

    // coordinate setter
    p1.x() = 10;
    p1.y() = 20;
    REQUIRE(10 == p1.x());
    REQUIRE(20 == p1.y());

    p2.set_coordinates(30, 40);
    REQUIRE(30 == p2.x());
    REQUIRE(40 == p2.y());
  }

  SECTION("point converter test")
  {
    SDL_Point sdl_p{-10, -20};
    sdl2::point p1(-10, -20);

    // raw pointer access
    SDL_Point* sdl_p1 = sdl2::to_sdl_type(p1);
    REQUIRE(sdl_p.x == sdl_p1->x);
    REQUIRE(sdl_p.y == sdl_p1->y);

    sdl_p1->x = -30;
    sdl_p1->y = -40;

    REQUIRE(-30 == p1.x());
    REQUIRE(-40 == p1.y());

    // const access to raw pointer
    const sdl2::point p2(-10, -20);
    const SDL_Point* sdl_p2 = sdl2::to_sdl_type(p2);
    REQUIRE(sdl_p.x == sdl_p2->x);
    REQUIRE(sdl_p.y == sdl_p2->y);
  }
}