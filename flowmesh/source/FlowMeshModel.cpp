#include "FlowMesh/FlowMeshModel.hpp"
#include "FlowMesh/FlowMeshPresenter.hpp"

namespace FlowMesh
{
void FlowMeshModel::setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter)
{
    m_flowMeshPresenter = flowMeshPresenter;
}
std::vector<FGuid> FlowMeshModel::calcFGuids() const
{
    return m_geometryElements.getFGuidsFromMaps();
}
void FlowMeshModel::addSegments(const FlowMeshSegments& flowMeshSegments)
{
    addAndUpdateView(flowMeshSegments);
}
void FlowMeshModel::addSphere(const FlowMeshSphere& sphere)
{
    addAndUpdateView(sphere);
}
void FlowMeshModel::addCone(const FlowMeshCone& flowMeshCone)
{
    addAndUpdateView(flowMeshCone);
}
void FlowMeshModel::addCylinder(const FlowMeshCylinder& cylinder)
{
    if (m_geometryElements.add(cylinder))
        m_flowMeshPresenter->add(cylinder);
}
void FlowMeshModel::remove(const FGuid& fGuid)
{
    m_geometryElements.remove(fGuid);
    m_flowMeshPresenter->remove(fGuid);
}
} // namespace FlowMesh
