add_library(filapp_interfaces INTERFACE
        include/FilAppInterfaces/Renderables/RendereableId.hpp
        include/FilAppInterfaces/Renderables/PointRenderable.hpp
        include/FilAppInterfaces/Renderables/LineRenderable.hpp
        include/FilAppInterfaces/Renderables/TriangleRenderable.hpp
        include/FilAppInterfaces/IView.hpp
        include/FilAppInterfaces/InputEvents/InputEvents.hpp
        include/FilAppInterfaces/InputEvents/IInputListener.hpp
        include/FilAppInterfaces/Viewport.hpp
        include/FilAppInterfaces/IWindow.hpp
        include/FilAppInterfaces/IApplication.hpp
        include/FilAppInterfaces/InputEvents/IInputEventDispatcher.hpp
        include/FilAppInterfaces/WindowConfig.hpp
        include/FilAppInterfaces/AppConfig.hpp
        include/FilAppInterfaces/Vertex.hpp
        include/FilAppInterfaces/Vec.hpp
        )

add_library(filapp::interfaces ALIAS filapp_interfaces)
target_include_directories(filapp_interfaces
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        )
target_compile_features(filapp_interfaces INTERFACE cxx_std_17)
