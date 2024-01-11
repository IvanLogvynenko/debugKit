cmake_minimum_required(VERSION 3.16)
project(debugKit)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

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

add_library(debugKit ${debug_kit_headers} ${debug_kit_sources})

target_include_directories(debugKit_basic PUBLIC ${PROJECT_SOURCE_DIR}/include/)

install(DIRECTORY include/ DESTINATION include)
install(TARGETS debugKit_basic
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

target_include_directories(debugKit PUBLIC ${PROJECT_SOURCE_DIR}/include/)

install(DIRECTORY include/ DESTINATION include)
install(TARGETS debugKit
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)