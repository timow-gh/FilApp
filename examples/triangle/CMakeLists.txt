add_executable(triangle_example triangle_example.cpp)
set_target_properties(triangle_example
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME triangleExample)
target_link_libraries(triangle_example PRIVATE filapp::filapp)