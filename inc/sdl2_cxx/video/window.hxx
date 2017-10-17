/**
* @file   window.hxx
* @Author: zie87
* @Date:   2017-10-16 22:38:08
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-17 05:30:00
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_VIDEO_WINDOW_HXX
#define SDL2_CXX_VIDEO_WINDOW_HXX

#include <SDL_video.h>

#include <sdl2_cxx/detail/bitmask.hxx>
#include <sdl2_cxx/detail/wrapper.hxx>
#include <sdl2_cxx/detail/interfaces.hxx>

#include <sdl2_cxx/core/error.hxx>

namespace sdl2
{
  enum class window_flags : std::underlying_type_t<SDL_WindowFlags>
  {
    none                = 0,
    fullscreen          = SDL_WINDOW_FULLSCREEN,         /**< fullscreen window */
    opengl              = SDL_WINDOW_OPENGL,             /**< window usable with OpenGL context */
    shown               = SDL_WINDOW_SHOWN,              /**< window is visible */
    hidden              = SDL_WINDOW_HIDDEN,             /**< window is not visible */
    borderless          = SDL_WINDOW_BORDERLESS,         /**< no window decoration */
    resizable           = SDL_WINDOW_RESIZABLE,          /**< window can be resized */
    minimized           = SDL_WINDOW_MINIMIZED,          /**< window is minimized */
    maximized           = SDL_WINDOW_MAXIMIZED,          /**< window is maximized */
    input_grabbed       = SDL_WINDOW_INPUT_GRABBED,      /**< window has grabbed input focus */
    input_focus         = SDL_WINDOW_INPUT_FOCUS,        /**< window has input focus */
    mouse_focus         = SDL_WINDOW_MOUSE_FOCUS,        /**< window has mouse focus */
    fullscreen_desktop  = SDL_WINDOW_FULLSCREEN_DESKTOP,
    foreign             = SDL_WINDOW_FOREIGN,            /**< window not created by SDL */
    allow_highdpi       = SDL_WINDOW_ALLOW_HIGHDPI,      /**< window should be created in high-DPI mode if supported */
    mouse_capture       = SDL_WINDOW_MOUSE_CAPTURE,      /**< window has mouse captured (unrelated to INPUT_GRABBED) */
    always_on_top       = SDL_WINDOW_ALWAYS_ON_TOP,      /**< window should always be above others */
    skip_taskbar        = SDL_WINDOW_SKIP_TASKBAR,       /**< window should not be added to the taskbar */
    utility             = SDL_WINDOW_UTILITY,            /**< window should be treated as a utility window */
    tooltip             = SDL_WINDOW_TOOLTIP,            /**< window should be treated as a tooltip */
    popup_menu          = SDL_WINDOW_POPUP_MENU,         /**< window should be treated as a popup menu */
    vulkan              = SDL_WINDOW_VULKAN              /**< window usable for Vulkan surface */
  };

  template<>
  struct enable_bitmask_operators<window_flags>{ static const bool enable = true; };

  namespace windowpos 
  {
      constexpr int undefined = SDL_WINDOWPOS_UNDEFINED;
      constexpr int centered = SDL_WINDOWPOS_CENTERED;
  }


  namespace detail 
  {
    template <typename Derived>
    struct window_api 
    {

      explicit operator bool() const { return to_sdl_type(*this) != nullptr; }

      friend SDL_Window* to_sdl_type(const window_api& self) { return to_sdl_type(static_cast<const Derived&>(self)); }

      protected:
        virtual ~window_api() = default;
    };
  } // namespace detail

  class window : public detail::window_api<window>, detail::noncopyable
  {
    public:
      explicit window(const std::string& title, int w, int h, window_flags flags = window_flags::none) : window(title, windowpos::undefined, windowpos::undefined, w, h, flags) {}
      explicit window(const std::string& title, int x, int y, int w, int h, window_flags flags = window_flags::none)
      : detail::window_api<window>(), detail::noncopyable(), m_window( SDL_CreateWindow(title.c_str(), x, y, w, h, static_cast<std::underlying_type_t<window_flags>>(flags)) )
      {
        SDL2_CXX_CHECK( m_window != nullptr );
      }

      window(window&& w): m_window(std::move(w.m_window)) {}
      window& operator=(window&& w) { m_window = std::move(w.m_window); return *this; }

      private:
        detail::sdl_ptr<SDL_Window, SDL_DestroyWindow> m_window = nullptr;

        friend SDL_Window* to_sdl_type(const window&);
    };

    inline SDL_Window* to_sdl_type(const window& w) { return w.m_window.get(); }

} // namespace sdl2

#endif