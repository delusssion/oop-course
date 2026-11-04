cmake_minimum_required(VERSION 3.16)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(array_ops array_ops.cpp)

add_executable(lab1 main.cpp)
target_link_libraries(lab1 array_ops)
