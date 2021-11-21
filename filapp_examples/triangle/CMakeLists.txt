add_executable(filapp_example_triangle example_triangle.cpp)
set_target_properties(filapp_example_triangle
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME filappExampleTriangle)
target_link_libraries(filapp_example_triangle PRIVATE filapp::filapp)