/**
* @file   init_test.cxx
* @Author: zie87
* @Date:   2017-10-09 21:23:08
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-14 10:17:23
**/

#include <sdl2_cxx/core/init.hxx>

#include <catch.hpp>

inline bool was_init( uint32_t flag ) { return (SDL_WasInit(0) & flag); }

TEST_CASE( "init SDL2 system", "[core]" ) 
{
    // precheck that sdl wasn't initialised
    SECTION( "default guard" ) 
    {
        try
        {
            sdl2::init_guard guard{};
            REQUIRE( was_init(SDL_INIT_EVERYTHING) );
        } catch( const sdl2::exception& e )
        {
            // init wasn't succesful but error handling works
        } catch (...) 
        {
            REQUIRE( false );
        }

        // todo: check isn't meaningful enough
        REQUIRE( !was_init(SDL_INIT_EVERYTHING) );
    }

    SECTION( "single flag guard init" ) 
    {
        sdl2::init_guard guard(sdl2::init_flags::timer);
        REQUIRE( was_init(SDL_INIT_TIMER) );
    }

    SECTION( "initializer_list flag guard init" ) 
    {
        sdl2::init_guard guard{sdl2::init_flags::timer, sdl2::init_flags::events};

        REQUIRE( was_init(SDL_INIT_TIMER) );
        REQUIRE( was_init(SDL_INIT_EVENTS) );
    }
}