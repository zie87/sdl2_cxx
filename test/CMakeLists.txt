
#set includes
include_directories ("${TEST_THIRD_PARTY_INCLUDE_PATH}")
add_definitions(-DTEST_DATA="${CMAKE_CURRENT_SOURCE_DIR}/test_data")

#set test sources
file (GLOB TEST_SRC_FILES_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cxx")
file (GLOB TEST_SRC_FILES_DETAIL "${CMAKE_CURRENT_SOURCE_DIR}/detail/*.cxx")
file (GLOB TEST_SRC_FILES_EVENTS "${CMAKE_CURRENT_SOURCE_DIR}/events/*.cxx")
file (GLOB TEST_SRC_FILES_TIME "${CMAKE_CURRENT_SOURCE_DIR}/time/*.cxx")
file (GLOB TEST_SRC_FILES_VIDEO "${CMAKE_CURRENT_SOURCE_DIR}/video/*.cxx")

if(SDL2_IMAGE_FOUND)
  file (GLOB TEST_SRC_FILES_IMAGE "${CMAKE_CURRENT_SOURCE_DIR}/image/*.cxx")
endif()

add_executable (${PROJECT_TEST_NAME}    "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx"
                                        "${TEST_SRC_FILES_CORE}"  
                                        "${TEST_SRC_FILES_DETAIL}" 
                                        "${TEST_SRC_FILES_EVENTS}" 
                                        "${TEST_SRC_FILES_TIME}"
                                        "${TEST_SRC_FILES_VIDEO}"

                                        # only if SDL2_image is availible
                                        "${TEST_SRC_FILES_IMAGE}"
    )
target_link_libraries (${PROJECT_TEST_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
enable_testing()

#parse catch tests
ParseAndAddCatchTests (${PROJECT_TEST_NAME})


# benchmark test vor event handling
add_executable (event_benchmark    "${CMAKE_CURRENT_SOURCE_DIR}/event_dispatch_timer.cxx" )
target_link_libraries (event_benchmark ${SDL2_LIBRARY} )