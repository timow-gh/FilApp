#include "FlowMesh/Model.hpp"
#include "FlowMesh/Presenter.hpp"

namespace FlowMesh
{
Model::Model(Presenter* presenter)
{
    m_flowMeshPresenter = presenter;
}

std::vector<FGuid> Model::calcFGuids() const
{
    return m_geometryElements.getFGuidsFromMaps();
}

void Model::add(const FlowMeshSegments& flowMeshSegments)
{
    addImpl(flowMeshSegments);
}

void Model::add(const FlowMeshSphere& sphere)
{
    addImpl(sphere);
}

void Model::add(const FlowMeshCone& flowMeshCone)
{
    addImpl(flowMeshCone);
}

void Model::add(const FlowMeshCylinder& cylinder)
{
    addImpl(cylinder);
}

void Model::remove(const FGuid& fGuid)
{
    m_geometryElements.remove(fGuid);
    m_flowMeshPresenter->remove(fGuid);
}

void Model::setPosition(const FGuid& fGuid, LinAl::Vec3d& position)
{
    if (m_geometryElements.setPosition(fGuid, position))
        m_flowMeshPresenter->updatePosition(fGuid, position);
}

SnapGeometries Model::calcModelSnapGeometries() const
{
    SnapGeometries result{Geometry::Plane<double_t>{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D}};

    for (const auto& pair: m_geometryElements.getSegmentMap())
        for (const Geometry::Segment3d& segment: pair.second.getSegments())
            result.add(segment);

    for (const auto& pair: m_geometryElements.getSphereMap())
        result.add(pair.second.getSphere());

    return result;
}

} // namespace FlowMesh
