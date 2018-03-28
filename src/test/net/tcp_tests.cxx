#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/net/tcp.hxx>

#include <catch.hpp>

#include <memory>
#include <mutex>
#include <thread>

class test_tcp_server
{
public:
  test_tcp_server(std::uint16_t port) : m_address(sdl2::net::resolve_host(port)), m_messages(), m_mutex() {}

  void run()
  {
    std::unique_lock<std::mutex> locker(m_mutex);
    using namespace std::chrono_literals;
    sdl2::net::tcp::socket server(m_address);

    auto client_optional = server.wait_for_accept(100, 5ms);
    if (!client_optional)
    {
      return;
    }

    auto client = std::move(client_optional.value());

    /* read the buffer from client */
    constexpr unsigned int buffer_size = 1024;
    char buffer[buffer_size];
    auto len = client.receive(buffer, buffer_size);

    std::string message(buffer, len);

    if (!message.empty())
    {
      m_messages.push_back(message);
    }
  }

  std::vector<std::string> messages() const noexcept
  {
    std::unique_lock<std::mutex> locker(m_mutex);
    return m_messages;
  }

private:
  sdl2::net::ip_address m_address;
  std::vector<std::string> m_messages;
  mutable std::mutex m_mutex;
};

TEST_CASE("test tcp wrapper for sdl2_net", "[net]")
{
  using thread_ptr = std::unique_ptr<std::thread>;
  using namespace std::chrono_literals;

  sdl2::init_guard sdl2_guard{};
  SECTION("test initialization")
  {
    constexpr std::uint16_t port = 8000;
    sdl2::net::ip_address ip_address{};
    REQUIRE(ip_address.host() == 0);
    REQUIRE(ip_address.port() == 0);

    sdl2::net::init_guard net_guard{};
    ip_address = sdl2::net::resolve_host(port);
    REQUIRE(ip_address.port() != 0);
  }

  SECTION("test connection")
  {
    sdl2::net::init_guard net_guard{};
    constexpr std::uint16_t port = 1234;
    const std::string hostname("localhost");
    test_tcp_server server(port);

    const std::string test_message("test_message");
    auto server_thread = thread_ptr(new std::thread(std::bind(&test_tcp_server::run, &server)));

    auto client_ip = sdl2::net::resolve_host(hostname, port);
    sdl2::net::tcp::socket client(client_ip);

    sdl2::delay(10ms);
    client.send(test_message);
    sdl2::delay(10ms);

    if (server_thread->joinable())
    {
      server_thread->join();
    }

    auto messages = server.messages();
    REQUIRE(messages.size() == 1);
    REQUIRE(messages.at(0) == test_message);
  }

  SECTION("test unsuccessfully client connection")
  {
    sdl2::net::init_guard net_guard{};
    constexpr std::uint16_t port = 1243;
    const std::string hostname("localhost");

    try
    {
      auto client_ip = sdl2::net::resolve_host(hostname, port);
      sdl2::net::tcp::socket client(client_ip);
      REQUIRE(false);
    }
    catch (sdl2::net_exception& e)
    {
      REQUIRE_THAT(e.what(), Catch::Matchers::Equals("Couldn't connect to remote host"));
    }
  }
}