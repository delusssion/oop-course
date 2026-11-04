cmake_minimum_required(VERSION 3.16)
project(lab2 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(my_string my_string.cpp)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 my_string)
