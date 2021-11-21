add_executable(filapp_example_triangle_animated example_triangle_animated.cpp)
set_target_properties(filapp_example_triangle_animated
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME filappExampleTriangleAnimated)
target_link_libraries(filapp_example_triangle_animated PRIVATE filapp::filapp)