/**
 * @file   timer_test.cxx
 * @Author: zie87
 * @Date:   2017-10-15 00:05:38
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-15 00:09:49
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#include <sdl2_cxx/time/timer.hxx>

#include "SDL.h"
#include <catch.hpp>

using namespace std::chrono_literals;

TEST_CASE("check timer wrapper", "[time]")
{
  SDL_Init(SDL_INIT_TIMER);

  SECTION("clock functionality")
  {
    auto t1 = SDL_GetTicks();
    auto t2 = sdl2::clock::now();

    REQUIRE(t1 <= t2.time_since_epoch().count());
    REQUIRE(sdl2::duration(t1) <= t2.time_since_epoch());
  }

  SECTION("global timer functions")
  {
    auto c1 = SDL_GetPerformanceCounter();
    auto c2 = sdl2::performance_counter();
    REQUIRE(c1 <= c2);

    REQUIRE(sdl2::performance_frequency() == SDL_GetPerformanceFrequency());
  }

  SECTION("delay functionality")
  {
    auto t1 = SDL_GetTicks();
    sdl2::delay(25ms);
    auto t2 = SDL_GetTicks();

    REQUIRE(t2 >= t1 + 25);
  }

  SDL_Quit();
}