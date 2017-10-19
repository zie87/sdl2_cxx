/**
* @file   error.hxx
* @Author: zie87
* @Date:   2017-10-09 21:33:01
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-19 03:42:17
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_CORE_ERROR_HXX
#define SDL2_CXX_CORE_ERROR_HXX

#include <SDL_error.h> 
#include <SDL_assert.h>

#include <string>
#include <stdexcept>

namespace sdl2
{

    inline std::string last_error() 
    {
        std::string result(SDL_GetError());
        SDL_ClearError();
        return result;
    }

    class exception : public std::runtime_error 
    {
    public:
        exception(): std::runtime_error(last_error()) {}
        exception(const std::string& str): std::runtime_error(str) {}
    };

    #define SDL2_CXX_CHECK(condition)                         \
    do {                                                      \
        if (!(condition)) throw exception();                  \
    } while (SDL_NULL_WHILE_LOOP_CONDITION);

}

#endif