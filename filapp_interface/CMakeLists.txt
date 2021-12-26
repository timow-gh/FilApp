add_library(filapp_interfaces INTERFACE
        include/FilAppInterface/Renderables/RendereableId.hpp
        include/FilAppInterface/Renderables/PointRenderable.hpp
        include/FilAppInterface/Renderables/LineRenderable.hpp
        include/FilAppInterface/Renderables/TriangleRenderable.hpp
        include/FilAppInterface/InputEvents/InputEventListener.hpp
        include/FilAppInterface/InputEvents/InputEventDispatcher.hpp
        include/FilAppInterface/View.hpp
        include/FilAppInterface/Viewport.hpp
        include/FilAppInterface/Window.hpp
        include/FilAppInterface/Application.hpp
        include/FilAppInterface/WindowConfig.hpp
        include/FilAppInterface/AppConfig.hpp
        include/FilAppInterface/Vertex.hpp
        include/FilAppInterface/Vec.hpp
        include/FilAppInterface/InputEvents/MouseMoveEvent.hpp
        include/FilAppInterface/InputEvents/MouseWheelEvent.hpp
        include/FilAppInterface/InputEvents/KeyUpEvent.hpp
        include/FilAppInterface/InputEvents/KeyDownEvent.hpp
        include/FilAppInterface/InputEvents/PickRayEvent.hpp
        include/FilAppInterface/InputEvents/RayPickEventListener.hpp
        include/FilAppInterface/InputEvents/PickRayMoveEvent.hpp
        include/FilAppInterface/InputEvents/RayPickEventDispatcher.hpp
        include/FilAppInterface/InputEvents/DispatcherBase.hpp
        include/FilAppInterface/InputEvents/MouseButtonEvent.hpp
        )

add_library(filapp::interfaces ALIAS filapp_interfaces)
target_include_directories(filapp_interfaces
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        )
target_compile_features(filapp_interfaces INTERFACE cxx_std_17)
