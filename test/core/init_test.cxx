/**
* @file   init_test.cxx
* @Author: zie87
* @Date:   2017-10-09 21:23:08
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-09 22:23:19
**/

#include <sdl2_cxx/core/init.hxx>

#include <catch.hpp>

TEST_CASE( "init SDL2 system", "[core]" ) 
{
    // precheck that sdl wasn't initialised
    REQUIRE( SDL_WasInit(0) == 0 );
    SECTION( "default guard" ) 
    {
        sdl2::init_guard guard{};

        REQUIRE( SDL_WasInit(0) != 0 );
        REQUIRE( SDL_WasInit(0) == SDL_INIT_EVERYTHING );
    }

    // check if SDL_Quit is called
    REQUIRE( SDL_WasInit(0) == 0 );

    SECTION( "single flag guard init" ) 
    {
        sdl2::init_guard guard(sdl2::init_flags::timer);

        REQUIRE( SDL_WasInit(0) != 0 );
        REQUIRE( SDL_WasInit(0) == SDL_INIT_TIMER );
    }

    // check if SDL_Quit is called
    REQUIRE( SDL_WasInit(0) == 0 );

    SECTION( "initializer_list flag guard init" ) 
    {
        sdl2::init_guard guard{sdl2::init_flags::timer, sdl2::init_flags::events};

        REQUIRE( SDL_WasInit(0) != 0 );
        REQUIRE( (SDL_WasInit(0) & SDL_INIT_TIMER) );
        REQUIRE( (SDL_WasInit(0) & SDL_INIT_EVENTS) );
    }

    // check if SDL_Quit is called
    REQUIRE( SDL_WasInit(0) == 0 );
}