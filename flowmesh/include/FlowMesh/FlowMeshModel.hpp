#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <FlowMesh/GeometryElements/GeometryElements.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace FlowMesh
{
class FlowMeshModel {
    GeometryElements m_geometryElements;
    FlowMeshPresenter* m_flowMeshPresenter{nullptr};

  public:
    void setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter);

    [[nodiscard]] std::vector<FGuid> calcFGuids() const;

    void add(const FlowMeshSphere& sphere);
    void add(const FlowMeshCone& flowMeshCone);
    void add(const FlowMeshCylinder& cylinder);
    void add(const FlowMeshSegments& flowMeshSegments);

    void remove(const FGuid& fGuid);
    void setPosition(const FGuid& fGuid, LinAl::Vec3d& position);

  private:
    template <typename T>
    void addToView(const T& geometryElement)
    {
        if (m_geometryElements.add(geometryElement))
            m_flowMeshPresenter->add(geometryElement);
    }
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
