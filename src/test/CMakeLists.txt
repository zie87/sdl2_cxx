
#set includes
include_directories ("${TEST_THIRD_PARTY_INCLUDE_PATH}")
add_definitions(-DTEST_DATA="${CMAKE_CURRENT_SOURCE_DIR}/test_data")

#set test sources
file (GLOB TEST_SRC_FILES_CORE "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cxx")
file (GLOB TEST_SRC_FILES_DETAIL "${CMAKE_CURRENT_SOURCE_DIR}/detail/*.cxx")
file (GLOB TEST_SRC_FILES_EVENTS "${CMAKE_CURRENT_SOURCE_DIR}/events/*.cxx")
file (GLOB TEST_SRC_FILES_PLATFORM "${CMAKE_CURRENT_SOURCE_DIR}/platform/*.cxx")
file (GLOB TEST_SRC_FILES_TIME "${CMAKE_CURRENT_SOURCE_DIR}/time/*.cxx")
file (GLOB TEST_SRC_FILES_VIDEO "${CMAKE_CURRENT_SOURCE_DIR}/video/*.cxx")

set (PROJECT_TEST_LIBS ${SDL2_LIBRARY})

if(SDL2_IMAGE_FOUND)
  file (GLOB TEST_SRC_FILES_IMAGE "${CMAKE_CURRENT_SOURCE_DIR}/image/*.cxx")
  set (PROJECT_TEST_LIBS ${PROJECT_TEST_LIBS} ${SDL2_IMAGE_LIBRARY})
endif()

if(SDL2_TTF_FOUND)
  file (GLOB TEST_SRC_FILES_FONTS "${CMAKE_CURRENT_SOURCE_DIR}/fonts/*.cxx")
  set (PROJECT_TEST_LIBS ${PROJECT_TEST_LIBS} ${SDL2_TTF_LIBRARY})
endif()

if(SDL2_NET_FOUND)
  file (GLOB TEST_SRC_FILES_NET "${CMAKE_CURRENT_SOURCE_DIR}/net/*.cxx")
  set (PROJECT_TEST_LIBS ${PROJECT_TEST_LIBS} ${SDL2_NET_LIBRARY})
endif()

add_executable (${PROJECT_TEST_NAME}    "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx"
                                        
                                        "${TEST_SRC_FILES_CORE}"  
                                        "${TEST_SRC_FILES_DETAIL}" 
                                        "${TEST_SRC_FILES_EVENTS}"
                                        "${TEST_SRC_FILES_PLATFORM}"
                                        "${TEST_SRC_FILES_TIME}"
                                        "${TEST_SRC_FILES_VIDEO}"

                                        # only if SDL2_image is available
                                        "${TEST_SRC_FILES_IMAGE}"
                                        # only if SDL2_ttf is available
                                        "${TEST_SRC_FILES_FONTS}"
                                        # only if SDL2_ttf is available
                                        "${TEST_SRC_FILES_NET}"
    )
target_link_libraries (${PROJECT_TEST_NAME} ${PROJECT_TEST_LIBS} )
enable_testing()

#parse catch tests
ParseAndAddCatchTests (${PROJECT_TEST_NAME})


# benchmark test vor event handling
add_executable (event_benchmark    "${CMAKE_CURRENT_SOURCE_DIR}/event_dispatch_timer.cxx" )
target_link_libraries (event_benchmark ${SDL2_LIBRARY} )