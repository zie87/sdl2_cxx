
include_directories(${SDL2_NET_INCLUDE_DIR})

add_executable (tcp_client "${CMAKE_CURRENT_SOURCE_DIR}/tcp_client.cxx" )
target_link_libraries (tcp_client ${SDL2_LIBRARY} ${SDL2_NET_LIBRARY})

add_executable (tcp_server "${CMAKE_CURRENT_SOURCE_DIR}/tcp_server.cxx" )
target_link_libraries (tcp_server ${SDL2_LIBRARY} ${SDL2_NET_LIBRARY})