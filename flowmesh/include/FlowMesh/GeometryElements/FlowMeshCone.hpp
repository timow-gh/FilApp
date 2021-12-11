#ifndef FILAPP_FLOWMESHCONE_HPP
#define FILAPP_FLOWMESHCONE_HPP

#include "FlowMesh/TypeId.hpp"
#include "_deps/geometry-src/src/include/Geometry/Cone.hpp"

namespace FlowMesh
{
class FlowMeshCone
{
    Geometry::Cone<double_t> m_cone;
    TypeId m_typeId;

  public:
    FlowMeshCone();
    FlowMeshCone(const Geometry::Cone<double_t>& cone, const TypeId& typeId);

    [[nodiscard]] const Geometry::Cone<double_t>& getCone() const;
    [[nodiscard]] const TypeId& getTypeId() const;

    friend bool operator==(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator!=(const FlowMeshCone& lhs, const FlowMeshCone& rhs);

    friend bool operator<(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator>(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator<=(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator>=(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONE_HPP
