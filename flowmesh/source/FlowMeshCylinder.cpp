#include "FlowMesh/FlowMeshCylinder.hpp"

using namespace Geometry;
using namespace LinAl;

namespace FlowMesh
{
FlowMeshCylinder::FlowMeshCylinder()
    : m_cylinder(Cylinder<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
    , m_typeId(TypeId())
{
}
FlowMeshCylinder::FlowMeshCylinder(const Cylinder<double_t>& cylinder,
                                   const TypeId& typeId)
    : m_cylinder(cylinder), m_typeId(typeId)
{
}
const Cylinder<double_t>& FlowMeshCylinder::getCylinder() const
{
    return m_cylinder;
}
const TypeId& FlowMeshCylinder::getTypeId() const
{
    return m_typeId;
}
bool operator==(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return lhs.m_cylinder == rhs.m_cylinder && lhs.m_typeId == rhs.m_typeId;
}
bool operator!=(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshCylinder& lhs, const FlowMeshCylinder& rhs)
{
    return lhs.m_typeId < rhs.m_typeId;
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
