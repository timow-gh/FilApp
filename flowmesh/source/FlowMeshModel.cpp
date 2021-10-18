#include "FlowMesh/FlowMeshModel.hpp"
#include "FlowMesh/FlowMeshPresenter.hpp"

namespace FlowMesh
{
void FlowMeshModel::setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter)
{
    m_flowMeshPresenter = flowMeshPresenter;
}
void FlowMeshModel::addSphere(const FlowMeshSphere& sphere)
{
    auto res = m_spheres.emplace(sphere.getGuid(), sphere);
    if (res.second)
        m_flowMeshPresenter->add(res.first->second);
}
void FlowMeshModel::remove(const xg::Guid& guid)
{
    m_spheres.erase(guid);
}
void FlowMeshModel::addSegments(const FlowMeshSegments& flowMeshSegments)
{
    auto res = m_segments.emplace(flowMeshSegments.getGuid(), flowMeshSegments);
    if (res.second)
        m_flowMeshPresenter->add(res.first->second);
}
} // namespace FlowMesh
