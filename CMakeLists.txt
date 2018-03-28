cmake_minimum_required(VERSION 3.1)

project(sdl2_cxx C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(SDL2_CXX_MAJOR_VERSION 0)
set(SDL2_CXX_MINOR_VERSION 1)
set(SDL2_CXX_PATCH_VERSION 0)

set(SDL2_CXX_VERSION "${SDL2_CXX_MAJOR_VERSION}.${SDL2_CXX_MINOR_VERSION}.${SDL2_CXX_PATCH_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(USE_GCOV "Start coverage build" OFF)

include_directories(inc)

include (FindSDL2)
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIR})

include (FindSDL2_gfx)
find_package(SDL2_gfx)

include (FindSDL2_image)
find_package(SDL2_image)

include (FindSDL2_mixer)
find_package(SDL2_mixer)

include (FindSDL2_net)
find_package(SDL2_net)

include (FindSDL2_ttf)
find_package(SDL2_ttf)

find_package (OpenGL)

add_subdirectory (3rd EXCLUDE_FROM_ALL)

add_subdirectory(src)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(doc)
endif()

include(CTest)
enable_testing()