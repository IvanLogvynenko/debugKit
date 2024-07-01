include(FetchContent)
FetchContent_Declare(
        debugKit
        GIT_REPOSITORY https://github.com/IvanLogvynenko/debugKit
        GIT_TAG 3ebfcc182ab61b9df72fc5a82f61f6c351e86cf9 # release 0.0.1.1
)
FetchContent_MakeAvailable(debugKit)
target_compile_options(debugKit PRIVATE -w)
target_include_directories(debugKit SYSTEM INTERFACE ${debugKit_SOURCE_DIR}/include/)
