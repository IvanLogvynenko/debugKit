include(FetchContent)
FetchContent_Declare(
        debugKit
        GIT_REPOSITORY https://github.com/IvanLogvynenko/debugKit
        GIT_TAG 9ce6f71e4cbd3f28cdd970927f3968b67e3b637b # release 0.0.1 
)
FetchContent_GetProperties(debugKit)
if (NOT azure-storage-lite_POPULATED)
    FetchContent_Populate(debugKit)
    add_subdirectory(${debugKit_SOURCE_DIR} ${debugKit_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
target_compile_options(debugKit PRIVATE -w)
target_include_directories(debugKit SYSTEM INTERFACE ${debugKit_SOURCE_DIR}/include/)
