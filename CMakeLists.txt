cmake_minimum_required(VERSION 3.19)

include(FetchContent)
FetchContent_Declare(twCMakeUtils
        GIT_REPOSITORY https://github.com/timow-gh/twCMakeUtils.git
        GIT_TAG main)
FetchContent_GetProperties(twCMakeUtils)
set(lcs_twCMakeUtils "")
string(TOLOWER "twCMakeUtils" lcs_twCMakeUtils)
if (NOT ${lcs_twCMakeUtils}_POPULATED)
    FetchContent_Populate(twCMakeUtils)
    list(APPEND CMAKE_MODULE_PATH ${${lcs_twCMakeUtils}_SOURCE_DIR}/modules)
    include(CMakeHelperFunctions)
endif ()

project(FilApp
        VERSION 0.1.0
        LANGUAGES C CXX ASM)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(BuildResourceHelper)

if ((CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR))
    option(FilApp_BUILD_EXAMPLES "" ON)
else ()
    option(FilApp_BUILD_EXAMPLES "" OFF)
endif ()

preamble()
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE")

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    if (NOT BUILD_SHARED_LIBS)
        message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
        add_compile_options(
                $<$<CONFIG:>:/MT>
                $<$<CONFIG:Debug>:/MTd>
                $<$<CONFIG:Release>:/MT>
        )
    else ()
        add_compile_options(
                $<$<CONFIG:>:/MD>
                $<$<CONFIG:Debug>:/MDd>
                $<$<CONFIG:Release>:/MD>
        )
    endif ()
    # The ASM_MASM compiler id for this compiler is "MSVC", so fill out the runtime library table.
    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreaded "")
    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreadedDLL "")
    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreadedDebug "")
    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreadedDebugDLL "")
endif ()

add_subdirectory(dependencies)

add_subdirectory(filapp_interfaces)
add_subdirectory(filapp)

add_subdirectory(flowmesh)

if (FilApp_BUILD_EXAMPLES)
    add_subdirectory(filapp_examples)
endif ()
