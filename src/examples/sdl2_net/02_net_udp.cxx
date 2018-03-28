#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/net/core.hxx>
#include <sdl2_cxx/net/udp.hxx>

#include <iostream>
#include <sstream>

struct udp_connection
{
  explicit udp_connection(std::uint16_t port) : m_quit(false), m_socket(port) {}
  ~udp_connection() noexcept = default;

  void set_ip_and_port(const std::string& ip, uint16_t port)
  {
    std::cout << "Setting IP ( " << ip << " ) "
              << "and port ( " << port << " )\n";

    m_server_ip = sdl2::net::resolve_host(ip, port);
    std::cout << "\tSuccess!\n\n";
  }

  // send_message data.
  bool send_message()
  {
    std::cout << "Type a message and hit enter (quit to leave)\n";
    std::string msg = "";
    std::cin.ignore();
    std::getline(std::cin, msg);

    sdl2::net::udp::packet packet(512);
    packet.address(m_server_ip);

    packet.set_data(msg);

    std::cout << "==========================================================================================================\n"
              << "Sending : \'" << msg << "\', Length : " << sdl2::net::udp::to_sdl_type(packet)->len << "\n";

    m_socket.send(packet);
    std::cout << "\tSuccess!\n"
              << "==========================================================================================================\n";

    if (msg == "quit") m_quit = true;
    return true;
  }

  void check_for_package()
  {
    std::cout << "==========================================================================================================\n"
              << "Check for data...\n";

    auto packet = m_socket.receive();
    // Check t see if there is a packet wauting for us...
    if (!packet.empty())
    {
      std::string msg((const char*)packet.data(), packet.length());
      std::cout << "\tData received : " << msg << std::endl;

      // If the data is "quit"
      if (msg == "quit") m_quit = true;
    }
    else
      std::cout << "\tNo data received!\n";

    std::cout << "==========================================================================================================\n";
  }
  bool quit() { return m_quit; }

private:
  bool m_quit;
  sdl2::net::udp::socket m_socket;
  sdl2::net::ip_address m_server_ip;
};

int main(int argc, char** argv)
{
  sdl2::init_guard sdl2_guard{};
  sdl2::net::init_guard net_guard{};

  std::string IP;
  int32_t localPort = 0;
  int32_t remotePort = 0;

  std::cout << "\n==========================================================================================================\n"
            << "UDP connection - A simple test for UDP connections using SDL_Net!"
            << "\n==========================================================================================================\n"
            << "You'll be asked to enter the following :"
            << "\n\tRemote IP   : The IP you want to connect to"
            << "\n\tRemote Port : The port you want to connect to"
            << "\n\tLocal port  : Uour port"
            << "\nLocal port should be the same as remote port on the other instance of the application"
            << "\n==========================================================================================================\n\n";

  std::cout << "Enter remote IP ( 127.0.0.1  for local connections ) : ";
  std::cin >> IP;
  std::cout << "...and remote port : ";
  std::cin >> remotePort;

  std::cout << "Enter local port : ";
  std::cin >> localPort;

  udp_connection connection(localPort);
  connection.set_ip_and_port(IP, remotePort);

  uint8_t command = 0;

  while (!connection.quit())
  {
    std::cout << "Your command : "
              << "\n\t0 : send_message a message"
              << "\n\t1 : Check for data" << std::endl;

    std::cin >> command;

    if (command == '0')
      connection.send_message();
    else if (command == '1')
      connection.check_for_package();
    else
      std::cout << "Illegal command\n";
  }
}