

add_executable (01_core_hello_sdl "${CMAKE_CURRENT_SOURCE_DIR}/01_core_hello_sdl.cxx" )
target_link_libraries (01_core_hello_sdl ${SDL2_LIBRARY})

if(OPENGL_FOUND)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable (02_core_opengl "${CMAKE_CURRENT_SOURCE_DIR}/02_core_opengl.cxx" )
target_link_libraries (02_core_opengl ${SDL2_LIBRARY} ${OPENGL_LIBRARY})

  if (GLEW_FOUND)
      include_directories($(GLEW_INCLUDE_DIRS))
      add_executable (03_core_modern_opengl "${CMAKE_CURRENT_SOURCE_DIR}/03_core_modern_opengl.cxx" )
      target_link_libraries (03_core_modern_opengl ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})
  endif()

endif()