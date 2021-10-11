#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include <Core/Types/TSet.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/FlowMeshSphere.hpp>
#include <map>

namespace FlowMesh
{
class FlowMeshModel
{
    std::map<xg::Guid, FlowMeshSphere> m_spheres;
    FlowMeshPresenter* m_flowMeshPresenter;

  public:
    void setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter);

    void addSphere(const FlowMeshSphere& sphere);
    void remove(const xg::Guid& guid);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
