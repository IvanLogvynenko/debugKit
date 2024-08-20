cmake_minimum_required(VERSION 3.16)
project(debugKit)

add_library(debugKit
    src/Timer.cpp

    src/Logger.cpp
    src/LogMessage.cpp
    src/LoggerThread.cpp
    src/LoggerConfig.cpp
)
target_include_directories(debugKit PRIVATE include)
