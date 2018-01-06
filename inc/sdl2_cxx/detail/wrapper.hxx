/**
 * @file   wrapper.hxx
 * @Author: zie87
 * @Date:   2017-10-16 23:07:04
 * @Last Modified by:   zie87
 * @Last Modified time: 2017-10-16 23:29:28
 *
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 **/

#ifndef SDL2_CXX_DETAIL_WRAPPER_HXX
#define SDL2_CXX_DETAIL_WRAPPER_HXX

#include <memory>

namespace sdl2
{
  namespace detail
  {

    template <typename T, void (*ReleaseFunction)(T*)>
    struct sdl_deleter
    {
      void operator()(T* ptr) const { ReleaseFunction(ptr); }
    };

    template <typename T, void (*ReleaseFunction)(T*)>
    using sdl_ptr = std::unique_ptr<T, sdl_deleter<T, ReleaseFunction>>;

  } // namespace detail
} // namespace sdl2

#endif