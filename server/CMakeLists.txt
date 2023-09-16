cmake_minimum_required(VERSION 3.26)
project(server C)

set(CMAKE_C_STANDARD 11)
include_directories(include)

add_executable(server main.c)
add_subdirectory(src/file)
add_subdirectory(src/network)
add_subdirectory(src/work)
target_link_libraries(server work)
