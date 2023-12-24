cmake_minimum_required(VERSION 3.16)
project(debugKit)

add_compile_definitions(FULL_LOGGING)
add_compile_definitions(DEBUG)
add_compile_definitions(ERROR)

add_executable(basicCase
    src/basic/main-basic.cpp)