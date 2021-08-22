cmake_minimum_required(VERSION 3.19)

include(FetchContent)
FetchContent_Declare(   twCMakeUtils
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
        LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(BuildResourceHelper)

preamble()

add_subdirectory(dependencies)

build_resources()

add_executable(filapp
        main.cpp
        Application.cpp
        Application.h
        View.cpp View.h
        ViewEvents.h
        ViewListener.h
        Window.cpp
        Window.h
        WindowConfig.h
        WindowsNativeWindowHelper.cpp
        WindowsNativeWindowHelper.h
        AppConfig.h Renderable.h)
target_include_directories(filapp
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        )
target_link_libraries(filapp
        PRIVATE
        filamentapp_sources
        # filamentapp
#        assimp
        filament
#        filament-iblprefilter
        sdl2
#        stb
        math
#        filamat
        utils
#        getopt
#        imgui
#        filagui
#        image
        camutils
#        geometry
        )