#ifndef SDL2_CXX_NET_UDP_HXX
#define SDL2_CXX_NET_UDP_HXX

#include <SDL_net.h>

#include <sdl2_cxx/detail/interfaces.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>

#include <sdl2_cxx/net/core.hxx>
#include <sdl2_cxx/time/timer.hxx>

#include <iostream>

namespace sdl2
{
  namespace net
  {

    namespace udp
    {
      class packet final : ::sdl2::detail::noncopyable
      {
      public:
        explicit packet(int size) : m_packet(SDLNet_AllocPacket(size))
        {
          SDL2_CXX_NET_CHECK(m_packet != nullptr);
          m_packet->len = 0;
          m_packet->channel = -1;
        }
        packet(packet&& other) : m_packet(std::move(other.m_packet)) {}

        packet& operator=(packet&& other)
        {
          packet(std::move(other)).swap(*this);
          return *this;
        }

        inline void resize(int new_size)
        {
          auto result = SDLNet_ResizePacket(m_packet.get(), new_size);
          SDL2_CXX_NET_CHECK(result == new_size);
        }

        inline void address(const ip_address& ip)
        {
          m_packet->address.host = ip.host();
          m_packet->address.port = ip.port();
        }

        inline ip_address address() const noexcept { return ip_address(m_packet->address); }

        inline void set_data(const std::string& msg, bool auto_resize = false)
        {
          set_data((const std::uint8_t*)msg.c_str(), static_cast<int>(msg.length()), auto_resize);
        }

        inline void set_data(const std::uint8_t* data, int len, bool auto_resize = false)
        {
          if (auto_resize && (len > capacity()))
          {
            auto new_size = std::pow(2, std::ceil(std::log(len) / std::log(2)));
            resize(new_size);
          }

          std::copy(data, data + len, m_packet->data);
          m_packet->len = len;
        }

        inline const std::uint8_t* data() const noexcept { return m_packet->data; }

        inline void channel(int id) { m_packet->channel = id; }
        inline int channel() const noexcept { return m_packet->channel; }

        inline bool empty() const noexcept { return length() == 0; }
        inline int length() const noexcept { return m_packet->len; }
        inline int capacity() const noexcept { return m_packet->maxlen; }

        inline void swap(packet& other)
        {
          using std::swap;
          swap(m_packet, other.m_packet);
        }

      private:
        detail::sdl_ptr<UDPpacket, SDLNet_FreePacket> m_packet = nullptr;

        friend UDPpacket* to_sdl_type(const packet&) noexcept;
      };

      inline UDPpacket* to_sdl_type(const packet& p) noexcept { return p.m_packet.get(); }

      namespace detail
      {
        template <typename Derived>
        struct socket_api
        {

          inline void send(packet& p) { send(-1, p); }
          inline void send(int channel, packet& p) { SDL2_CXX_NET_CHECK(SDLNet_UDP_Send(to_sdl_type(*this), channel, to_sdl_type(p)) == 1); }

          inline packet receive(int size = 512)
          {
            packet p(size);
            receive(p);
            return p;
          }

          inline bool receive(packet& p)
          {
            auto received = SDLNet_UDP_Recv(to_sdl_type(*this), to_sdl_type(p));
            SDL2_CXX_NET_CHECK(received != -1);
            return (received == 1);
          }

          friend UDPsocket to_sdl_type(socket_api& self) { return to_sdl_type(static_cast<Derived&>(self)); }
          friend const UDPsocket& to_sdl_type(const socket_api& self) { return to_sdl_type(static_cast<const Derived&>(self)); }

        protected:
          virtual ~socket_api() = default;
        };

      } // namespace detail

      class socket final : public detail::socket_api<socket>, ::sdl2::detail::noncopyable
      {
      public:
        explicit socket(UDPsocket& socket) : m_socket(socket) { SDL2_CXX_NET_CHECK(m_socket != nullptr); }
        explicit socket(std::uint16_t port) : m_socket(SDLNet_UDP_Open(port)) { SDL2_CXX_NET_CHECK(m_socket != nullptr); }
        ~socket() noexcept { SDLNet_UDP_Close(m_socket); }

        socket(socket&& s) noexcept : m_socket(std::move(s.m_socket)) { s.m_socket = nullptr; }
        socket& operator=(socket&& s) noexcept
        {
          socket(std::move(s)).swap(*this);
          return *this;
        }

        void swap(socket& s) noexcept
        {
          auto tmp = s.m_socket;
          s.m_socket = m_socket;
          m_socket = tmp;
        }

      private:
        UDPsocket m_socket;

        friend UDPsocket to_sdl_type(socket&);
        friend const UDPsocket& to_sdl_type(const socket&);
      };

      inline UDPsocket to_sdl_type(socket& s) { return s.m_socket; }
      inline const UDPsocket& to_sdl_type(const socket& s) { return s.m_socket; }
    } // namespace udp

  } // namespace net
} // namespace sdl2

#endif /*SDL2_CXX_NET_UDP_HXX*/