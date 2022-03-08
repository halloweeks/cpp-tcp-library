cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(socket VERSION 1.0)

add_executable(server1.exe server1.cpp)
add_executable(server2.exe server2.cpp)
add_executable(client.exe client.cpp)

target_link_libraries(server1.exe pthread)
