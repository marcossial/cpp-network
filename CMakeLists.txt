cmake_minimum_required(VERSION 3.29)
project(TCP_Server)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE ws2_32)

add_executable(cliente cliente.cpp)
target_link_libraries(cliente PRIVATE ws2_32)