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


set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CodeCoverage)
  set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
  set(LCOV_REMOVE_EXTRA "'test/*'" "'3rd/*'")
  setup_target_for_coverage(test_coverage ${PROJECT_TEST_NAME} coverage)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories(inc)

include (FindSDL2)
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIR})

add_subdirectory (3rd EXCLUDE_FROM_ALL)

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(doc)
endif()

include(CTest)
enable_testing()