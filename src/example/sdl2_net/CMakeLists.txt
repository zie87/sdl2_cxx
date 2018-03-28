
include_directories(${SDL2_NET_INCLUDE_DIR})

add_executable (01_net_tcp_client "${CMAKE_CURRENT_SOURCE_DIR}/01_net_tcp_client.cxx" )
target_link_libraries (01_net_tcp_client ${SDL2_LIBRARY} ${SDL2_NET_LIBRARY})

add_executable (01_net_tcp_server "${CMAKE_CURRENT_SOURCE_DIR}/01_net_tcp_server.cxx" )
target_link_libraries (01_net_tcp_server ${SDL2_LIBRARY} ${SDL2_NET_LIBRARY})