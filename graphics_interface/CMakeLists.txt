add_library(graphics_interface INTERFACE
        include/GraphicsInterface/InputEvents/InputEventListener.hpp
        include/GraphicsInterface/InputEvents/InputEventDispatcher.hpp
        include/GraphicsInterface/InputEvents/MouseMoveEvent.hpp
        include/GraphicsInterface/InputEvents/MouseWheelEvent.hpp
        include/GraphicsInterface/InputEvents/KeyUpEvent.hpp
        include/GraphicsInterface/InputEvents/KeyDownEvent.hpp
        include/GraphicsInterface/InputEvents/PickRayEvent.hpp
        include/GraphicsInterface/InputEvents/RayPickEventListener.hpp
        include/GraphicsInterface/InputEvents/PickRayMoveEvent.hpp
        include/GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp
        include/GraphicsInterface/InputEvents/DispatcherBase.hpp
        include/GraphicsInterface/InputEvents/MouseButtonEvent.hpp
        include/GraphicsInterface/Renderables/RendereableId.hpp
        include/GraphicsInterface/Renderables/PointRenderable.hpp
        include/GraphicsInterface/Renderables/LineRenderable.hpp
        include/GraphicsInterface/Renderables/TriangleRenderable.hpp
        include/GraphicsInterface/View.hpp
        include/GraphicsInterface/Viewport.hpp
        include/GraphicsInterface/Window.hpp
        include/GraphicsInterface/Application.hpp
        include/GraphicsInterface/RGBAColor.hpp
        include/GraphicsInterface/WindowConfig.hpp
        include/GraphicsInterface/AppConfig.hpp
        include/GraphicsInterface/Vertex.hpp
        include/GraphicsInterface/Vec.hpp
        )

add_library(graphics::interface ALIAS graphics_interface)
target_include_directories(graphics_interface INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_compile_features(graphics_interface INTERFACE cxx_std_17)
