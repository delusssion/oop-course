cmake_minimum_required(VERSION 3.20)
project(lab3 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(date_set date.cpp date_set.cpp)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 date_set)
