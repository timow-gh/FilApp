#include "FlowMesh/GeometryElements/FlowMeshCone.hpp"
#include "_deps/geometry-src/src/include/Geometry/Segment.hpp"
#include "_deps/linal-src/src/include/LinAl/LinearAlgebra.hpp"

using namespace Geometry;
using namespace LinAl;

namespace FlowMesh
{
FlowMeshCone::FlowMeshCone()
    : m_cone(Cone<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
    , m_fGuid(FGuid())
{
}
FlowMeshCone::FlowMeshCone(const Cone<double_t>& cone, const FGuid& fGuid)
    : m_cone(cone), m_fGuid(fGuid)
{
}
const Cone<double_t>& FlowMeshCone::getCone() const
{
    return m_cone;
}
const FGuid& FlowMeshCone::getFGuid() const
{
    return m_fGuid;
}
bool operator==(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return lhs.m_cone == rhs.m_cone && lhs.m_fGuid == rhs.m_fGuid;
}
bool operator!=(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return lhs.m_fGuid < rhs.m_fGuid;
}
bool operator>(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return rhs < lhs;
}
bool operator<=(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return !(rhs < lhs);
}
bool operator>=(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return !(lhs < rhs);
}
} // namespace FlowMesh
