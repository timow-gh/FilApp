#include "FlowMesh/GeometryElements/FlowMeshCylinder.hpp"

using namespace Geometry;
using namespace LinAl;

namespace FlowMesh
{
FlowMeshCylinder::FlowMeshCylinder()
    : m_cylinder(Cylinder<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
    , m_fGuid(FGuid())
{
}
FlowMeshCylinder::FlowMeshCylinder(const Cylinder<double_t>& cylinder,
                                   const FGuid& fGuid)
    : m_cylinder(cylinder), m_fGuid(fGuid)
{
}
const Cylinder<double_t>& FlowMeshCylinder::getCylinder() const
{
    return m_cylinder;
}
const FGuid& FlowMeshCylinder::getFGuid() const
{
    return m_fGuid;
}
bool operator==(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return lhs.m_cylinder == rhs.m_cylinder && lhs.m_fGuid == rhs.m_fGuid;
}
bool operator!=(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return lhs.m_fGuid < rhs.m_fGuid;
}
bool operator>(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return rhs < lhs;
}
bool operator<=(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return !(rhs < lhs);
}
bool operator>=(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return !(lhs < rhs);
}
} // namespace FlowMesh
