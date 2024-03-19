cmake_minimum_required(VERSION 3.22)
project(EchoUDPServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HOST_NAME "localhost" CACHE STRING "Set the host name")
set(PORT "43845" CACHE STRING "Set the port")

add_definitions("-DHOST_NAME=\"${HOST_NAME}\"")
add_definitions("-DPORT=${PORT}")

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system network CONFIG REQUIRED)

add_executable(client MainClient.cpp)
add_executable(server MainServer.cpp)

target_link_libraries(client PRIVATE sfml-system sfml-network)
target_link_libraries(server PRIVATE sfml-system sfml-network)