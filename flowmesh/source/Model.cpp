#include "FlowMesh/Model.hpp"
#include "FlowMesh/Presenter.hpp"

namespace FlowMesh
{
void Model::setFlowMeshPresenter(Presenter* flowMeshPresenter)
{
    m_flowMeshPresenter = flowMeshPresenter;
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
} // namespace FlowMesh
