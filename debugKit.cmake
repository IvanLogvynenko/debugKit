include(FetchContent)
FetchContent_Declare(
        debugKit
        GIT_REPOSITORY https://github.com/IvanLogvynenko/debugKit
        GIT_TAG main
)
FetchContent_MakeAvailable(debugKit)
target_compile_options(debugKit PRIVATE -w)
target_include_directories(debugKit SYSTEM INTERFACE ${debugKit_SOURCE_DIR}/include/)
target_compile_definitions(debugKit PRIVATE EXECUTABLE_NAME="Set your name in debugKit.cmake")
