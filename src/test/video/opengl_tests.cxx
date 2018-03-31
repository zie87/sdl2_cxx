#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/video/opengl.hxx>

#include <catch.hpp>
#include <iostream>

TEST_CASE("check opengl wrapper", "[video]")
{
  sdl2::init_guard sdl2_guard{sdl2::init_flags::everything};
  constexpr int screen_width = 640;
  constexpr int screen_height = 480;

  SECTION("test interval setting")
  {
    sdl2::window window{"interval tests", sdl2::windowpos::centered, sdl2::windowpos::centered, screen_width, screen_height, sdl2::window_flags::opengl};
    auto context = sdl2::gl::context(window);
    sdl2::gl::make_current(window, context);
    sdl2::gl::swap_window(window);

    // SWAP interval isn't support inside of the VM

    // REQUIRE(SDL_GL_SetSwapInterval(1) == 0);

    // auto interval = sdl2::gl::get_swap_interval();
    // int int_interval = static_cast<std::underlying_type_t<sdl2::gl::swap_interval>>(interval);
    // REQUIRE(int_interval == SDL_GL_GetSwapInterval());
  }
}