build_resources()

set(FILAPP_SOURCES
        source/Application.cpp
        source/View.cpp
        source/Window.cpp
        source/WindowsNativeWindowHelper.cpp
        source/WindowsNativeWindowHelper.h
        )

set(FILAPP_PUBLIC_HEADERS
        include/FilApp/Application.h
        include/FilApp/View.h
        include/FilApp/ViewEvents.h
        include/FilApp/ViewListener.h
        include/FilApp/Window.h
        include/FilApp/WindowConfig.h
        include/FilApp/AppConfig.h
        include/FilApp/Renderable.h
        )

add_library(fil_app ${FILAPP_SOURCES} ${FILAPP_PUBLIC_HEADERS})
add_library(filapp::filapp ALIAS fil_app)
target_include_directories(fil_app
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>
        )
set_target_properties(fil_app
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME filapp)
target_link_libraries(fil_app
        PUBLIC
        filamentapp_sources
        filament
        sdl2
        math
        utils
        camutils
        )

include(GenerateExportHeader)
generate_export_header(fil_app BASE_NAME FilApp)
#        filamat
#        stb
#        assimp
#        filament-iblprefilter
#        getopt
#        imgui
#        filagui
#        image
#        geometry

install(DIRECTORY "include/FilApp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS
        fil_app
        filamentapp_sources
        filament
        sdl2
        math
        utils
        camutils
        EXPORT FilAppTargetsExportSet
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

setupExportSetInstall("${PROJECT_NAME}" "FilAppTargetsExportSet")