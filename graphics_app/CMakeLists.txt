add_library(graphics_interface INTERFACE
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

target_include_directories(graphics_interface INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries(graphics_interface INTERFACE
        Core::Utils
        Core::Types)
add_library(graphics::interface ALIAS graphics_interface)
