set(FLOWMESH_PUBLIC_HEADERS
        include/FlowMesh/GeometryElements/FlowMeshSphere.hpp
        include/FlowMesh/GeometryElements/FlowMeshCone.hpp
        include/FlowMesh/GeometryElements/FlowMeshSegments.hpp
        include/FlowMesh/GeometryElements/FlowMeshCylinder.hpp
        include/FlowMesh/GeometryElements/GeometryElements.hpp
        include/FlowMesh/GeometryElements/GeometryElementBase.hpp
        include/FlowMesh/Interactors/Interactor.hpp
        include/FlowMesh/Interactors/PlacingInteractor.hpp
        include/FlowMesh/Interactors/CameraInteractor.hpp
        include/FlowMesh/Interactors/InteractorCommands.hpp
        include/FlowMesh/Model.hpp
        include/FlowMesh/Controller.hpp
        include/FlowMesh/Presenter.hpp
        include/FlowMesh/FlowMeshGuid.hpp)

set(FLOWMESH_SOURCES
        source/GeometryElements/FlowMeshSegments.cpp
        source/GeometryElements/FlowMeshCylinder.cpp
        source/GeometryElements/FlowMeshSphere.cpp
        source/GeometryElements/FlowMeshCone.cpp
        source/GeometryElements/GeometryElements.cpp
        source/Interactors/PlacingInteractor.cpp
        source/Presenter.cpp
        source/Controller.cpp
        source/Model.cpp)

add_library(flow_mesh ${FLOWMESH_SOURCES} ${FLOWMESH_PUBLIC_HEADERS})
add_library(flowmesh::flowmesh ALIAS flow_mesh)
target_include_directories(flow_mesh
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>)
set_target_properties(flow_mesh
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME flowmesh)
target_link_libraries(flow_mesh
        PUBLIC
        graphics::interface
        LinAl::LinAl
        Geometry::Geometry
        CrossGuid::CrossGuid)

include(GenerateExportHeader)
generate_export_header(flow_mesh BASE_NAME FlowMesh)

add_executable(FlowMesh flowMesh.cpp)
target_link_libraries(FlowMesh PRIVATE flowmesh::flowmesh filapp::filapp)
