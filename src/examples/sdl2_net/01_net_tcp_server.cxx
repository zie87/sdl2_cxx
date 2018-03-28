#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/time/timer.hxx>

#include <sdl2_cxx/net/core.hxx>
#include <sdl2_cxx/net/tcp.hxx>

#include <iostream>

int main(int argc, char** argv)
{
  using namespace std::chrono_literals;

  /* check our commandline */
  if (argc < 2)
  {
    std::cerr << "usage: " << argv[0] << " port" << std::endl;
    exit(0);
  }

  /* initialize SDL */
  sdl2::init_guard guard{};

  /* initialize SDL_net */
  sdl2::net::init_guard net_guard{};

  /* get the port from the commandline */
  std::uint16_t port = std::stoi(argv[1]);

  auto ip = sdl2::net::resolve_host(port);
  std::cout << "ip address: " << ip << std::endl;

  sdl2::net::tcp::socket server(ip);
  while (true)
  {
    /* try to accept a connection */
    auto client_optional = server.wait_for_accept(100, 100ms);
    if (!client_optional)
    {
      std::cerr << "no client connected in time" << std::endl;
      return -1;
    }

    auto client = std::move(client_optional.value());

    /* get the clients IP and port number */
    std::cout << "Accepted a connection from " << client.get_peer_address() << std::endl;

    /* read the buffer from client */
    constexpr unsigned int buffer_size = 1024;
    char buffer[buffer_size];
    auto len = client.receive(buffer, buffer_size);

    std::string message(buffer, len);
    std::cout << "Received: " << message << std::endl;

    if (message == "Q")
    {
      std::cout << "Quitting, because quit message received" << std::endl;
      break;
    }
  }

  return (0);
}