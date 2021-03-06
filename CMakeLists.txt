cmake_minimum_required(VERSION 3.9)

project(MsBoot CXX C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(unknown "Unknown" CACHE STRING "Unknown Tag" FORCE)

set (MSBOOT_BUILD_TESTS off)
if (BUILD_TESTS)
    set (MSBOOT_BUILD_TESTS on)
    unset (BUILD_TESTS CACHE)
endif ()

include(cmake/GitModules.cmake)
fetch_module_via_branch(lib/hal ${PROJECT_SOURCE_DIR}/lib/hal ${CMAKE_CURRENT_SOURCE_DIR} "master")

if (NOT ${MSBOOT_BUILD_TESTS})
    message (STATUS "Build: target")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(linker_scripts_directory "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts" CACHE STRING "Path to linker scripts")
    message (STATUS "Linker script directory: ${linker_scripts_directory}")

    add_subdirectory(lib)
    add_subdirectory(src)

elseif (${MSBOOT_BUILD_TESTS})
    message(STATUS "Build: UT")

    set(BOARD "x86_mock")
    set(CMAKE_CXX_STANDARD 17)

    project(MsBoot_UTs CXX C ASM)

    add_subdirectory(lib)
    add_subdirectory(src)
    add_subdirectory(test)
endif()

