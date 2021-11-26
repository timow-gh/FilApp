add_library(filapp_interfaces INTERFACE
        IView.hpp
        InputEvents.hpp
        IInputListener.hpp
        Viewport.hpp
        IWindow.hpp
        IApplication.hpp
        IInputEventDispatcher.hpp
        WindowConfig.hpp
        AppConfig.hpp
        )

add_library(filapp::interfaces ALIAS filapp_interfaces)
target_include_directories(filapp_interfaces
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/filapp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>
        )

target_compile_features(fil_app PUBLIC cxx_std_17)
