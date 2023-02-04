cmake_minimum_required(VERSION 3.21)

include(FetchContent)
FetchContent_Declare(twCMakeUtils
        GIT_REPOSITORY https://github.com/timow-gh/twCMakeUtils.git
        GIT_TAG main)
FetchContent_GetProperties(twCMakeUtils)
set(lcs_twCMakeUtils "")
string(TOLOWER "twCMakeUtils" lcs_twCMakeUtils)
if (NOT ${lcs_twCMakeUtils}_POPULATED)
    FetchContent_Populate(twCMakeUtils)

    # Adding CPM to the project
    set(utils_cmake_modules_path ${${lcs_twCMakeUtils}_SOURCE_DIR}/modules)
    include(${utils_cmake_modules_path}/CPM.cmake)
    if (NOT CPM_SOURCE_CACHE AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CPMSourceVariable.cmake")
        include(CPMSourceVariable.cmake)
    endif ()

    if (NOT CPM_SOURCE_CACHE)
        message(AUTHOR_WARNING "CPM_SOURCE_CACHE not set. The source files are downloaded for every build. This is not recommended.
        Set the CPM_SOURCE_CACHE variable to a directory of your choice to cache the cloned git repositories.
        Set the CPM_SOURCE_CACHE variable in CPMSourceVariable.cmake to keep your paths private.")
    endif ()

    list(APPEND CMAKE_MODULE_PATH ${utils_cmake_modules_path})
endif ()

project(Meshler
        VERSION 0.1.0
        LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(BuildResourceHelper)
include(setup_export_set_installation)
include(project_preamble)
project_preamble()

find_package(filament CONFIG REQUIRED)

#if (BUILD_SHARED_LIBS)
#    message(AUTHOR_ERROR "BUILD_SHARED_LIBS is not by google/filament. Please set BUILD_SHARED_LIBS to OFF.")
#endif ()

#find_program(CCACHE_PROGRAM ccache)
#if(CCACHE_PROGRAM)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
#
#    set(C_LAUNCHER   "${CCACHE_PROGRAM}")
#    set(CXX_LAUNCHER "${CCACHE_PROGRAM}")
#
#    configure_file(cmake/launch-c.in   launch-c)
#    configure_file(cmake/launch-cxx.in launch-cxx)
#
#    execute_process(COMMAND chmod a+rx
#            "${CMAKE_BINARY_DIR}/launch-c"
#            "${CMAKE_BINARY_DIR}/launch-cxx"
#            )
#endif()

#if (MSVC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE")
#
#    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#    if (NOT BUILD_SHARED_LIBS)
#        add_compile_options(
#                $<$<CONFIG:>:/MT>
#                $<$<CONFIG:Debug>:/MTd>
#                $<$<CONFIG:Release>:/MT>
#        )
#    endif ()
#    # The ASM_MASM compiler id for this compiler is "MSVC", so fill out the runtime library table.
#    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreaded "")
#    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreadedDLL "")
#    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreadedDebug "")
#    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OPTIONS_MSVC_RUNTIME_LIBRARY_MultiThreadedDebugDLL "")
#endif ()

#find_program(CCACHE_PROGRAM ccache)
#if(CCACHE_PROGRAM)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
#
#    set(C_LAUNCHER   "${CCACHE_PROGRAM}")
#    set(CXX_LAUNCHER "${CCACHE_PROGRAM}")
#
#    configure_file(cmake/launch-c.in   launch-c)
#    configure_file(cmake/launch-cxx.in launch-cxx)
#
#    execute_process(COMMAND chmod a+rx
#            "${CMAKE_BINARY_DIR}/launch-c"
#            "${CMAKE_BINARY_DIR}/launch-cxx"
#            )
#endif()

option(${PROJECT_NAME}_INSTALL "" ON)

#option(USE_SCCACHE "Use sccache" OFF)
#if (ENABLE_DEVELOPER_MODE)
#    option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
#    option(${PROJECT_NAME}_STATIC_ANALYSIS "" ON)
#    option(${PROJECT_NAME}_TESTS "" ON)
#    option(${PROJECT_NAME}_BUILD_EXAMPLES "" ON)
#
#    # check if the file CPMSourceVariable.cmake exists in project root
#    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CPMSourceVariable.cmake")
#        include(CPMSourceVariable.cmake)
#    else ()
#        message(AUTHOR_WARNING "CPMSourceVariable.cmake not found. Set the CPM_SOURCE_CACHE variable to a directory to cache the git clones or create a the CPMSourceVariable.cmake file in the project root. Set the CPM_SOURCE_CACHE variable in CPMSourceVariable.cmake to keep your paths private.")
#    endif ()
#
#    if (NOT CPM_SOURCE_CACHE)
#        message(AUTHOR_WARNING "CPM_SOURCE_CACHE not set. The source files are downloaded for each project.")
#    endif ()
#else ()
#    option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
#    option(${PROJECT_NAME}_STATIC_ANALYSIS "" OFF)
#    option(${PROJECT_NAME}_TESTS "" OFF)
#    option(${PROJECT_NAME}_BUILD_EXAMPLES "" OFF)
#endif ()
#
#if (NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja")
#    message(AUTHOR_WARNING "sccache is only testet with the generator Ninja. Setting USE_SCCACHE to OFF.")
#    set(USE_SCCACHE OFF CACHE BOOL "" FORCE)
#endif ()
#
#if (USE_SCCACHE)
#    find_program(CCACHE_PROGRAM sccache)
#    message(STATUS "CCACHE_PROGRAM=${CCACHE_PROGRAM}")
#    if (CCACHE_PROGRAM)
#        # Makefile Generators and the Ninja generator prefix compiler commands with the given launcher command line.
#        # This is intended to allow launchers to intercept build problems with high granularity. Other generators ignore
#        # this property because their underlying build systems provide no hook to wrap individual commands with a launcher.
#        set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
#        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
#    else ()
#        message(FATAL_ERROR "sccache not found. Please install it or disable USE_SCCACHE")
#    endif ()
#
#    include(cmake/sccache_setup.cmake)
#    fix_msvc_ninja_compile_flags()
#endif ()
#
#message(STATUS "USE_SCCACHE: ${USE_SCCACHE}")
#message(STATUS "${PROJECT_NAME}_WARNINGS_AS_ERRORS: ${${PROJECT_NAME}_WARNINGS_AS_ERRORS}")
#message(STATUS "${PROJECT_NAME}_STATIC_ANALYSIS: ${${PROJECT_NAME}_STATIC_ANALYSIS}")

add_subdirectory(dependencies)

set(project_export_set_name "${PROJECT_NAME}TargetsExportSet")

add_subdirectory(graphics_app)
add_subdirectory(filapp)
if (${PROJECT_NAME}_BUILD_EXAMPLES)
    add_subdirectory(filapp_examples)
endif ()
add_subdirectory(meshler)

setup_export_set_installation(
        ${PROJECT_NAME}
        "${project_export_set_name}"
        "${PROJECT_NAME}Config.cmake.in"
        ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH}
)


