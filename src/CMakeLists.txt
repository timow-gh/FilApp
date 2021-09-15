build_resources()

set(FILAPP_PUBLIC_HEADERS
        include/FilApp/Application.hpp
        include/FilApp/FilAppView.hpp
        include/FilApp/ViewEvents.hpp
        include/FilApp/Window.hpp
        include/FilApp/WindowConfig.hpp
        include/FilApp/AppConfig.hpp
        include/FilApp/FilAppRenderable.hpp
        include/FilApp/Vertex.hpp
        include/FilApp/NativeWindowHelper.hpp
        include/FilApp/IController.hpp
        include/FilApp/IView.hpp
        include/FilApp/IModel.hpp
        include/FilApp/InputEvents.hpp
        include/FilApp/EvtPos.hpp
        include/FilApp/IInputListener.hpp
        include/FilApp/CameraMode.hpp
        include/FilApp/BackendMode.hpp
        include/FilApp/FilAppConversion.hpp
        include/FilApp/Renderable.hpp
        )

set(FILAPP_SOURCES
        source/Application.cpp
        source/FilAppView.cpp
        source/Window.cpp
        source/NativeWindowHelper.cpp
        source/FilAppRenderable.cpp
        source/FilAppConversion.cpp
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
        filament
        fil_app_sources
        sdl2
        math
        utils
        camutils
        )

if (MSVC)
    target_compile_definitions(fil_app PRIVATE -DMSVC)
else ()
    target_compile_definitions(fil_app PRIVATE -DLINUX)
endif ()

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
        fil_app_sources
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