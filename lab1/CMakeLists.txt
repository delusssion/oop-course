cmake_minimum_required(VERSION 3.16)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(array_ops array_ops.cpp)

add_executable(lab1 main.cpp)
target_link_libraries(lab1 array_ops)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab1_tests test_variant.cpp)
target_link_libraries(lab1_tests array_ops GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab1_tests)
