
include_directories(${SDL2_MIXER_INCLUDE_DIR})

add_executable (01_mixer_player "${CMAKE_CURRENT_SOURCE_DIR}/01_mixer_player.cxx" )
target_link_libraries (01_mixer_player ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} )