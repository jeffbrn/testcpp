cmake_minimum_required(VERSION 3.16)
project(MultiTest VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(matrix)
include_directories(matrix/include)

add_executable(MultiTest main.cpp)

target_link_libraries(MultiTest matrix_lib)