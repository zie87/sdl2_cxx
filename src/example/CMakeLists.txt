
include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(sdl2)

if(SDL2_NET_FOUND)
  add_subdirectory(sdl2_net)
endif()