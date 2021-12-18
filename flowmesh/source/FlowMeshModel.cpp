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

void FlowMeshModel::add(const FlowMeshSegments& flowMeshSegments)
{
    addToView(flowMeshSegments);
}

void FlowMeshModel::add(const FlowMeshSphere& sphere)
{
    addToView(sphere);
}

void FlowMeshModel::add(const FlowMeshCone& flowMeshCone)
{
    addToView(flowMeshCone);
}

void FlowMeshModel::add(const FlowMeshCylinder& cylinder)
{
    if (m_geometryElements.add(cylinder))
        m_flowMeshPresenter->add(cylinder);
}

void FlowMeshModel::remove(const FGuid& fGuid)
{
    m_geometryElements.remove(fGuid);
    m_flowMeshPresenter->remove(fGuid);
}

void FlowMeshModel::setPosition(const FGuid& fGuid, LinAl::Vec3d& position)
{
    if (m_geometryElements.setPosition(fGuid, position))
        m_flowMeshPresenter->updatePosition(fGuid, position);
}
} // namespace FlowMesh
