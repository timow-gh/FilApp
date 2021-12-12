add_library(filapp_interfaces INTERFACE
        include/FilAppInterfaces/Renderables/RendereableId.hpp
        include/FilAppInterfaces/Renderables/PointRenderable.hpp
        include/FilAppInterfaces/Renderables/LineRenderable.hpp
        include/FilAppInterfaces/Renderables/TriangleRenderable.hpp
        include/FilAppInterfaces/InputEvents/InputEventListener.hpp
        include/FilAppInterfaces/InputEvents/InputEventDispatcher.hpp
        include/FilAppInterfaces/IView.hpp
        include/FilAppInterfaces/Viewport.hpp
        include/FilAppInterfaces/IWindow.hpp
        include/FilAppInterfaces/IApplication.hpp
        include/FilAppInterfaces/WindowConfig.hpp
        include/FilAppInterfaces/AppConfig.hpp
        include/FilAppInterfaces/Vertex.hpp
        include/FilAppInterfaces/Vec.hpp
        include/FilAppInterfaces/InputEvents/EvtPos.hpp include/FilAppInterfaces/InputEvents/MouseDownEvent.hpp include/FilAppInterfaces/InputEvents/MouseUpEvent.hpp include/FilAppInterfaces/InputEvents/MouseMoveEvent.hpp include/FilAppInterfaces/InputEvents/MouseWheelEvent.hpp include/FilAppInterfaces/InputEvents/KeyDownEvent.hpp include/FilAppInterfaces/InputEvents/KeyUpEvent.hpp include/FilAppInterfaces/InputEvents/PickRayEvent.hpp include/FilAppInterfaces/InputEvents/RayPickEventListener.hpp include/FilAppInterfaces/InputEvents/PickRayMoveEvent.hpp)

add_library(filapp::interfaces ALIAS filapp_interfaces)
target_include_directories(filapp_interfaces
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        )
target_compile_features(filapp_interfaces INTERFACE cxx_std_17)
