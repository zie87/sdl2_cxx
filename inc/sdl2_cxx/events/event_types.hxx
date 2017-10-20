/**
* @file   event_types.hxx
* @Author: zie87
* @Date:   2017-10-18 21:05:09
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-20 17:10:01
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_EVENTS_EVENT_TYPES_HXX
#define SDL2_CXX_EVENTS_EVENT_TYPES_HXX

#include <SDL_events.h>
#include <type_traits>

#include <sdl2_cxx/core/stdinc.hxx>
#include <sdl2_cxx/detail/type_traits.hxx>

namespace sdl2
{
  enum class button_state : uint8_t
  {
    released = SDL_RELEASED,
    pressed = SDL_PRESSED
  };

  enum class event_type : std::underlying_type_t<SDL_EventType>
  {
    first = SDL_FIRSTEVENT,
    quit = SDL_QUIT,

    app_terminating = SDL_APP_TERMINATING,
    app_lowmemory = SDL_APP_LOWMEMORY,
    app_will_enter_background = SDL_APP_WILLENTERBACKGROUND,
    app_did_enter_background = SDL_APP_DIDENTERBACKGROUND,
    app_will_enter_foreground = SDL_APP_WILLENTERFOREGROUND,
    app_did_enter_foreground = SDL_APP_DIDENTERFOREGROUND,

    window = SDL_WINDOWEVENT,
    syswm = SDL_SYSWMEVENT,

    key_down = SDL_KEYDOWN,
    key_up = SDL_KEYUP,
    text_editing = SDL_TEXTEDITING,
    text_input = SDL_TEXTINPUT,
    keymap_changed = SDL_KEYMAPCHANGED,

    mouse_motion = SDL_MOUSEMOTION,
    mouse_button_down = SDL_MOUSEBUTTONDOWN,
    mouse_button_up = SDL_MOUSEBUTTONUP,
    mouse_wheel = SDL_MOUSEWHEEL,

    joy_axis_motion = SDL_JOYAXISMOTION,
    joy_ball_motion = SDL_JOYBALLMOTION,
    joy_hat_motion = SDL_JOYHATMOTION,
    joy_button_down = SDL_JOYBUTTONDOWN,
    joy_button_up = SDL_JOYBUTTONUP,
    joy_device_added = SDL_JOYDEVICEADDED,
    joy_device_removed = SDL_JOYDEVICEREMOVED,

    controller_axis_motion = SDL_CONTROLLERAXISMOTION,
    controller_button_down = SDL_CONTROLLERBUTTONDOWN,
    controller_button_up = SDL_CONTROLLERBUTTONUP,
    controller_device_added = SDL_CONTROLLERDEVICEADDED,
    controller_device_removed = SDL_CONTROLLERDEVICEREMOVED,
    controller_device_remapped = SDL_CONTROLLERDEVICEREMAPPED,

    finger_down = SDL_FINGERDOWN,
    finger_up = SDL_FINGERUP,
    finger_motion = SDL_FINGERMOTION,

    dollar_gesture = SDL_DOLLARGESTURE,
    dollar_record = SDL_DOLLARRECORD,
    multi_gesture = SDL_MULTIGESTURE,

    clipboard_update = SDL_CLIPBOARDUPDATE,

    drop_file = SDL_DROPFILE,
    drop_text = SDL_DROPTEXT,
    drop_begin = SDL_DROPBEGIN,
    drop_complete = SDL_DROPCOMPLETE,

    audio_device_added = SDL_AUDIODEVICEADDED,
    audio_device_removed = SDL_AUDIODEVICEREMOVED,

    render_targets_reset = SDL_RENDER_TARGETS_RESET,
    render_device_reset = SDL_RENDER_DEVICE_RESET,

    user_event = SDL_USEREVENT,

    last = SDL_LASTEVENT,
    invalid = static_cast<uint32_t>(-1)
  };

  constexpr bool is_quit_event_type(event_type type) { return (type == event_type::quit); }
  constexpr bool is_window_event_type(event_type type) { return (type == event_type::window); }
  constexpr bool is_syswm_event_type(event_type type) { return (type == event_type::syswm); }
  constexpr bool is_keyboard_event_type(event_type type) { return (type == event_type::key_down) || (type == event_type::key_up); }
  constexpr bool is_text_editing_event_type(event_type type) { return (type == event_type::text_editing); }
  constexpr bool is_text_input_event_type(event_type type) { return (type == event_type::text_input); }
  constexpr bool is_mouse_motion_event_type(event_type type) { return (type == event_type::mouse_motion); }
  constexpr bool is_mouse_button_event_type(event_type type) { return (type == event_type::mouse_button_down) || (type == event_type::mouse_button_up); }
  constexpr bool is_mouse_wheel_event_type(event_type type) { return (type == event_type::mouse_wheel); }
  constexpr bool is_joy_axis_event_type(event_type type) { return (type == event_type::joy_axis_motion); }
  constexpr bool is_joy_ball_event_type(event_type type) { return (type == event_type::joy_ball_motion); }
  constexpr bool is_joy_hat_event_type(event_type type) { return (type == event_type::joy_hat_motion); }
  constexpr bool is_joy_button_event_type(event_type type) { return (type == event_type::joy_button_down) || (type == event_type::joy_button_up); }
  constexpr bool is_joy_device_event_type(event_type type) { return (type == event_type::joy_device_added) || (type == event_type::joy_device_removed); }
  constexpr bool is_controller_axis_event_type(event_type type) { return (type == event_type::controller_axis_motion); }
  constexpr bool is_controller_button_event_type(event_type type) { return (type == event_type::controller_button_down) || (type == event_type::controller_button_up); }
  constexpr bool is_controller_device_event_type(event_type type) { return (type == event_type::controller_device_added) || (type == event_type::controller_device_removed) || (type == event_type::controller_device_remapped); }
  constexpr bool is_touch_finger_event_type(event_type type) { return (type == event_type::finger_down) || (type == event_type::finger_up) || (type == event_type::finger_motion); }
  constexpr bool is_dollar_gesture_event_type(event_type type) { return (type == event_type::dollar_gesture) || (type == event_type::dollar_record); }
  constexpr bool is_multi_gesture_event_type(event_type type) { return (type == event_type::multi_gesture); }
  constexpr bool is_drop_event_type(event_type type) { return (type == event_type::drop_file) || (type == event_type::drop_text) || (type == event_type::drop_begin) || (type == event_type::drop_complete); }
  constexpr bool is_audio_device_event_type(event_type type) { return (type == event_type::audio_device_added) || (type == event_type::audio_device_removed); }
  constexpr bool is_user_event_type(event_type type) { return (type >= event_type::user_event) && (type <= event_type::last); }
  constexpr bool is_valid_event_type(event_type type) { return (type >= event_type::first) && (type <= event_type::last); }

  template <typename T>
  struct is_common_event : meta_if<std::is_same<T, SDL_CommonEvent>::value> {};

  template <event_type T>
  struct is_quit_event : meta_if<is_quit_event_type(T)> {};

  template <event_type T>
  struct is_window_event : meta_if<is_window_event_type(T)> {};

  template <event_type T>
  struct is_syswm_event : meta_if<is_syswm_event_type(T)> {};

  template <event_type T>
  struct is_keyboard_event : meta_if<is_keyboard_event_type(T)> {};

  template <event_type T>
  struct is_text_editing_event : meta_if<is_text_editing_event_type(T)> {};

  template <event_type T>
  struct is_text_input_event : meta_if<is_text_input_event_type(T)> {};

  template <event_type T>
  struct is_mouse_motion_event : meta_if<is_mouse_motion_event_type(T)> {};

  template <event_type T>
  struct is_mouse_button_event : meta_if<is_mouse_button_event_type(T)> {};

  template <event_type T>
  struct is_mouse_wheel_event : meta_if<is_mouse_wheel_event_type(T)> {};

  template <event_type T>
  struct is_joy_axis_event : meta_if<is_joy_axis_event_type(T)> {};

  template <event_type T>
  struct is_joy_ball_event : meta_if<is_joy_ball_event_type(T)> {};

  template <event_type T>
  struct is_joy_hat_event : meta_if<is_joy_hat_event_type(T)> {};

  template <event_type T>
  struct is_joy_button_event : meta_if<is_joy_button_event_type(T)> {};

  template <event_type T>
  struct is_joy_device_event : meta_if<is_joy_device_event_type(T)> {};

  template <event_type T>
  struct is_controller_axis_event : meta_if<is_controller_axis_event_type(T)> {};

  template <event_type T>
  struct is_controller_button_event : meta_if<is_controller_button_event_type(T)> {};

  template <event_type T>
  struct is_controller_device_event : meta_if<is_controller_device_event_type(T)> {};

  template <event_type T>
  struct is_touch_finger_event : meta_if<is_touch_finger_event_type(T)> {};

  template <event_type T>
  struct is_dollar_gesture_event : meta_if<is_dollar_gesture_event_type(T)> {};

  template <event_type T>
  struct is_multi_gesture_event : meta_if<is_multi_gesture_event_type(T)> {};

  template <event_type T>
  struct is_drop_event : meta_if<is_drop_event_type(T)> {};

  template <event_type T>
  struct is_audio_device_event : meta_if<is_audio_device_event_type(T)> {};

  template <event_type T>
  struct is_user_event : meta_if<is_user_event_type(T)> {};

  template <event_type T>
  struct is_valid_event : meta_if<is_valid_event_type(T)> {};

  template <event_type T>
  using event_data =
    std::conditional_t<is_quit_event<T>::value, SDL_QuitEvent,
    std::conditional_t<is_window_event<T>::value, SDL_WindowEvent,
    std::conditional_t<is_syswm_event<T>::value, SDL_SysWMEvent,
    std::conditional_t<is_keyboard_event<T>::value, SDL_KeyboardEvent,
    std::conditional_t<is_text_editing_event<T>::value, SDL_TextEditingEvent,
    std::conditional_t<is_text_input_event<T>::value, SDL_TextInputEvent,
    std::conditional_t<is_mouse_motion_event<T>::value, SDL_MouseMotionEvent,
    std::conditional_t<is_mouse_button_event<T>::value, SDL_MouseButtonEvent,
    std::conditional_t<is_mouse_wheel_event<T>::value, SDL_MouseWheelEvent,
    std::conditional_t<is_joy_axis_event<T>::value, SDL_JoyAxisEvent,
    std::conditional_t<is_joy_ball_event<T>::value, SDL_JoyBallEvent,
    std::conditional_t<is_joy_hat_event<T>::value, SDL_JoyHatEvent,
    std::conditional_t<is_joy_button_event<T>::value, SDL_JoyButtonEvent,
    std::conditional_t<is_joy_device_event<T>::value, SDL_JoyDeviceEvent,
    std::conditional_t<is_controller_axis_event<T>::value, SDL_ControllerAxisEvent,
    std::conditional_t<is_controller_button_event<T>::value, SDL_ControllerButtonEvent,
    std::conditional_t<is_controller_device_event<T>::value, SDL_ControllerDeviceEvent,
    std::conditional_t<is_touch_finger_event<T>::value, SDL_TouchFingerEvent,
    std::conditional_t<is_dollar_gesture_event<T>::value, SDL_DollarGestureEvent,
    std::conditional_t<is_multi_gesture_event<T>::value, SDL_MultiGestureEvent,
    std::conditional_t<is_drop_event<T>::value, SDL_DropEvent,
    std::conditional_t<is_audio_device_event<T>::value, SDL_AudioDeviceEvent,
    std::conditional_t<is_user_event<T>::value, SDL_UserEvent,
    std::conditional_t<is_valid_event<T>::value, SDL_CommonEvent,
    void
  >>>>>>>>>> >>>>>>>>>> >>>>;

  template <class T, concept_is_same<T, SDL_QuitEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::quit; }

  template <class T, concept_is_same<T, SDL_WindowEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::window; }

  template <class T, concept_is_same<T, SDL_SysWMEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::syswm; }

  template <class T, concept_is_same<T, SDL_KeyboardEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::key_down; }

  template <class T, concept_is_same<T, SDL_TextEditingEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::text_editing; }

  template <class T, concept_is_same<T, SDL_TextInputEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::text_input; }

  template <class T, concept_is_same<T, SDL_MouseMotionEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::mouse_motion; }

  template <class T, concept_is_same<T, SDL_MouseButtonEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::mouse_button_down; }

  template <class T, concept_is_same<T, SDL_MouseWheelEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::mouse_wheel; }

  template <class T, concept_is_same<T, SDL_JoyAxisEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::joy_axis_motion; }

  template <class T, concept_is_same<T, SDL_JoyBallEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::joy_ball_motion; }

  template <class T, concept_is_same<T, SDL_JoyHatEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::joy_hat_motion; }

  template <class T, concept_is_same<T, SDL_JoyButtonEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::joy_button_down; }

  template <class T, concept_is_same<T, SDL_JoyDeviceEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::joy_device_added; }

  template <class T, concept_is_same<T, SDL_ControllerAxisEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::controller_axis_motion; }

  template <class T, concept_is_same<T, SDL_ControllerButtonEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::controller_button_down; }

  template <class T, concept_is_same<T, SDL_ControllerDeviceEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::controller_device_added; }

  template <class T, concept_is_same<T, SDL_TouchFingerEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::finger_down; }

  template <class T, concept_is_same<T, SDL_DollarGestureEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::dollar_gesture; }

  template <class T, concept_is_same<T, SDL_MultiGestureEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::multi_gesture; }

  template <class T, concept_is_same<T, SDL_DropEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::drop_file; }

  template <class T, concept_is_same<T, SDL_AudioDeviceEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::audio_device_added; }

  template <class T, concept_is_same<T, SDL_UserEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::user_event; }

  template <class T, concept_is_same<T, SDL_CommonEvent> = nullptr>
  constexpr inline event_type to_event_type() { return event_type::first; }

  constexpr inline event_type to_event_type() { return event_type::invalid; }
} // namespace sdl2

#endif