/**
* @file   event_handler.hxx
* @Author: zie87
* @Date:   2017-10-18 20:53:14
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-18 21:54:48
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_EVENT_EVENT_HANDLER_HXX
#define SDL2_CXX_EVENT_EVENT_HANDLER_HXX

#include <SDL_events.h>
#include <functional>

namespace sdl2
{

  struct event_handler
  {
    static inline bool poll(SDL_Event* event) noexcept { return (SDL_PollEvent(event) != 0); }
    static inline void poll(std::function<void (const SDL_Event&)> fn) noexcept 
    {
      if (fn) 
      {
        SDL_Event event;
        while (poll(&event)) {  fn(event); }
      }
    }

    template <typename T>
    static inline void poll(std::function<void(const T&)> fn) noexcept 
    {
      if (fn) 
      {
        SDL_Event event;
        while (poll(&event)) { fn(event); }
      }
    }
  };

} // namespace sdl2

#endif