#include "FlowMesh/FlowMeshModel.hpp"
#include "FlowMesh/FlowMeshPresenter.hpp"
#include <Geometry/Cone.hpp>
#include <Geometry/Transformation/TransformCone.hpp>
#include <Geometry/Transformation/TransformCuboid.hpp>
#include <Geometry/Transformation/TransformCylinder.hpp>
#include <Geometry/Transformation/TransformSegment.hpp>
#include <Geometry/Transformation/TransformVec.hpp>

namespace FlowMesh
{
FlowMeshModel::FlowMeshModel(ModelEventListener* modelEventListener)
{
    m_modelEventDispatcher.registerListener(modelEventListener);
}

void FlowMeshModel::remove(const FGuid& fGuid)
{
    m_geometryElements.remove(fGuid);
    m_modelEventDispatcher.dispatchRemove(fGuid);
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
        for (const Geometry::Segment3d& segment: pair.second.getSegments())
            result.add(Geometry::transformation(segment, pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getSphereMap())
        result.add(pair.second.getGeometryElement(), pair.second.getTransformation());

    for (const auto& pair: m_geometryElements.getCylinderMap())
        result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                            pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getConeMap())
        result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                            pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getCuboidMap())
        result.add(Geometry::transformation(pair.second.getGeometryElement(),
                                            pair.second.getTransformation()));

    for (const auto& pair: m_geometryElements.getGridMap())
    {
        auto trafo = pair.second.getTransformation();

        for (const Geometry::Segment3d& segment: pair.second.getSegments())
            result.add(Geometry::transformation(segment, trafo));

        for (const LinAl::Vec3d& vec: pair.second.getIntersectionPoints())
            result.add(Geometry::transformation(vec, trafo));
    }

    return result;
}

} // namespace FlowMesh
