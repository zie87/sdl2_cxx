/**
* @file   init_test.cxx
* @Author: zie87
* @Date:   2017-10-09 21:23:08
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-13 14:33:17
**/

#include <sdl2_cxx/core/init.hxx>

#include <catch.hpp>

inline void expect_init(uint32_t flags) { REQUIRE(SDL_WasInit(flags) != SDL_FALSE); }
inline void expect_not_init(uint32_t flags = SDL_INIT_EVERYTHING) { REQUIRE(SDL_WasInit(flags) == SDL_FALSE);}

TEST_CASE( "init SDL2 system", "[core]" ) 
{
    // precheck that sdl wasn't initialised
    const auto start_flags = SDL_WasInit(0);
    SECTION( "default guard" ) 
    {
        try
        {
            sdl2::init_guard guard{};
            expect_init(SDL_INIT_EVERYTHING);
        } catch( const sdl2::exception& e )
        {
            REQUIRE( SDL_WasInit(0) == start_flags );
        } catch (...) 
        {
            REQUIRE( false );
        }
    }

    // check if SDL_Quit is called
    REQUIRE( SDL_WasInit(0) == start_flags );

    SECTION( "single flag guard init" ) 
    {
        sdl2::init_guard guard(sdl2::init_flags::timer);
        expect_init( SDL_INIT_TIMER );
    }

    // check if SDL_Quit is called
    REQUIRE( SDL_WasInit(0) == start_flags );

    SECTION( "initializer_list flag guard init" ) 
    {
        sdl2::init_guard guard{sdl2::init_flags::timer, sdl2::init_flags::events};

        expect_init(SDL_INIT_TIMER);
        expect_init(SDL_INIT_EVENTS);
    }

    // check if SDL_Quit is called
    REQUIRE( SDL_WasInit(0) == start_flags );
}