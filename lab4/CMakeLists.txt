cmake_minimum_required(VERSION 3.20)
project(lab4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

option(USE_SANITIZERS "Build with address and undefined sanitizers" OFF)
if(USE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined -g)
    add_link_options(-fsanitize=address,undefined)
endif()

add_library(bodies
    celestial_body.cpp
    star.cpp
    planet.cpp
    moon.cpp
    body_collection.cpp
)

add_executable(lab4 main.cpp)
target_link_libraries(lab4 bodies)

include(FetchContent)
