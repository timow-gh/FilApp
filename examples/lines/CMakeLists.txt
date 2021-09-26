add_executable(example_lines example_lines.cpp)
set_target_properties(example_lines
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME exampleLines)
target_link_libraries(example_lines PRIVATE filapp::filapp)