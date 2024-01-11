cmake_minimum_required(VERSION 3.16)
project(debugKit)

include(default_headers.cmake)

set(debug_kit_headers 
    include/basic.hpp
    include/Timer.hpp
)

set(debug_kit_sources
    src/Timer/Timer.cpp
)

add_library(debugKit_basic 
    include/basic.hpp

    include/Timer.hpp
    src/Timer/Timer.cpp
)

add_library(debugKit 
    ${debug_kit_headers} 
    ${debug_kit_sources}
)

target_include_directories(debugKit_basic PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(debugKit PUBLIC ${PROJECT_SOURCE_DIR}/include/)