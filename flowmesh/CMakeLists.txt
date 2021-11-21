set(FLOWMESH_PUBLIC_HEADERS
        include/FlowMesh/Interactors/Selection/OneWayToSelectMany.hpp
        include/FlowMesh/Interactors/PickingContext.hpp
        include/FlowMesh/FlowMeshModel.hpp
        include/FlowMesh/FlowMeshSphere.hpp
        include/FlowMesh/FlowMeshCone.hpp
        include/FlowMesh/FlowMeshController.hpp
        include/FlowMesh/FlowMeshPresenter.hpp
        include/FlowMesh/FlowMeshSegments.hpp
        include/FlowMesh/TypeId.hpp
        include/FlowMesh/FlowMeshCylinder.hpp)

set(FLOWMESH_SOURCES
        source/Interactors/PickingContext.cpp
        source/FlowMeshPresenter.cpp
        source/FlowMeshController.cpp
        source/FlowMeshModel.cpp
        source/FlowMeshSegments.cpp
        source/FlowMeshCylinder.cpp
        source/FlowMeshSphere.cpp
        source/FlowMeshCone.cpp
        )

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
        LinAl::LinAl
        Geometry::Geometry
        CrossGuid::CrossGuid
        )

include(GenerateExportHeader)
generate_export_header(flow_mesh BASE_NAME FlewMesh)


add_executable(FLowMesh main.cpp)
target_link_libraries(FLowMesh PRIVATE flowmesh::flowmesh)
