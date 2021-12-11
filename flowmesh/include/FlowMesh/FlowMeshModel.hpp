#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include "FlowMesh/GeometryElements/FlowMeshCone.hpp"
#include "FlowMesh/GeometryElements/FlowMeshCylinder.hpp"
#include "FlowMesh/GeometryElements/FlowMeshSegments.hpp"
#include "FlowMesh/GeometryElements/FlowMeshSphere.hpp"
#include "FlowMesh/GeometryElements/GeometryElements.hpp"
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
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

    void addSphere(const FlowMeshSphere& sphere);
    void addCone(const FlowMeshCone& flowMeshCone);
    void addCylinder(const FlowMeshCylinder& cylinder);
    void addSegments(const FlowMeshSegments& flowMeshSegments);

    void remove(const FGuid& fGuid);

  private:
    template <typename T>
    void addAndUpdateView(const T& geometryElement)
    {
        if (m_geometryElements.add(geometryElement))
            m_flowMeshPresenter->add(geometryElement);
    }
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
