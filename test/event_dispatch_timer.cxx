/**
* @file   event_dispatch_timer.cxx
* @Author: zie87
* @Date:   2017-10-18 22:02:15
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-18 22:06:14
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/events/event.hxx>
#include <sdl2_cxx/events/event_handler.hxx>

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

struct timer {
    using time_point = std::chrono::high_resolution_clock::time_point;

    std::chrono::milliseconds elapsed() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _start);
    }

    time_point _start = std::chrono::high_resolution_clock::now();
};

int main(int argc, char const *argv[])
{

    constexpr auto timeout = 3s;
    auto c_count = 0;
    auto cxx_match_count = 0;

    {
      auto t = timer{};
      while (t.elapsed() < timeout) 
      {
        SDL_Event e;
        while (SDL_PollEvent(&e)) 
        {
            switch (e.type) {
            case SDL_USEREVENT:
                c_count++;
            }
        }
        SDL_Event push_event;
        push_event.type = SDL_USEREVENT;
        SDL_PushEvent(&push_event);
      }
    }


    {
      auto t = timer{};
      while (t.elapsed() < timeout) 
      {
        sdl2::event_handler::poll([&cxx_match_count](auto e) 
        {
          auto type = sdl2::event_traits::type(e);
          if (type == sdl2::event_type::user_event) { cxx_match_count++; }
        });

        SDL_Event push_event;
        push_event.type = SDL_USEREVENT;
        SDL_PushEvent(&push_event);
      }
    }

    std::cout << "SDL_Event loop: " << c_count / timeout.count()
              << " events per second\n";

    std::cout << "sdl2::event poll loop: "
              << cxx_match_count / timeout.count()
              << " events per second (overhead "
              << 100.0 * (c_count - cxx_match_count) / double(c_count)
              << "%)\n";

  return 0;
}