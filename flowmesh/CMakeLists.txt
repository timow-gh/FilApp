set(FLOWMESH_PUBLIC_HEADERS
        include/FlowMesh/FlowMesh.hpp)

set(FLOWMESH_SOURCES
        source/FlowMesh.cpp)

add_library(flow_mesh ${FLOWMESH_SOURCES} ${FLOWMESH_PUBLIC_HEADERS})
add_library(flowmesh::flowmesh ALIAS flow_mesh)
target_include_directories(flow_mesh
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>
        )
set_target_properties(flow_mesh
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME flowmesh
        )
target_link_libraries(flow_mesh
        PUBLIC
        filapp::filapp
        Geometry::Geometry
        )

include(GenerateExportHeader)
generate_export_header(flow_mesh BASE_NAME FlewMesh)


add_executable(FLowMeshApp main.cpp)
target_link_libraries(FLowMeshApp PRIVATE flowmesh::flowmesh)
