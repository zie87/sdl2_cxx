/**
 *  @file    window.hxx
 *  @author  zie87
 *  @date    2017-10-23 19:53:49
 *  @version 2017-10-24 05:38:20
 *
 *  @brief   Header file for window functionality
 *
 * This file manly wraps the window related content of `SDL_video.h`
 *
 **/

#ifndef SDL2_CXX_VIDEO_WINDOW_HXX
#define SDL2_CXX_VIDEO_WINDOW_HXX

#include <SDL_video.h>

#include <sdl2_cxx/detail/interfaces.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/video/surface.hxx>

namespace sdl2
{
  /**
   * @brief An enumeration of window states.
   * @details Flags passed to the `sdl2::window` constructor
   *
   * @sa `sdl2::window_api::get_flags`
   */
  enum class window_flags : std::underlying_type_t<SDL_WindowFlags>
  {
    none = 0,
    fullscreen = SDL_WINDOW_FULLSCREEN,                 /**< fullscreen window */
    opengl = SDL_WINDOW_OPENGL,                         /**< window usable with OpenGL context */
    shown = SDL_WINDOW_SHOWN,                           /**< window is visible */
    hidden = SDL_WINDOW_HIDDEN,                         /**< window is not visible */
    borderless = SDL_WINDOW_BORDERLESS,                 /**< no window decoration */
    resizable = SDL_WINDOW_RESIZABLE,                   /**< window can be resized */
    minimized = SDL_WINDOW_MINIMIZED,                   /**< window is minimized */
    maximized = SDL_WINDOW_MAXIMIZED,                   /**< window is maximized */
    input_grabbed = SDL_WINDOW_INPUT_GRABBED,           /**< window has grabbed input focus */
    input_focus = SDL_WINDOW_INPUT_FOCUS,               /**< window has input focus */
    mouse_focus = SDL_WINDOW_MOUSE_FOCUS,               /**< window has mouse focus */
    fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP, /**< window is fullscreen in desktop mode */
    foreign = SDL_WINDOW_FOREIGN,                       /**< window not created by SDL */
    allow_highdpi = SDL_WINDOW_ALLOW_HIGHDPI,           /**< window should be created in high-DPI mode if supported */
    mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,           /**< window has mouse captured (unrelated to INPUT_GRABBED) */
    always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,           /**< window should always be above others */
    skip_taskbar = SDL_WINDOW_SKIP_TASKBAR,             /**< window should not be added to the taskbar */
    utility = SDL_WINDOW_UTILITY,                       /**< window should be treated as a utility window */
    tooltip = SDL_WINDOW_TOOLTIP,                       /**< window should be treated as a tooltip */
    popup_menu = SDL_WINDOW_POPUP_MENU,                 /**< window should be treated as a popup menu */
    vulkan = SDL_WINDOW_VULKAN                          /**< window usable for Vulkan surface */
  };

  /**
   * help structur to enable or-operator on `sdl2::window_flags`
   */
  template <>
  struct enable_bitmask_operators<window_flags>
  {
    static const bool enable = true;
  };

  namespace windowpos
  {
    constexpr int undefined = SDL_WINDOWPOS_UNDEFINED; /**< use to indicate that you don't care what the window position is. */
    constexpr int centered = SDL_WINDOWPOS_CENTERED;   /**< used to indicate that the window position should be centered */
  }                                                    // namespace windowpos

  namespace detail
  {
    /**
     * @brief window base class
     * @details this class provides the api implementation for window structures
     *
     * @tparam Derived concret window class
     */
    template <typename Derived>
    struct window_api
    {
    private:
      inline void set_fullscreen(std::uint32_t flags) { SDL2_CXX_CHECK(SDL_SetWindowFullscreen(to_sdl_type(*this), flags) == 0); }

    public:
      /**
       * @brief Get the `sdl2::surface` associated with the window
       * @details A new surface will be created with the optimal format for the current window.
       * This function calls `SDL_GetWindowSurface`
       *
       * @note the returned surface is managed by the window it self
       *
       * @return `sdl2::surface_ref` associated with the window
       * @throw sdl2::exception on error
       *
       * @sa `window_api::update_surface`
       */
      inline surface_ref get_surface() const
      {
        SDL_Surface* sf(SDL_GetWindowSurface(to_sdl_type(*this)));
        SDL2_CXX_CHECK(sf != nullptr);
        return surface_ref(sf);
      }
      inline void update_surface() { SDL2_CXX_CHECK(SDL_UpdateWindowSurface(to_sdl_type(*this)) >= 0); }

      inline void get_size(int& w, int& h) const noexcept { SDL_GetWindowSize(to_sdl_type(*this), &w, &h); }
      inline void set_size(int w, int h) noexcept { SDL_SetWindowSize(to_sdl_type(*this), w, h); }

      inline void set_position(int x, int y) noexcept { SDL_SetWindowPosition(to_sdl_type(*this), x, y); }

      inline void set_windowed() { set_fullscreen(0); }
      inline void set_fullscreen(window_flags flag) { set_fullscreen(static_cast<std::underlying_type_t<window_flags>>(flag)); }

      inline uint32_t get_flags() const noexcept { return SDL_GetWindowFlags(to_sdl_type(*this)); }

      explicit operator bool() const { return to_sdl_type(*this) != nullptr; }
      friend SDL_Window* to_sdl_type(const window_api& self) { return to_sdl_type(static_cast<const Derived&>(self)); }

    protected:
      virtual ~window_api() = default;
    };
  } // namespace detail

  class window final : public detail::window_api<window>, detail::noncopyable
  {
  public:
    explicit window(const std::string& title, int w, int h, window_flags flags = window_flags::none)
        : window(title, windowpos::undefined, windowpos::undefined, w, h, flags)
    {
    }
    explicit window(const std::string& title, int x, int y, int w, int h, window_flags flags = window_flags::none)
        : m_window(SDL_CreateWindow(title.c_str(), x, y, w, h, (flags == window_flags::none) ? 0 : static_cast<std::underlying_type_t<window_flags>>(flags)))
    {
      SDL2_CXX_CHECK(m_window != nullptr);
    }

    explicit window(const std::string& title, int x, int y, int w, int h, std::initializer_list<window_flags> flags)
        : m_window(SDL_CreateWindow(title.c_str(), x, y, w, h, combine(flags)))
    {
      SDL2_CXX_CHECK(m_window != nullptr);
    }

    window(window&& w) : m_window(std::move(w.m_window)) {}
    window& operator=(window&& w)
    {
      m_window = std::move(w.m_window);
      return *this;
    }

  private:
    detail::sdl_ptr<SDL_Window, SDL_DestroyWindow> m_window = nullptr;

    friend SDL_Window* to_sdl_type(const window&);
  };

  inline SDL_Window* to_sdl_type(const window& w) { return w.m_window.get(); }

} // namespace sdl2

#endif