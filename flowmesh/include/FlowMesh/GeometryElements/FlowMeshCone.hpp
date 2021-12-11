#ifndef FILAPP_FLOWMESHCONE_HPP
#define FILAPP_FLOWMESHCONE_HPP

#include "FlowMesh/FlowMeshGuid.hpp"
#include "_deps/geometry-src/src/include/Geometry/Cone.hpp"

namespace FlowMesh
{
class FlowMeshCone
{
    Geometry::Cone<double_t> m_cone;
    FGuid m_fGuid;

  public:
    FlowMeshCone();
    FlowMeshCone(const Geometry::Cone<double_t>& cone, const FGuid& fGuid);

    [[nodiscard]] const Geometry::Cone<double_t>& getCone() const;
    [[nodiscard]] const FGuid& getFGuid() const;

    friend bool operator==(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator!=(const FlowMeshCone& lhs, const FlowMeshCone& rhs);

    friend bool operator<(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator>(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator<=(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
    friend bool operator>=(const FlowMeshCone& lhs, const FlowMeshCone& rhs);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONE_HPP
