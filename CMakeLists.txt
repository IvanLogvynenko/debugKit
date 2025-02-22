cmake_minimum_required(VERSION 3.16)
project(debugKit VERSION 1.0.0)

add_library(debugKit
    src/Timer.cpp

    src/Logger.cpp
    src/LogMessage.cpp
    src/LoggerThread.cpp
    src/LoggerConfig.cpp
)
target_include_directories(debugKit PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(GNUInstallDirs)
install(TARGETS debugKit
        EXPORT debugKitTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/debugKit)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/debugKitConfig.cmake"
    COMPATIBILITY SameMajorVersion
)
install(EXPORT debugKitTargets
        FILE debugKitTargets.cmake
        NAMESPACE debugKit::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/debugKit
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/debugKitConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/debugKit
)

if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt")
    add_custom_target(uninstall
        COMMAND xargs rm < "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt"
        COMMENT "Удаление установленных файлов"
    )
else()
    add_custom_target(uninstall
        COMMAND echo "install_manifest.txt not found. Uninstall impossible."
    )
endif()
