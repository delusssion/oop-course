cmake_minimum_required(VERSION 3.20)
project(lab3 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(date_set date.cpp date_set.cpp)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 date_set)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab3_tests tests.cpp)
target_link_libraries(lab3_tests date_set GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab3_tests)
