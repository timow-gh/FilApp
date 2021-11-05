#include "FlowMesh/FlowMeshCone.hpp"
#include <Geometry/Segment.hpp>
#include <LinAl/LinearAlgebra.hpp>

using namespace Geometry;
using namespace LinAl;

namespace FlowMesh
{
FlowMeshCone::FlowMeshCone()
    : m_cone(Cone<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
    , m_typeId(TypeId())
{
}
FlowMeshCone::FlowMeshCone(const Cone<double_t>& cone, const TypeId& typeId)
    : m_cone(cone), m_typeId(typeId)
{
}
const Cone<double_t>& FlowMeshCone::getCone() const
{
    return m_cone;
}
const TypeId& FlowMeshCone::getTypeId() const
{
    return m_typeId;
}
bool operator==(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return lhs.m_cone == rhs.m_cone && lhs.m_typeId == rhs.m_typeId;
}
bool operator!=(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshCone& lhs, const FlowMeshCone& rhs)
{
    return lhs.m_typeId < rhs.m_typeId;
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
