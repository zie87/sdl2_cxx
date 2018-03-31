/**
 * @file   window_test.cxx
 * @Author: zie87
 * @Date:   2017-10-17 05:07:32
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-23 18:55:44
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
  SDL_VideoInit(nullptr);

  SECTION("basic construction test")
  {
    const std::string title("construction test test");
    const int x = 10;
    const int y = 20;
    const int w = 120;
    const int h = 80;

    // test move
    {
      sdl2::window window(title, sdl2::windowpos::undefined, sdl2::windowpos::centered, w, h);
      REQUIRE(window);

      sdl2::window move_win(std::move(window));
      REQUIRE(move_win);

      window = std::move(move_win);
      REQUIRE(window);
    }

    {
      SDL_Window* sdl_win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
      auto sdl_flags = SDL_GetWindowFlags(sdl_win);
      int sdl_w = -1;
      int sdl_h = -1;
      SDL_GetWindowSize(sdl_win, &sdl_w, &sdl_h);
      SDL_DestroyWindow(sdl_win);

      sdl2::window window(title, x, y, w, h);

      REQUIRE(title == SDL_GetWindowTitle(sdl2::to_sdl_type(window)));
      REQUIRE(sdl_flags == SDL_GetWindowFlags(sdl2::to_sdl_type(window)));
      REQUIRE(sdl_flags == window.get_flags());

      int w_x = -1;
      int w_y = -1;

      SDL_GetWindowPosition(sdl2::to_sdl_type(window), &w_x, &w_y);
      REQUIRE(x == w_x);
      REQUIRE(y == w_y);

      int w_w = -1;
      int w_h = -1;
      SDL_GetWindowSize(sdl2::to_sdl_type(window), &w_w, &w_h);
      REQUIRE(sdl_w == w_w);
      REQUIRE(sdl_h == w_h);
    }

    {
      SDL_Window* sdl_win = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_HIDDEN);
      auto sdl_flags = SDL_GetWindowFlags(sdl_win);
      int sdl_w = -1;
      int sdl_h = -1;
      SDL_GetWindowSize(sdl_win, &sdl_w, &sdl_h);
      SDL_DestroyWindow(sdl_win);

      sdl2::window window(title, w, h, sdl2::window_flags::hidden);

      REQUIRE(title == SDL_GetWindowTitle(sdl2::to_sdl_type(window)));
      REQUIRE(sdl_flags == SDL_GetWindowFlags(sdl2::to_sdl_type(window)));
      REQUIRE(sdl_flags == window.get_flags());

      int w_x = -1;
      int w_y = -1;

      SDL_GetWindowPosition(sdl2::to_sdl_type(window), &w_x, &w_y);
      REQUIRE(w_x >= 0);
      REQUIRE(w_y >= 0);

      int w_w = -1;
      int w_h = -1;
      SDL_GetWindowSize(sdl2::to_sdl_type(window), &w_w, &w_h);
      REQUIRE(sdl_w == w_w);
      REQUIRE(sdl_h == w_h);
    }

    {
      SDL_Window* sdl_win = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
      auto sdl_flags = SDL_GetWindowFlags(sdl_win);
      int sdl_w = -1;
      int sdl_h = -1;
      SDL_GetWindowSize(sdl_win, &sdl_w, &sdl_h);
      int sdl_x = -1;
      int sdl_y = -1;

      SDL_GetWindowPosition(sdl_win, &sdl_x, &sdl_y);

      SDL_DestroyWindow(sdl_win);

      sdl2::window window(title, x, y, w, h, {sdl2::window_flags::shown, sdl2::window_flags::maximized});

      REQUIRE(title == SDL_GetWindowTitle(sdl2::to_sdl_type(window)));
      REQUIRE(sdl_flags == SDL_GetWindowFlags(sdl2::to_sdl_type(window)));
      REQUIRE(sdl_flags == window.get_flags());

      int w_x = -1;
      int w_y = -1;

      SDL_GetWindowPosition(sdl2::to_sdl_type(window), &w_x, &w_y);
      REQUIRE(sdl_x == w_x);
      REQUIRE(sdl_y == w_y);

      int w_w = -1;
      int w_h = -1;
      SDL_GetWindowSize(sdl2::to_sdl_type(window), &w_w, &w_h);
      REQUIRE(sdl_w == w_w);
      REQUIRE(sdl_h == w_h);
    }
  }

  SECTION("screen test")
  {
    try
    {
      auto window = sdl2::window("SDL Tutorial", sdl2::windowpos::undefined, sdl2::windowpos::undefined, 640, 480, sdl2::window_flags::shown);
      REQUIRE(window);

      auto screen = window.get_surface();
      REQUIRE(screen);

      screen.fill(0xFF, 0xFF, 0xFF);
      window.update_surface();
    }
    catch (...)
    {
      REQUIRE(false);
    }
  }

  SDL_VideoQuit();
}