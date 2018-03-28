#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/net/udp.hxx>

#include <catch.hpp>

#include <memory>
#include <thread>

TEST_CASE("test udp wrapper for sdl2_net", "[net]")
{
  using thread_ptr = std::unique_ptr<std::thread>;
  using namespace std::chrono_literals;

  sdl2::init_guard sdl2_guard{};
}