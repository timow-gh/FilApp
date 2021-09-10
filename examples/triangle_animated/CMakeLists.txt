add_executable(triangle_animated triangle_animated.cpp)
set_target_properties(triangle_animated
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME triangleAnimated)
target_link_libraries(triangle_animated PRIVATE filapp::filapp)