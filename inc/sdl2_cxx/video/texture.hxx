/**
* @file   texture.hxx
* @Author: zie87
* @Date:   2017-10-19 05:16:26
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-19 06:11:19
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_TEXTURE_HXX
#define SDL2_CXX_VIDEO_TEXTURE_HXX

#include <SDL_render.h>

#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>
#include <sdl2_cxx/detail/interfaces.hxx>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/core/stdinc.hxx>

#include <sdl2_cxx/video/surface.hxx>
#include <sdl2_cxx/video/render.hxx>
#include <sdl2_cxx/video/pixels.hxx>

namespace sdl2
{
  enum class texture_access : std::underlying_type_t<SDL_TextureAccess> 
  {
      static_access = SDL_TEXTUREACCESS_STATIC, /**< Changes rarely, not lockable */
      streaming     = SDL_TEXTUREACCESS_STREAMING, /**< Changes frequently, lockable */
      target        = SDL_TEXTUREACCESS_TARGET, /**< Texture can be used as a render target */
  };

  namespace detail 
  {
    template <typename Derived>
    struct texture_api 
    {
      void query_dimension( int& w, int& h) const { SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), NULL, NULL, &w, &h) >= 0 ) ); }
      pixel_format_type query_format() const 
      {
        uint32_t format = SDL_PIXELFORMAT_UNKNOWN;
        SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), &format, NULL, NULL, NULL) >= 0 ) );
        return static_cast<pixel_format_type>(format);
      }

      texture_access query_access() const
      {
        int access = -1;
        SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), NULL, &access, NULL, NULL) >= 0 ) );
        return static_cast<texture_access>(access);
      }

      void query( pixel_format_type& format, texture_access& access, int& w, int& h) const
      {
        uint32_t f = SDL_PIXELFORMAT_UNKNOWN;
        int a = -1;
        SDL2_CXX_CHECK( (SDL_QueryTexture(to_sdl_type(*this), &f, &a, &w, &h) >= 0 ) );
        format = static_cast<pixel_format_type>(f);
        access = static_cast<texture_access>(a);
      }

      explicit operator bool() const noexcept { return to_sdl_type(*this) != nullptr; }

      friend SDL_Texture* to_sdl_type(const texture_api& self) noexcept { return to_sdl_type(static_cast<const Derived&>(self)); }

      protected:
        virtual ~texture_api() = default;
    };
  } // namespace detail

  class texture final : public detail::texture_api<texture>, detail::noncopyable
  {
    public:
      explicit texture(const renderer& rend, const surface& s) 
      : detail::texture_api<texture>(), detail::noncopyable()
      , m_texture( SDL_CreateTextureFromSurface(to_sdl_type(rend), to_sdl_type(s)) )
      { SDL2_CXX_CHECK( m_texture != nullptr );}

      texture(texture&& w): m_texture(std::move(w.m_texture)) {}
      texture& operator=(texture&& w) { m_texture = std::move(w.m_texture); return *this; }

      private:
        detail::sdl_ptr<SDL_Texture, SDL_DestroyTexture> m_texture = nullptr;
        friend SDL_Texture* to_sdl_type(const texture&) noexcept;
    };

    inline SDL_Texture* to_sdl_type(const texture& w) noexcept { return w.m_texture.get(); }
}

#endif