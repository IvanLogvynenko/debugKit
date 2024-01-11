include(FetchContent)
FetchContent_Declare(
        debugKit
        GIT_REPOSITORY https://github.com/IvanLogvynenko/debugKit
        GIT_TAG 8f106e29565acbeb5fa417e68cf9d919d0e991d2 # release 0.0.1.1
)
FetchContent_MakeAvailable(debugKit)
target_compile_options(debugKit PRIVATE -w)
target_include_directories(debugKit SYSTEM INTERFACE ${debugKit_SOURCE_DIR}/include/)
