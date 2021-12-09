cmake_minimum_required(VERSION 3.20)

project(Google_tests)

add_subdirectory(../vendor/googletest lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run BasicTests.cpp)

target_link_libraries(Google_Tests_run Interpreter_lib)
target_link_libraries(Google_Tests_run gtest gtest_main)
