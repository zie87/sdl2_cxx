#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/net/udp.hxx>

#include <catch.hpp>

#include <iostream>

TEST_CASE("test udp wrapper for sdl2_net", "[net]")
{
  sdl2::init_guard sdl2_guard{};

  SECTION("test package resizing")
  {
    sdl2::net::udp::packet packet(16);
    REQUIRE(packet.capacity() == 16);

    const std::string test_data("this is a string which should init resizing");

    packet.set_data(test_data, true);
    REQUIRE(packet.length() == test_data.length());
    REQUIRE(packet.capacity() == 64);
  }

  SECTION("test package sending")
  {
    sdl2::net::init_guard net_guard{};
    constexpr std::uint16_t port = 1234;
    const std::string hostname("localhost");

    const std::string test_message("this is a test message");

    sdl2::net::udp::socket socket(port);
    auto server_ip = sdl2::net::resolve_host(hostname, port);

    sdl2::net::udp::packet out_packet(512);
    out_packet.address(server_ip);
    out_packet.set_data(test_message);

    socket.send(out_packet);

    auto in_packet = socket.receive();
    std::string in_msg((const char*)in_packet.data(), in_packet.length());

    REQUIRE_THAT(in_msg, Catch::Matchers::Equals(test_message));
  }
}