/**
* @file   window_test.cxx
* @Author: zie87
* @Date:   2017-10-17 05:07:32
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-17 06:35:44
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/video/window.hxx>

#include "SDL.h"
#include <catch.hpp>

TEST_CASE("check window wrapper", "[video]") 
{
  SDL_VideoInit(NULL);

  SECTION("Basic construction test") 
  {
    const std::string title("construction test test");
    const int x = 10;
    const int y = 20;
    const int w = 120;
    const int h = 80;

    {
      sdl2::window window(title, x, y, w, h);
      SDL_Window* sdl_win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);

      REQUIRE( title == SDL_GetWindowTitle( sdl2::to_sdl_type(window) ) );
      REQUIRE( SDL_GetWindowFlags(sdl_win) == SDL_GetWindowFlags(sdl2::to_sdl_type(window)));

      int w_x = -1;
      int w_y = -1;

      SDL_GetWindowPosition(sdl2::to_sdl_type(window), &w_x, &w_y);
      REQUIRE(x == w_x);
      REQUIRE(y == w_y);

      int w_w = -1;
      int w_h = -1;
      SDL_GetWindowSize(sdl2::to_sdl_type(window), &w_w, &w_h);
      REQUIRE(w == w_w);
      REQUIRE(h == w_h);

      SDL_DestroyWindow(sdl_win);
    }

    {
      sdl2::window window(title, w, h, sdl2::window_flags::hidden);
      SDL_Window* sdl_win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_HIDDEN);

      REQUIRE( title == SDL_GetWindowTitle( sdl2::to_sdl_type(window) ) );
      REQUIRE( SDL_GetWindowFlags(sdl_win) == SDL_GetWindowFlags(sdl2::to_sdl_type(window)));

      int w_x = -1;
      int w_y = -1;

      SDL_GetWindowPosition(sdl2::to_sdl_type(window), &w_x, &w_y);
      REQUIRE(w_x >= 0);
      REQUIRE(w_y >= 0);

      int w_w = -1;
      int w_h = -1;
      SDL_GetWindowSize(sdl2::to_sdl_type(window), &w_w, &w_h);
      REQUIRE(w == w_w);
      REQUIRE(h == w_h);

      SDL_DestroyWindow(sdl_win);
    }
  }

  SDL_VideoQuit();
}