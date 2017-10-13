/**
* @file   init_test.cxx
* @Author: zie87
* @Date:   2017-10-09 21:23:08
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-13 15:07:04
**/

#include <sdl2_cxx/core/init.hxx>

#include <catch.hpp>

inline void expect_init(uint32_t flags) { REQUIRE(SDL_WasInit(0) & flags); }

TEST_CASE( "init SDL2 system", "[core]" ) 
{
    // precheck that sdl wasn't initialised
    SECTION( "default guard" ) 
    {
        try
        {
            sdl2::init_guard guard{};
            expect_init(SDL_INIT_EVERYTHING);
        } catch( const sdl2::exception& e )
        {
            // todo: check isn't meaningful enough
            expect_not_init(SDL_INIT_EVERYTHING);
        } catch (...) 
        {
            REQUIRE( false );
        }
    }

    SECTION( "single flag guard init" ) 
    {
        sdl2::init_guard guard(sdl2::init_flags::timer);
        expect_init( SDL_INIT_TIMER );
    }

    SECTION( "initializer_list flag guard init" ) 
    {
        sdl2::init_guard guard{sdl2::init_flags::timer, sdl2::init_flags::events};

        expect_init(SDL_INIT_TIMER);
        expect_init(SDL_INIT_EVENTS);
    }
}