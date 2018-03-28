#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/net/core.hxx>
#include <sdl2_cxx/net/tcp.hxx>

#include <iostream>

int main(int argc, char** argv)
{
  /* check our commandline */
  if (argc < 3)
  {
    std::cerr << "usage: " << argv[0] << " host port" << std::endl;
    exit(0);
  }

  /* initialize SDL */
  sdl2::init_guard guard{};
  /* initialize SDL_net */
  sdl2::net::init_guard net_guard{};

  /* get the port from the commandline */
  std::uint16_t port = std::stoi(argv[2]);

  auto ip = sdl2::net::resolve_host(argv[1], port);
  std::cout << "ip address: " << ip << std::endl;

  /* open the server socket */
  sdl2::net::tcp::socket sock(ip);

  /* read the buffer from stdin */
  std::string message;
  std::cout << "Enter Message, or Q to make the server quit:" << std::endl;
  std::cin >> message;

  if (!message.empty())
  {
    std::cout << "Sending: " << message << std::endl;
    sock.send(message);
  }

  return (0);
}