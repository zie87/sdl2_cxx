/**
* @file   interfaces.hxx
* @Author: zie87
* @Date:   2017-10-16 23:20:30
* @Last Modified by:   zie87
* @Last Modified time: 2017-10-16 23:31:49
*
* @brief  Brief description of file.
*
* Detailed description of file.
**/

#ifndef SDL2_CXX_DETAIL_INTERFACES_HXX
#define SDL2_CXX_DETAIL_INTERFACES_HXX

namespace sdl2
{
  namespace detail
  {
    class noncopyable
    {
      protected:
        noncopyable() {}
        virtual ~noncopyable() {}

        noncopyable( const noncopyable& ) = delete;
        noncopyable& operator=( const noncopyable& ) = delete;
    };
  }

} // namspace sdl2

#endif