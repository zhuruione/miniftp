cmake_minimum_required(VERSION 3.26)
project(client C)

set(CMAKE_C_STANDARD 11)
include_directories(include)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(src/file)       #文件操作的一些函数
add_subdirectory(src/network)    #网络相关函数
add_subdirectory(src/shell)      #终端相关函数

add_executable(client main.c)
target_link_libraries(client PRIVATE shell)