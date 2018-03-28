
add_definitions(-DEXAMPLE_DATA="${CMAKE_CURRENT_SOURCE_DIR}/data")
include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(sdl2)

if(SDL2_MIXER_FOUND)
  add_subdirectory(sdl2_mixer)
endif()

if(SDL2_NET_FOUND)
  add_subdirectory(sdl2_net)
endif()