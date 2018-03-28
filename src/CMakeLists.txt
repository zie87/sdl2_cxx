
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
    include(CodeCoverage)
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall --coverage")
    set(LCOV_REMOVE_EXTRA '${CMAKE_SOURCE_DIR}/3rd/*' '${CMAKE_CURRENT_SOURCE_DIR}/test/*')
    setup_target_for_coverage(test_coverage ${PROJECT_TEST_NAME} coverage)
endif()

add_subdirectory(examples)
add_subdirectory(test)