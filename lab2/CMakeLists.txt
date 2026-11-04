cmake_minimum_required(VERSION 3.16)
project(lab2 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(my_string my_string.cpp)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 my_string)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab2_tests tests.cpp)
target_link_libraries(lab2_tests my_string GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab2_tests)
