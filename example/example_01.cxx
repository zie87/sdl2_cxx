/**
* @file   example_01.cxx
* @Author: zie87
* @Date:   2017-10-15 02:51:40
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-15 02:56:46
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/


#include <sdl2_cxx/core/init.hxx>
#include <sdl2_cxx/core/log.hxx>

#include <sdl2_cxx/time/timer.hxx>

using namespace std::chrono_literals;

int main(int /*argc*/, char** /*argv*/)
{
    try
    {
        sdl2::init_guard guard{};
        sdl2::delay(2s);
    } catch( const sdl2::exception& e )
    {
        sdl2::log::out() << sdl2::log::category::error << sdl2::log::priority::critical << e.what(); 
    } catch (...) 
    {   
        sdl2::log::out() << sdl2::log::category::error << sdl2::log::priority::critical << "sdl init wasn't possible!";
    }

    return 0;
}