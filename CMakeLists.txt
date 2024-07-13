cmake_minimum_required(VERSION 3.16)
project(debugKit)

include(default_headers.cmake)

add_library(debugKit
    src/Timer/Timer.cpp
)
target_include_directories(debugKit PUBLIC include)