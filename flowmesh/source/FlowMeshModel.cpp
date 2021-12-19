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
    addImpl(flowMeshSegments);
}

void FlowMeshModel::add(const FlowMeshSphere& sphere)
{
    addImpl(sphere);
}

void FlowMeshModel::add(const FlowMeshCone& flowMeshCone)
{
    addImpl(flowMeshCone);
}

void FlowMeshModel::add(const FlowMeshCylinder& cylinder)
{
    addImpl(cylinder);
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
