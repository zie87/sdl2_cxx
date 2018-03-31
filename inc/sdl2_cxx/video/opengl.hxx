#ifndef SDL2_CXX_VIDEO_OPENGL_HXX
#define SDL2_CXX_VIDEO_OPENGL_HXX

#include <sdl2_cxx/video/window.hxx>

namespace sdl2
{
  namespace gl
  {
    enum class swap_interval : int
    {
      immediate = 0,
      synchronized = 1,
      allow_late = -1
    };

    enum class attribute : std::underlying_type_t<SDL_GLattr>
    {
      red_size = SDL_GL_RED_SIZE,
      green_size = SDL_GL_GREEN_SIZE,
      blue_size = SDL_GL_BLUE_SIZE,
      alpha_size = SDL_GL_ALPHA_SIZE,
      buffer_size = SDL_GL_BUFFER_SIZE,
      doublebuffer = SDL_GL_DOUBLEBUFFER,
      depth_size = SDL_GL_DEPTH_SIZE,
      stencil_size = SDL_GL_STENCIL_SIZE,
      accum_red_size = SDL_GL_ACCUM_RED_SIZE,
      accum_green_size = SDL_GL_ACCUM_GREEN_SIZE,
      accum_blue_size = SDL_GL_ACCUM_BLUE_SIZE,
      accum_alpha_size = SDL_GL_ACCUM_ALPHA_SIZE,
      stereo = SDL_GL_STEREO,
      multisamplebuffers = SDL_GL_MULTISAMPLEBUFFERS,
      multisamplesamples = SDL_GL_MULTISAMPLESAMPLES,
      accelerated_visual = SDL_GL_ACCELERATED_VISUAL,
      context_major_version = SDL_GL_CONTEXT_MAJOR_VERSION,
      context_minor_version = SDL_GL_CONTEXT_MINOR_VERSION,
      context_flags = SDL_GL_CONTEXT_FLAGS,
      context_profile_mask = SDL_GL_CONTEXT_PROFILE_MASK,
      share_with_current_context = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
      framebuffer_srgb_capable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
      release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR
    };

    class context final
    {
    public:
      explicit context(window& win) : m_gl_context(SDL_GL_CreateContext(to_sdl_type(win))) { SDL2_CXX_CHECK(m_gl_context != nullptr); }

      explicit operator bool() const { return m_gl_context != nullptr; }

    private:
      detail::sdl_ptr<void, SDL_GL_DeleteContext> m_gl_context = nullptr;
      friend SDL_GLContext to_sdl_type(const context&) noexcept;
    };

    inline SDL_GLContext to_sdl_type(const context& c) noexcept { return c.m_gl_context.get(); }

    inline void make_current(window& w, context& c) { SDL2_CXX_CHECK(SDL_GL_MakeCurrent(to_sdl_type(w), to_sdl_type(c)) == 0); }
    inline void swap_window(window& w) { SDL_GL_SwapWindow(to_sdl_type(w)); }

    inline bool set_swap_interval(swap_interval interval)
    {
      return (SDL_GL_SetSwapInterval(static_cast<std::underlying_type_t<swap_interval>>(interval)) == 0);
    }

    inline swap_interval get_swap_interval() noexcept { return static_cast<swap_interval>(SDL_GL_GetSwapInterval()); }

    inline void set_attribute(attribute attr, int value) { SDL2_CXX_CHECK(SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value) == 0); }
    inline int get_attribute(attribute attr)
    {
      int value = 0;
      SDL2_CXX_CHECK(SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attr), &value) == 0);
      return value;
    }

  } // namespace gl
} // namespace sdl2

#endif /*SDL2_CXX_VIDEO_OPENGL_HXX*/