add_executable(example_points example_points.cpp)
set_target_properties(triangle_example
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME examplePoints)
target_link_libraries(example_points PRIVATE FilApp::FilApp)