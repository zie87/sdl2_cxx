/**
 * @file   hints.hxx
 * @Author: zie87
 * @Date:   2017-10-22 14:41:16
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-22 16:08:03
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_CORE_HINT_HXX
#define SDL2_CXX_CORE_HINT_HXX

#include <SDL_hints.h>

#include <sdl2_cxx/core/error.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>

namespace sdl2
{
  enum class hint_type
  {
    framebuffer_acceleration,                 // SDL_HINT_FRAMEBUFFER_ACCELERATION
    render_driver,                            // SDL_HINT_RENDER_DRIVER
    render_opengl_shaders,                    // SDL_HINT_RENDER_OPENGL_SHADERS
    render_direct3d_threadsafe,               // SDL_HINT_RENDER_DIRECT3D_THREADSAFE
    render_direct3d11_debug,                  // SDL_HINT_RENDER_DIRECT3D11_DEBUG
    render_logical_size_mode,                 // SDL_HINT_RENDER_LOGICAL_SIZE_MODE"
    render_scale_quality,                     // SDL_HINT_RENDER_SCALE_QUALITY
    render_vsync,                             // SDL_HINT_RENDER_VSYNC
    video_allow_screensaver,                  // SDL_HINT_VIDEO_ALLOW_SCREENSAVER
    video_x11_xvidmode,                       // SDL_HINT_VIDEO_X11_XVIDMODE
    video_x11_xinerama,                       // SDL_HINT_VIDEO_X11_XINERAMA
    video_x11_xrandr,                         // SDL_HINT_VIDEO_X11_XRANDR
    video_x11_net_wm_ping,                    // SDL_HINT_VIDEO_X11_NET_WM_PING
    window_frame_usable_while_cursor_hidden,  // SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN
    window_intresource_icon,                  // SDL_HINT_WINDOWS_INTRESOURCE_ICON
    window_intresource_icon_small,            // SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL
    windows_enable_messageloop,               // SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP
    grab_keyboard,                            // SDL_HINT_GRAB_KEYBOARD
    mouse_normal_speed_scale,                 // SDL_HINT_MOUSE_NORMAL_SPEED_SCALE
    mouse_relative_speed_scale,               // SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE
    mouse_relative_warp_mode,                 // SDL_HINT_MOUSE_RELATIVE_MODE_WARP
    mouse_focus_clickthrough,                 // SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH
    touch_mouse_events,                       // SDL_HINT_TOUCH_MOUSE_EVENTS
    video_minimize_on_focus_loss,             // SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS
    idle_timer_disabled,                      // SDL_HINT_IDLE_TIMER_DISABLED
    orientations,                             // SDL_HINT_ORIENTATIONS
    apple_tv_controller_ui_events,            // SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS
    apple_tv_remote_allow_rotation,           // SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION
    accelerometer_as_joystick,                // SDL_HINT_ACCELEROMETER_AS_JOYSTICK
    xinput_enabled,                           // SDL_HINT_XINPUT_ENABLED
    xinput_use_old_joystick_mapping,          // SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING
    gamecontrollerconfig,                     // SDL_HINT_GAMECONTROLLERCONFIG
    gamecontroller_ignore_devices,            // SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES
    gamecontroller_ignore_devices_except,     // SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT
    joystick_allow_background_events,         // SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS
    allow_topmost,                            // SDL_HINT_ALLOW_TOPMOST
    timer_resolution,                         // SDL_HINT_TIMER_RESOLUTION
    qtwayland_content_orientation,            // SDL_HINT_QTWAYLAND_CONTENT_ORIENTATION
    qtwayland_window_flags,                   // SDL_HINT_QTWAYLAND_WINDOW_FLAGS
    thread_stack_size,                        // SDL_HINT_THREAD_STACK_SIZE
    video_highdpi_disabled,                   // SDL_HINT_VIDEO_HIGHDPI_DISABLED
    mac_ctrl_click_emulate_right_click,       // SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK
    video_win_d3dcompiler,                    // SDL_HINT_VIDEO_WIN_D3DCOMPILER
    video_window_share_pixel_format,          // SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT
    winrt_privacy_policy_url,                 // SDL_HINT_WINRT_PRIVACY_POLICY_URL
    winrt_privacy_policy_label,               // SDL_HINT_WINRT_PRIVACY_POLICY_LABEL
    winrt_handle_back_button,                 // SDL_HINT_WINRT_HANDLE_BACK_BUTTON
    video_mac_fullscreen_spaces,              // SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES
    mac_background_app,                       // SDL_HINT_MAC_BACKGROUND_APP
    android_apk_expansion_main_file_version,  // SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION
    android_apk_expansion_patch_file_version, // SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION
    ime_internal_editing,                     // SDL_HINT_IME_INTERNAL_EDITING
    android_separate_mouse_and_touch,         // SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH
    emscripten_keyboard_element,              // SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT
    no_signal_handlers,                       // SDL_HINT_NO_SIGNAL_HANDLERS
    windows_no_close_on_alt_f4,               // SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4
    bmp_save_legacy_format,                   // SDL_HINT_BMP_SAVE_LEGACY_FORMAT "SDL_BMP_SAVE_LEGACY_FORMAT"
    window_disable_thread_naming,             // SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING
    rpi_video_layer,                          // SDL_HINT_RPI_VIDEO_LAYER
    opengl_es_driver,                         // SDL_HINT_OPENGL_ES_DRIVER
    audio_resampling_mode,                    // SDL_HINT_AUDIO_RESAMPLING_MODE
    audio_category                            // SDL_HINT_AUDIO_CATEGORY
  };

  inline const char* to_sdl_type(hint_type h)
  {
    switch (h)
    {
      case hint_type::framebuffer_acceleration:
        return SDL_HINT_FRAMEBUFFER_ACCELERATION;
      case hint_type::render_driver:
        return SDL_HINT_RENDER_DRIVER;
      case hint_type::render_opengl_shaders:
        return SDL_HINT_RENDER_OPENGL_SHADERS;
      case hint_type::render_direct3d_threadsafe:
        return SDL_HINT_RENDER_DIRECT3D_THREADSAFE;
      case hint_type::render_direct3d11_debug:
        return SDL_HINT_RENDER_DIRECT3D11_DEBUG;
      case hint_type::render_logical_size_mode:
        return SDL_HINT_RENDER_LOGICAL_SIZE_MODE;
      case hint_type::render_scale_quality:
        return SDL_HINT_RENDER_SCALE_QUALITY;
      case hint_type::render_vsync:
        return SDL_HINT_RENDER_VSYNC;
      case hint_type::video_allow_screensaver:
        return SDL_HINT_VIDEO_ALLOW_SCREENSAVER;
      case hint_type::video_x11_xvidmode:
        return SDL_HINT_VIDEO_X11_XVIDMODE;
      case hint_type::video_x11_xinerama:
        return SDL_HINT_VIDEO_X11_XINERAMA;
      case hint_type::video_x11_xrandr:
        return SDL_HINT_VIDEO_X11_XRANDR;
      case hint_type::video_x11_net_wm_ping:
        return SDL_HINT_VIDEO_X11_NET_WM_PING;
      case hint_type::window_frame_usable_while_cursor_hidden:
        return SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN;
      case hint_type::window_intresource_icon:
        return SDL_HINT_WINDOWS_INTRESOURCE_ICON;
      case hint_type::window_intresource_icon_small:
        return SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL;
      case hint_type::windows_enable_messageloop:
        return SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP;
      case hint_type::grab_keyboard:
        return SDL_HINT_GRAB_KEYBOARD;
      case hint_type::mouse_normal_speed_scale:
        return SDL_HINT_MOUSE_NORMAL_SPEED_SCALE;
      case hint_type::mouse_relative_speed_scale:
        return SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE;
      case hint_type::mouse_relative_warp_mode:
        return SDL_HINT_MOUSE_RELATIVE_MODE_WARP;
      case hint_type::mouse_focus_clickthrough:
        return SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH;
      case hint_type::touch_mouse_events:
        return SDL_HINT_TOUCH_MOUSE_EVENTS;
      case hint_type::video_minimize_on_focus_loss:
        return SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS;
      case hint_type::idle_timer_disabled:
        return SDL_HINT_IDLE_TIMER_DISABLED;
      case hint_type::orientations:
        return SDL_HINT_ORIENTATIONS;
      case hint_type::apple_tv_controller_ui_events:
        return SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS;
      case hint_type::apple_tv_remote_allow_rotation:
        return SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION;
      case hint_type::accelerometer_as_joystick:
        return SDL_HINT_ACCELEROMETER_AS_JOYSTICK;
      case hint_type::xinput_enabled:
        return SDL_HINT_XINPUT_ENABLED;
      case hint_type::xinput_use_old_joystick_mapping:
        return SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING;
      case hint_type::gamecontrollerconfig:
        return SDL_HINT_GAMECONTROLLERCONFIG;
      case hint_type::gamecontroller_ignore_devices:
        return SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES;
      case hint_type::gamecontroller_ignore_devices_except:
        return SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT;
      case hint_type::joystick_allow_background_events:
        return SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS;
      case hint_type::allow_topmost:
        return SDL_HINT_ALLOW_TOPMOST;
      case hint_type::timer_resolution:
        return SDL_HINT_TIMER_RESOLUTION;
      case hint_type::qtwayland_content_orientation:
        return SDL_HINT_QTWAYLAND_CONTENT_ORIENTATION;
      case hint_type::qtwayland_window_flags:
        return SDL_HINT_QTWAYLAND_WINDOW_FLAGS;
      case hint_type::thread_stack_size:
        return SDL_HINT_THREAD_STACK_SIZE;
      case hint_type::video_highdpi_disabled:
        return SDL_HINT_VIDEO_HIGHDPI_DISABLED;
      case hint_type::mac_ctrl_click_emulate_right_click:
        return SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK;
      case hint_type::video_win_d3dcompiler:
        return SDL_HINT_VIDEO_WIN_D3DCOMPILER;
      case hint_type::video_window_share_pixel_format:
        return SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT;
      case hint_type::winrt_privacy_policy_url:
        return SDL_HINT_WINRT_PRIVACY_POLICY_URL;
      case hint_type::winrt_privacy_policy_label:
        return SDL_HINT_WINRT_PRIVACY_POLICY_LABEL;
      case hint_type::winrt_handle_back_button:
        return SDL_HINT_WINRT_HANDLE_BACK_BUTTON;
      case hint_type::video_mac_fullscreen_spaces:
        return SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES;
      case hint_type::mac_background_app:
        return SDL_HINT_MAC_BACKGROUND_APP;
      case hint_type::android_apk_expansion_main_file_version:
        return SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION;
      case hint_type::android_apk_expansion_patch_file_version:
        return SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION;
      case hint_type::ime_internal_editing:
        return SDL_HINT_IME_INTERNAL_EDITING;
      case hint_type::android_separate_mouse_and_touch:
        return SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH;
      case hint_type::emscripten_keyboard_element:
        return SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT;
      case hint_type::no_signal_handlers:
        return SDL_HINT_NO_SIGNAL_HANDLERS;
      case hint_type::windows_no_close_on_alt_f4:
        return SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4;
      case hint_type::bmp_save_legacy_format:
        return SDL_HINT_BMP_SAVE_LEGACY_FORMAT;
      case hint_type::window_disable_thread_naming:
        return SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING;
      case hint_type::rpi_video_layer:
        return SDL_HINT_RPI_VIDEO_LAYER;
      case hint_type::opengl_es_driver:
        return SDL_HINT_OPENGL_ES_DRIVER;
      case hint_type::audio_resampling_mode:
        return SDL_HINT_AUDIO_RESAMPLING_MODE;
      case hint_type::audio_category:
        return SDL_HINT_AUDIO_CATEGORY;
      default:
        SDL_assert(false);
    }

    return nullptr;
  }

  struct hint final
  {
    enum class priority : std::underlying_type_t<SDL_HintPriority>
    {
      sdl_default = SDL_HINT_DEFAULT,
      sdl_normal = SDL_HINT_NORMAL,
      sdl_override = SDL_HINT_OVERRIDE
    };

    using value_type = const char*;

    static inline bool set(hint_type name, value_type value) noexcept { return (SDL_SetHint(to_sdl_type(name), value) == SDL_TRUE); }
    static inline bool set(hint_type name, value_type value, priority priority) noexcept
    {
      return (SDL_SetHintWithPriority(to_sdl_type(name), value, static_cast<SDL_HintPriority>(priority)) == SDL_TRUE);
    }

    static inline value_type get(hint_type name) noexcept { return SDL_GetHint(to_sdl_type(name)); }
    static bool get(hint_type name, bool default_value) noexcept
    {
      return (SDL_GetHintBoolean(to_sdl_type(name), default_value ? SDL_TRUE : SDL_FALSE) == SDL_TRUE);
    }

    static void clear() noexcept { SDL_ClearHints(); }
  };

} // sdl2

#endif