#ifndef FILAPP_FLOWMESHCYLINDER_HPP
#define FILAPP_FLOWMESHCYLINDER_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Cylinder.hpp>
#include <Geometry/Segment.hpp>

namespace FlowMesh
{

class FlowMeshCylinder : public GeometryElementBase<FlowMeshCylinder> {
    Geometry::Cylinder<double_t> m_cylinder;

  public:
    FlowMeshCylinder();
    FlowMeshCylinder(const Geometry::Cylinder<double_t>& cylinder, const FGuid& fGuid);

    [[nodiscard]] const Geometry::Cylinder<double_t>& getGeometryElement() const;
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCYLINDER_HPP
