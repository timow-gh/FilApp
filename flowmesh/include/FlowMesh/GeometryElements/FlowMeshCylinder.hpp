#ifndef FILAPP_FLOWMESHCYLINDER_HPP
#define FILAPP_FLOWMESHCYLINDER_HPP

#include "FlowMesh/TypeId.hpp"
#include "_deps/geometry-src/src/include/Geometry/Cylinder.hpp"
#include "_deps/geometry-src/src/include/Geometry/Segment.hpp"

namespace FlowMesh
{
class FlowMeshCylinder
{
    Geometry::Cylinder<double_t> m_cylinder;
    TypeId m_typeId;

  public:
    FlowMeshCylinder();
    FlowMeshCylinder(const Geometry::Cylinder<double_t>& cylinder,
                     const TypeId& typeId);

    [[nodiscard]] const Geometry::Cylinder<double_t>& getCylinder() const;
    [[nodiscard]] const TypeId& getTypeId() const;

    friend bool operator==(const FlowMeshCylinder& lhs,
                           const FlowMeshCylinder& rhs);
    friend bool operator!=(const FlowMeshCylinder& lhs,
                           const FlowMeshCylinder& rhs);

    friend bool operator<(const FlowMeshCylinder& lhs,
                          const FlowMeshCylinder& rhs);
    friend bool operator>(const FlowMeshCylinder& lhs,
                          const FlowMeshCylinder& rhs);
    friend bool operator<=(const FlowMeshCylinder& lhs,
                           const FlowMeshCylinder& rhs);
    friend bool operator>=(const FlowMeshCylinder& lhs,
                           const FlowMeshCylinder& rhs);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCYLINDER_HPP
