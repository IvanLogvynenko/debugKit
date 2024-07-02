cmake_minimum_required(VERSION 3.16)
project(debugKit)

include(default_headers.cmake)

add_library(debugKit
    src/Timer/Timer.cpp
)

target_include_directories(debugKit PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install target and export configuration
install(TARGETS debugKit
    EXPORT debugKitConfig
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT debugKitConfig
    FILE debugKitConfig.cmake
    NAMESPACE debugKit::
    DESTINATION lib/cmake/debugKit
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)