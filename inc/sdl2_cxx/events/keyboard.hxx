/**
* @file   keyboard.hxx
* @Author: zie87
* @Date:   2017-10-20 17:57:41
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-20 18:13:49
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_EVENTS_KEYBOARD_HXX
#define SDL2_CXX_EVENTS_KEYBOARD_HXX

#include <SDL_keyboard.h>

#include <string>

#include <sdl2_cxx/events/event_types.hxx>
#include <sdl2_cxx/events/scancode.hxx>
#include <sdl2_cxx/events/keycode.hxx>

namespace sdl2
{
  struct keyboard
  {
    static inline bool is_pressed(scancode code) noexcept 
    { 
      int size = 0;
      auto current_states = SDL_GetKeyboardState(&size);
      std::size_t pos(static_cast<size_t>(code));
      
      bool pressed = false;
      if( pos < size )
        pressed = (current_states[pos] == static_cast<uint8_t>(button_state::pressed) );

      return pressed;
    }
    static inline bool is_pressed(keycode code) noexcept { return is_pressed(to_scancode(code)); }

    static inline keycode to_keycode(scancode code) noexcept { return static_cast<keycode>(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(code))); }
    static inline keycode to_keycode(const std::string& name) noexcept { return static_cast<keycode>(SDL_GetKeyFromName(name.c_str())); }
    static inline std::string keycode_name(keycode code) noexcept { return SDL_GetKeyName(static_cast<SDL_Keycode>(code)); }

    static inline scancode to_scancode(keycode code) noexcept { return static_cast<scancode>(SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(code))); }
    static inline scancode to_scancode(const std::string& name) noexcept { return static_cast<scancode>(SDL_GetScancodeFromName(name.c_str())); }
    static inline std::string scancode_name(scancode code) noexcept { return SDL_GetScancodeName(static_cast<SDL_Scancode>(code)); }
  };
}

#endif