set(FILAPP_PUBLIC_HEADERS
        include/FilApp/FilApplication.hpp
        include/FilApp/FilAppCameraView.hpp
        include/FilApp/FilAppConversion.hpp
        include/FilApp/FilAppGuiContext.hpp
        include/FilApp/FilAppWindow.hpp
        include/FilApp/FilAppRenderable.hpp
        include/FilApp/FilAppRenderableCreator.hpp
        include/FilApp/FilAppScene.hpp
        include/FilApp/IOHelper.hpp
        )

set(FILAPP_SOURCES
        source/FilAppCameraView.cpp
        source/FilAppConversion.cpp
        source/FilAppGuiContext.cpp
        source/FilApplication.cpp
        source/FilAppWindow.cpp
        source/NativeWindowHelper.hpp
        source/NativeWindowHelper.cpp
        source/FilAppRenderableBuffers.cpp
        source/FilAppRenderableBuffers.hpp
        source/FilAppRenderableCreator.cpp
        source/FilAppScene.cpp)

add_library(fil_app ${FILAPP_SOURCES} ${FILAPP_PUBLIC_HEADERS})
add_library(filapp::filapp ALIAS fil_app)
target_include_directories(fil_app
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/filapp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>
        )
set_target_properties(fil_app
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME filapp
        )
target_link_libraries(fil_app
        PUBLIC
        Core::Types
        Core::Utils
        graphics::app
        fil_app_sources
        Filament::filament
        Filament::filagui
        Filament::sdl2
        Filament::math
        Filament::utils
        Filament::camutils
        )

if (MSVC)
    target_compile_definitions(fil_app PRIVATE -DMSVC)
else ()
    target_compile_definitions(fil_app PRIVATE -DLINUX)
endif ()

include(GenerateExportHeader)
generate_export_header(fil_app BASE_NAME FilApp)

build_resources()

if (${PROJECT_NAME}_INSTALL)
    install(DIRECTORY "include/FilApp" DESTINATION "$CMAKE_INSTALL_INCLUDEDIR}")
    install(TARGETS
            fil_app
            fil_app_sources
            EXPORT ${project_export_set_name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            INCLUDES DESTINATION
            ${CMAKE_INSTALL_INCLUDEDIR}
            ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
endif ()
