#ifndef SDL2_CXX_NET_TCP_HXX
#define SDL2_CXX_NET_TCP_HXX

#include <SDL_net.h>

#include <sdl2_cxx/detail/interfaces.hxx>
#include <sdl2_cxx/net/core.hxx>
#include <sdl2_cxx/time/timer.hxx>

#include <optional>

namespace sdl2
{
  namespace net
  {

    namespace tcp
    {

      namespace detail
      {
        template <typename Derived>
        struct socket_api
        {
          inline void send(const void* data, int length) { SDL2_CXX_NET_CHECK(SDLNet_TCP_Send(to_sdl_type(*this), data, length) == length); }
          inline void send(const std::string& message)
          {
            if (message.empty())
            {
              return;
            }

            send((const void*)message.c_str(), message.length());
          }

          inline int receive(void* data, int length)
          {
            int len = SDLNet_TCP_Recv(to_sdl_type(*this), data, length);
            SDL2_CXX_NET_CHECK(len > 0);
            return len;
          }

          inline std::optional<Derived> accept() noexcept
          {
            TCPsocket socket = SDLNet_TCP_Accept(to_sdl_type(*this));
            if (socket == nullptr) return std::optional<Derived>();
            return std::optional<Derived>(socket);
          }

          inline std::optional<Derived> wait_for_accept(unsigned int number_of_retries, uint32_t delay) noexcept
          {
            unsigned int count = 0;
            auto socket = accept();
            while (!socket)
            {
              sdl2::delay(delay);
              socket = accept();
              if (++count > number_of_retries) break;
            }
            return socket;
          }

          inline std::optional<Derived> wait_for_accept(unsigned int number_of_retries, duration delay) noexcept
          {
            return wait_for_accept(number_of_retries, delay.count());
          }

          inline ip_address get_peer_address()
          {
            auto address = SDLNet_TCP_GetPeerAddress(to_sdl_type(*this));
            SDL2_CXX_NET_CHECK(address != nullptr);
            return ip_address(*address);
          }

          friend TCPsocket to_sdl_type(socket_api& self) { return to_sdl_type(static_cast<Derived&>(self)); }
          friend const TCPsocket& to_sdl_type(const socket_api& self) { return to_sdl_type(static_cast<const Derived&>(self)); }

        protected:
          virtual ~socket_api() = default;
        };

      } // namespace detail

      class socket final : public detail::socket_api<socket>, ::sdl2::detail::noncopyable
      {
      public:
        explicit socket(TCPsocket& socket) : m_socket(socket) { SDL2_CXX_NET_CHECK(m_socket != nullptr); }
        explicit socket(ip_address& address) : m_socket(SDLNet_TCP_Open(to_sdl_type(address))) { SDL2_CXX_NET_CHECK(m_socket != nullptr); }
        ~socket() noexcept { SDLNet_TCP_Close(m_socket); }

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
        TCPsocket m_socket;

        friend TCPsocket to_sdl_type(socket&);
        friend const TCPsocket& to_sdl_type(const socket&);
      };

      inline TCPsocket to_sdl_type(socket& s) { return s.m_socket; }
      inline const TCPsocket& to_sdl_type(const socket& s) { return s.m_socket; }

    } // tcp

  } // net
} // sdl2

#endif /*SDL2_CXX_NET_TCP_HXX*/