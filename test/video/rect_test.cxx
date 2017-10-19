/**
* @file   rect_test.cxx
* @Author: zie87
* @Date:   2017-10-19 04:50:55
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-19 05:04:38
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/video/rect.hxx>

#include <catch.hpp>

TEST_CASE("check rectangle wrapper", "[video]") 
{
  SECTION("rectangle construction test") 
  {
    // default values
    sdl2::rect r1;
    REQUIRE( 0 == r1.x() );
    REQUIRE( 0 == r1.y() );
    REQUIRE( 0 == r1.width() );
    REQUIRE( 0 == r1.height() );

    // value construction
    sdl2::rect r2(1, 2, 3, 4 );
    REQUIRE( 1 == r2.x() );
    REQUIRE( 2 == r2.y() );
    REQUIRE( 3 == r2.width() );
    REQUIRE( 4 == r2.height() );

    // copy construction
    sdl2::rect r3(r2);
    REQUIRE( 1 == r3.x() );
    REQUIRE( 2 == r3.y() );
    REQUIRE( 3 == r3.width() );
    REQUIRE( 4 == r3.height() );
  }

  SECTION("rectangle assignment test") 
  {
    sdl2::rect r1(1, 2, 3, 4 );
    sdl2::rect r2(5, 6, 7, 8 );
    REQUIRE( r1 != r2 );

    // assignment operator
    r1 = r2;
    REQUIRE( r1 == r2 );

    // element setter
    r1.x() = 10;
    r1.y() = 20;
    r1.width() = 30;
    r1.height() = 40;

    REQUIRE( 10 == r1.x() );
    REQUIRE( 20 == r1.y() );
    REQUIRE( 30 == r1.width() );
    REQUIRE( 40 == r1.height() );

    r1.set_coordinates(-1, -2);
    r1.set_dimension(-3, -4);
    r2.set(-1, -2, -3, -4);

    REQUIRE(r1 == r2);
  }

  SECTION("rectangle area test") 
  {
    sdl2::rect r1;
    REQUIRE(r1.empty());

    sdl2::point p1(10,10);
    REQUIRE( !r1.point_in(p1) );

    r1.set_dimension(100, 100);
    REQUIRE(!r1.empty());
    REQUIRE(r1.point_in(p1));

    sdl2::rect r2( 200, 90, 50, 50 );
    REQUIRE(!r1.has_intersection(r2));
    sdl2::rect r3 = r1.intersection_rectangle(r2);
    REQUIRE(r3.empty());

    r2.x() = 0;
    REQUIRE(r1.has_intersection(r2));

    r3 = r1.intersection_rectangle(r2);
    REQUIRE(  0 == r3.x() );
    REQUIRE( 90 == r3.y() );
    REQUIRE( 50 == r3.width() );
    REQUIRE( 10 == r3.height() );

    r3 = r1.union_rectangel(r2);
    REQUIRE(   0 == r3.x() );
    REQUIRE(   0 == r3.y() );
    REQUIRE( 100 == r3.width() );
    REQUIRE( 140 == r3.height() );

    int x1 = 10;
    int y1 = 10;
    int x2 = 200;
    int y2 = 200;
    REQUIRE( r1.intersection_line(x1, y1, x2, y2) );
    REQUIRE(x2 == y2);
    REQUIRE(99 == x2);

    sdl2::point start( 0, 200 );
    sdl2::point end( 400, 0);
    REQUIRE( !r1.intersection_line(start, end) );

    end.x() = 150;
    REQUIRE( r1.intersection_line(start, end) );
    REQUIRE(75 == start.x());
    REQUIRE(99 == start.y());
    REQUIRE(99 == end.x());
    REQUIRE(68 == end.y());
  }

  SECTION("rectangle converter test") 
  {
    SDL_Rect sdl_r{-1 , -2, -3, 4};
    sdl2::rect r1(-1, -2, -3, 4);

    // raw pointer access
    SDL_Rect* sdl_r1 = sdl2::to_sdl_type(r1);
    REQUIRE(SDL_TRUE == SDL_RectEquals(&sdl_r, sdl_r1) );

    sdl_r1->x = 1;
    sdl_r1->y = 2;
    sdl_r1->w = 3;
    sdl_r1->h = 4;

    REQUIRE( 1 == r1.x() );
    REQUIRE( 2 == r1.y() );
    REQUIRE( 3 == r1.width() );
    REQUIRE( 4 == r1.height() );

    // const access to raw pointer
    const sdl2::rect r2( r1 );
    const SDL_Rect* sdl_r2 = sdl2::to_sdl_type(r2);
    REQUIRE( 1 == sdl_r2->x );
    REQUIRE( 2 == sdl_r2->y );
    REQUIRE( 3 == sdl_r2->w );
    REQUIRE( 4 == sdl_r2->h );
  }

}