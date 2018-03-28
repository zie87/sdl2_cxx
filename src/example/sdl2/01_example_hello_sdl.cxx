/** 
 *  @file    01_example_hello_sdl.cxx
 *  @author  zie87
 *  @date    2017-10-15 02:51:40
 *  @version 2017-10-24 05:25:53
 *  
 *  @brief Hello SDL
 *
 *  Simple example about window creation
 **/


#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/core/log.hxx>

#include <sdl2_cxx/time/timer.hxx>
#include <sdl2_cxx/video/window.hxx>

using namespace std::chrono_literals;

int main(int /*argc*/, char** /*argv*/)
{
  constexpr int SCREEN_WIDTH = 640;
  constexpr int SCREEN_HEIGHT = 480;

  try
  {
      sdl2::init_guard guard(sdl2::init_flags::video);

      sdl2::window window("Hello SDL", sdl2::windowpos::centered, sdl2::windowpos::centered, SCREEN_WIDTH, SCREEN_HEIGHT, sdl2::window_flags::shown);
      
      auto screen = window.get_surface();
      screen.fill(0xFF, 0xFF, 0xFF);

      sdl2::rect rect( 50, 50, 50, 50 );
      screen.fill(rect, 0, 0, 0);

      window.update_surface();

      using namespace std::chrono_literals;
      sdl2::delay(2s);

  } catch( const sdl2::exception& e )
  {
    sdl2::log::out() << sdl2::log::category::error << sdl2::log::priority::critical << "sdl2::exception: " << e.what();
    return -1;
  } catch (...) 
  {
    sdl2::log::out() << sdl2::log::category::error << sdl2::log::priority::critical << "sdl init wasn't possible!";
    return -1;
  }

  return 0;
}