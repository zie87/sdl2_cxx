
#configure variables
set (TEST_APP_NAME "sdl2_cxx_tests")

#set includes
include_directories ("${TEST_THIRD_PARTY_INCLUDE_PATH}")

#set test sources
file (GLOB TEST_SRC_FILES_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cxx")
file (GLOB TEST_SRC_FILES_DETAIL "${CMAKE_CURRENT_SOURCE_DIR}/detail/*.cxx")
file (GLOB TEST_SRC_FILES_TIME "${CMAKE_CURRENT_SOURCE_DIR}/time/*.cxx")
file (GLOB TEST_SRC_FILES_VIDEO "${CMAKE_CURRENT_SOURCE_DIR}/video/*.cxx")

#set target executable
add_executable (${TEST_APP_NAME}    "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx"
                                    "${TEST_SRC_FILES_CORE}"  
                                    "${TEST_SRC_FILES_DETAIL}"  
                                    "${TEST_SRC_FILES_TIME}"
                                    "${TEST_SRC_FILES_VIDEO}"
    )

#add the library
target_link_libraries (${TEST_APP_NAME} ${SDL2_LIBRARY} )

# Turn on CMake testing capabilities
enable_testing()

#parse catch tests
ParseAndAddCatchTests (${TEST_APP_NAME})