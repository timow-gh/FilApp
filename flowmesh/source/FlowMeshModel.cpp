#include "FlowMesh/FlowMeshModel.hpp"
#include "FlowMesh/FlowMeshPresenter.hpp"

namespace FlowMesh
{
void FlowMeshModel::setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter)
{
    m_flowMeshPresenter = flowMeshPresenter;
}
std::vector<TypeId> FlowMeshModel::calcTypeIds() const
{
    return m_geometryElements.getTypeIdsFromMaps();
}
void FlowMeshModel::addSegments(const FlowMeshSegments& flowMeshSegments)
{
    if (m_geometryElements.add(flowMeshSegments))
        m_flowMeshPresenter->add(flowMeshSegments);
}
void FlowMeshModel::addSphere(const FlowMeshSphere& sphere)
{
    if (m_geometryElements.add(sphere))
        m_flowMeshPresenter->add(sphere);
}
void FlowMeshModel::addCone(const FlowMeshCone& flowMeshCone)
{
    if (m_geometryElements.add(flowMeshCone))
        m_flowMeshPresenter->add(flowMeshCone);
}
void FlowMeshModel::addCylinder(const FlowMeshCylinder& cylinder)
{
    if (m_geometryElements.add(cylinder))
        m_flowMeshPresenter->add(cylinder);
}
void FlowMeshModel::remove(const TypeId& typeId)
{
    m_geometryElements.remove(typeId);
    m_flowMeshPresenter->remove(typeId);
}
} // namespace FlowMesh
