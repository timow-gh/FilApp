set(GRAPHICS_HEADER
        include/Graphics/InputEvents/InputEventListener.hpp
        include/Graphics/InputEvents/InputEventDispatcher.hpp
        include/Graphics/InputEvents/MouseMoveEvent.hpp
        include/Graphics/InputEvents/MouseWheelEvent.hpp
        include/Graphics/InputEvents/PickRayEvent.hpp
        include/Graphics/InputEvents/RayPickEventListener.hpp
        include/Graphics/InputEvents/PickRayMoveEvent.hpp
        include/Graphics/InputEvents/RayPickEventDispatcher.hpp
        include/Graphics/InputEvents/MouseButtonEvent.hpp
        include/Graphics/Renderables/RendereableId.hpp
        include/Graphics/Renderables/PointRenderable.hpp
        include/Graphics/Renderables/LineRenderable.hpp
        include/Graphics/Renderables/TriangleRenderable.hpp
        include/Graphics/View.hpp
        include/Graphics/Viewport.hpp
        include/Graphics/Window.hpp
        include/Graphics/GraphicsApp.hpp
        include/Graphics/GraphicsController.hpp
        include/Graphics/RGBAColor.hpp
        include/Graphics/WindowConfig.hpp
        include/Graphics/AppConfig.hpp
        include/Graphics/Vertex.hpp
        include/Graphics/Vec.hpp
        )

set(GRAPHICS_SOURCES
        source/View.cpp
        source/InputEvents/InputEventListener.cpp
        source/GraphicsApp.cpp
        source/Window.cpp
        source/Vec.cpp)

add_library(graphics_app ${GRAPHICS_SOURCES} ${GRAPHICS_HEADER})
add_library(graphics::app ALIAS graphics_app)
set_target_properties(graphics_app
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME graphicsapp
        )

target_include_directories(graphics_app PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>)

target_link_libraries(graphics_app PUBLIC
        Core::Utils
        Core::Types)

include(GenerateExportHeader)
generate_export_header(graphics_app BASE_NAME GraphicsApp)

install(DIRECTORY "include/Graphics" DESTINATION "$CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS
        graphics_app
        EXPORT GraphicsAppTargetsExportSet
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

setupExportSetInstall("${PROJECT_NAME}" "GraphicsAppTargetsExportSet")
