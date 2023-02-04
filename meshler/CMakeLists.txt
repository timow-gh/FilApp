set(MESHLER_PUBLIC_HEADERS
        include/Meshler/GeometryElements/MCone.hpp
        include/Meshler/GeometryElements/MConeTraits.hpp
        include/Meshler/GeometryElements/MCylinder.hpp
        include/Meshler/GeometryElements/MCylinderTraits.hpp
        include/Meshler/GeometryElements/MSegments.hpp
        include/Meshler/GeometryElements/MSphere.hpp
        include/Meshler/GeometryElements/MSphereTraits.hpp
        include/Meshler/GeometryElements/GeometryElements.hpp
        include/Meshler/GeometryElements/GeometryElementBase.hpp
        include/Meshler/GeometryElements/MCuboid.hpp
        include/Meshler/GeometryElements/MCuboidTraits.hpp
        include/Meshler/GeometryElements/MGrid.hpp
        include/Meshler/GeometryElements/MGeometryConfigBase.hpp
        include/Meshler/Interactors/CommandInteractor.hpp
        include/Meshler/Interactors/MeshlerCommands.hpp
        include/Meshler/Interactors/MeshlerCommandsKeyMap.hpp
        include/Meshler/Interactors/MElementPlacingInteractor.hpp
        include/Meshler/GeometryElements/SnapGeometries.hpp
        include/Meshler/Interactors/MGridInteractor.hpp
        include/Meshler/Interactors/Interactor.hpp
        include/Meshler/MController.hpp
        include/Meshler/MGuid.hpp
        include/Meshler/MModel.hpp
        include/Meshler/MModelEventDispatcher.hpp
        include/Meshler/PresenterConfig.hpp
        include/Meshler/MPresenter.hpp
        include/Meshler/LinAlConversion.hpp
        include/Meshler/MModelEventListener.hpp
        include/Meshler/PresenterUtils.hpp
        include/Meshler/RenderableBuilder.hpp)

set(MESHLER_SOURCES
        source/GeometryElements/MSegments.cpp
        source/GeometryElements/MCylinder.cpp
        source/GeometryElements/MSphere.cpp
        source/GeometryElements/MCone.cpp
        source/GeometryElements/MCuboid.cpp
        source/GeometryElements/MGrid.cpp
        source/Interactors/CommandInteractor.cpp
        source/Interactors/MGridInteractor.cpp
        source/Interactors/SnapGeometries.cpp
        source/Interactors/Interactor.cpp
        source/MPresenter.cpp
        source/RenderableBuilder.cpp
        source/MModel.cpp
        source/MController.cpp
        source/MModelEventListener.cpp)

add_library(meshler ${MESHLER_SOURCES} ${MESHLER_PUBLIC_HEADERS})
add_library(meshler::meshler ALIAS meshler)
target_include_directories(meshler
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source>)
set_target_properties(meshler
        PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        DEBUG_POSTFIX d
        LINKER_LANGUAGE CXX
        EXPORT_NAME meshler)
target_link_libraries(meshler
        PUBLIC
        Core::Types
        Core::Utils
        CrossGuid::CrossGuid
        LinAl::LinAl
        Geometry::Geometry
        filapp::filapp
        )

include(GenerateExportHeader)
generate_export_header(meshler BASE_NAME Meshler)

add_executable(MeshlerApp meshler.cpp)
target_link_libraries(MeshlerApp PRIVATE meshler::meshler)
