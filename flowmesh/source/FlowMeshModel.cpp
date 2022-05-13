#include "FlowMesh/FlowMeshModel.hpp"
#include "FlowMesh/FlowMeshPresenter.hpp"
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGrid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <Geometry/Transformation/TransformCone.hpp>
#include <Geometry/Transformation/TransformCuboid.hpp>
#include <Geometry/Transformation/TransformCylinder.hpp>
#include <Geometry/Transformation/TransformSegment.hpp>
#include <Geometry/Transformation/TransformSphere.hpp>
#include <Geometry/Transformation/TransformVec.hpp>

namespace FlowMesh
{
FlowMeshModel::FlowMeshModel(ModelEventListener* modelEventListener)
{
    m_modelEventDispatcher.registerListener(modelEventListener);
}

void FlowMeshModel::remove(FGuid fGuid)
{
    m_geometryElements.remove(fGuid);
    m_modelEventDispatcher.dispatchRemove(fGuid);
}

void FlowMeshModel::update(const FGuid& guid)
{
    // clang-format off
    if (auto elem = get<FlowMeshCone>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<FlowMeshCuboid>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<FlowMeshCylinder>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<FlowMeshGrid>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<FlowMeshSegments>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<FlowMeshSphere>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    // clang-format on
}

void FlowMeshModel::setPosition(const FGuid& fGuid, LinAl::Vec3d& position)
{
    if (m_geometryElements.setPosition(fGuid, position))
        m_modelEventDispatcher.dispatchPositionChanged(PositionEvent{fGuid, position});
}

SnapGeometries FlowMeshModel::calcModelSnapGeometries() const
{
    SnapGeometries result{Geometry::Plane<double_t>{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D}};

    for (const auto& pair: m_geometryElements.getSegmentMap())
        if (pair.second.getIsSnapGeometry())
            for (const Geometry::Segment3d& segment: pair.second.getSegments())
                result.add(Geometry::transformation(segment, pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getSphereMap())
        if (pair.second.getIsSnapGeometry())
            result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                                pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getCylinderMap())
        if (pair.second.getIsSnapGeometry())
            result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                                pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getConeMap())
        if (pair.second.getIsSnapGeometry())
            result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                                pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getCuboidMap())
        if (pair.second.getIsSnapGeometry())
            result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                                pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getGridMap())
    {
        if (!pair.second.getIsSnapGeometry())
            continue;

        auto trafo = pair.second.getTransformation();

        for (const Geometry::Segment3d& segment: pair.second.getSegments())
            result.add(Geometry::transformation(segment, trafo));

        for (const LinAl::Vec3d& vec: pair.second.getIntersectionPoints())
            result.add(Geometry::transformation(vec, trafo));
    }

    return result;
}

} // namespace FlowMesh
