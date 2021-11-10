cmake_minimum_required(VERSION 3.20)
project(Custom_Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(Interpreter main.cpp)
include_directories(src)
add_subdirectory(src)

target_link_libraries(Interpreter Interpreter_lib)

add_subdirectory(Tests)