#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include "FlowMesh/GeometryElements/FlowMeshCone.hpp"
#include "FlowMesh/GeometryElements/FlowMeshCylinder.hpp"
#include <FlowMesh/FlowMeshPresenter.hpp>
#include "FlowMesh/GeometryElements/FlowMeshSegments.hpp"
#include "FlowMesh/GeometryElements/FlowMeshSphere.hpp"
#include "FlowMesh/GeometryElements/GeometryElements.hpp"
#include <FlowMesh/TypeId.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace FlowMesh
{
class FlowMeshModel {
    GeometryElements m_geometryElements;
    FlowMeshPresenter* m_flowMeshPresenter{nullptr};

  public:
    void setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter);

    [[nodiscard]] std::vector<TypeId> calcTypeIds() const;

    void addSphere(const FlowMeshSphere& sphere);
    void addCone(const FlowMeshCone& flowMeshCone);
    void addCylinder(const FlowMeshCylinder& cylinder);
    void addSegments(const FlowMeshSegments& flowMeshSegments);

    void remove(const TypeId& typeId);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
