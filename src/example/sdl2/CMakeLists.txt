

add_executable (01_example_hello_sdl "${CMAKE_CURRENT_SOURCE_DIR}/01_example_hello_sdl.cxx" )
target_link_libraries (01_example_hello_sdl ${SDL2_LIBRARY})