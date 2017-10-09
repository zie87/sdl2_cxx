cmake_minimum_required(VERSION 3.1)

project(sdl2_cxx C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(SDL2_CXX_MAJOR_VERSION 0)
set(SDL2_CXX_MINOR_VERSION 1)
set(SDL2_CXX_PATCH_VERSION 0)

set(SDL2_CXX_VERSION "${SDL2_CXX_MAJOR_VERSION}.${SDL2_CXX_MINOR_VERSION}.${SDL2_CXX_PATCH_VERSION}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(inc)

include (FindSDL2)
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIR})

include (FindSDL2_image)
find_package (SDL2_image REQUIRED)
include_directories (${SDL2_IMAGE_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(doc)
endif()
