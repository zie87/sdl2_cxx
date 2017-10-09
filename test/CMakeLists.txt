

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}" )
add_executable(sdl2_cxx_tests   "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx"

                                "${CMAKE_CURRENT_SOURCE_DIR}/detail/bitmask_test.cxx"
    )

# target_link_libraries(sdl2_cxx_tests ${SDL2_LIBRARY})
add_test(sdl2_cxx_tests sdl2_cxx_tests)