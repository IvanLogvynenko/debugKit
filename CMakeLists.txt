cmake_minimum_required(VERSION 3.16)
project(debugKit)

add_library(debugKit
    src/Timer.cpp

    src/Logger.cpp
    src/LogMessage.cpp
    src/LoggerThread.cpp
    src/LoggerConfig.cpp
)
target_include_directories(debugKit PUBLIC include)

add_executable(main
    src/main.cpp
)
target_compile_definitions(main PRIVATE EXECUTABLE_NAME="TEST")
target_link_libraries(main PRIVATE debugKit)
target_include_directories(main PRIVATE include/)