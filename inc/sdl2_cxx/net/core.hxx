#ifndef SDL2_CXX_NET_CORE_HXX
#define SDL2_CXX_NET_CORE_HXX

#include <SDL_net.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/platform/endian.hxx>

#include <ostream>

namespace sdl2
{
  class net_exception : public exception
  {
  public:
    static inline std::string last_error()
    {
      std::string result(SDLNet_GetError());
      SDL_ClearError();
      return result;
    }

    net_exception() : exception(last_error()) {}
    net_exception(const std::string& str) : exception(str) {}
    virtual ~net_exception() = default;
  };

#define SDL2_CXX_NET_CHECK(condition)                                                                                                                          \
  do                                                                                                                                                           \
  {                                                                                                                                                            \
    if (!(condition)) throw net_exception();                                                                                                                   \
  } while (SDL_NULL_WHILE_LOOP_CONDITION);

  namespace net
  {
    struct init_guard
    {
      explicit init_guard() { SDL2_CXX_NET_CHECK(::SDLNet_Init() != -1); }

      init_guard(init_guard&&) noexcept = default;
      init_guard& operator=(init_guard&&) noexcept = default;

      ~init_guard() { ::SDLNet_Quit(); }
    };

    class ip_address
    {
    public:
      using host_type = std::uint32_t;
      using port_type = std::uint16_t;

      ip_address() noexcept : m_address{0, 0} {}
      ip_address(const ip_address& address) noexcept : m_address(address.m_address) {}

      explicit ip_address(const IPaddress& address) noexcept : m_address{address.host, address.port} {}
      ~ip_address() = default;

      ip_address& operator=(ip_address r) noexcept
      {
        swap(*this, r);
        return *this;
      }

      inline host_type host() const noexcept { return m_address.host; }
      inline port_type port() const noexcept { return m_address.port; }

      friend void swap(ip_address& lhs, ip_address& rhs) noexcept
      {
        using std::swap;
        swap(lhs.m_address.host, rhs.m_address.host);
        swap(lhs.m_address.port, rhs.m_address.port);
      }

    private:
      IPaddress m_address;
      friend IPaddress* to_sdl_type(ip_address&);
      friend const IPaddress* to_sdl_type(const ip_address&);
    };

    inline IPaddress* to_sdl_type(ip_address& address) { return (&address.m_address); }
    inline const IPaddress* to_sdl_type(const ip_address& address) { return (&address.m_address); }

    inline ip_address resolve_host(std::uint16_t port)
    {
      IPaddress address;
      SDL2_CXX_NET_CHECK(SDLNet_ResolveHost(&address, nullptr, port) != -1);
      return ip_address(address);
    }

    inline ip_address resolve_host(const std::string& hostname, std::uint16_t port)
    {
      IPaddress address;
      SDL2_CXX_NET_CHECK(SDLNet_ResolveHost(&address, hostname.c_str(), port) != -1);
      return ip_address(address);
    }

    std::ostream& operator<<(std::ostream& stream, const ip_address& address)
    {
      auto ipaddr = SDL_SwapBE32(address.host());
      auto port = SDL_SwapBE16(address.port());

      stream << "host: " << (ipaddr >> 24) << "." << ((ipaddr >> 16) & 0xff) << "." << ((ipaddr >> 8) & 0xff) << "." << (ipaddr & 0xff) << " port: " << port;
      return stream;
    }

  } // namespace net
} // sdl2

#endif /*SDL2_CXX_NET_CORE_HXX*/