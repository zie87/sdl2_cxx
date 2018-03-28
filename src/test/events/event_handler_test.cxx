/**
* @file   event_handler_test.cxx
* @Author: zie87
* @Date:   2017-10-21 10:03:08
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-21 10:12:29
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#include <sdl2_cxx/events/event.hxx>
#include <sdl2_cxx/events/event_handler.hxx>

#include <SDL.h>

#include <catch.hpp>


TEST_CASE("test basic event handling functions", "[events]") 
{
  SDL_Init(SDL_INIT_EVENTS);

  {
    // make sure no event is left
    SDL_Event e;
    while (SDL_PollEvent(&e)) {}   
  }

  SECTION("poll and types are wrapped correctly") 
  {
    {
      SDL_Event push_event;
      push_event.type = SDL_USEREVENT;
      SDL_PushEvent(&push_event);

      bool event_found = false;
      sdl2::event_handler::poll([&event_found](auto e) 
      {
        auto type = sdl2::event_traits::type(e);
        if (type == sdl2::event_type::user_event) { event_found = true; }
      });

      REQUIRE(event_found);
    }
  }

  SDL_Quit();
}