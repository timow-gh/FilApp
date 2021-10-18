#include "FlowMesh/FlowMeshSphere.hpp"

namespace FlowMesh
{
FlowMeshSphere::FlowMeshSphere()
    : m_sphere(Geometry::Sphere<double_t>(LinAl::ZERO_VEC3D, 1.0)), m_guid()
{
}
FlowMeshSphere::FlowMeshSphere(Geometry::Sphere<double_t> sphere,
                               const xg::Guid& guid)
    : m_sphere(std::move(sphere)), m_guid(guid)
{
}
const Geometry::Sphere<double_t>& FlowMeshSphere::getSphere() const
{
    return m_sphere;
}
void FlowMeshSphere::setSphere(const Geometry::Sphere<double_t>& sphere)
{
    m_sphere = sphere;
}
const xg::Guid& FlowMeshSphere::getGuid() const
{
    return m_guid;
}
bool operator==(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs)
{
    return std::tie(lhs.m_sphere, lhs.m_guid) ==
           std::tie(rhs.m_sphere, rhs.m_guid);
}
bool operator!=(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs)
{
    return lhs.m_guid < rhs.m_guid;
}
bool operator>(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs)
{
    return rhs < lhs;
}
bool operator<=(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs)
{
    return !(rhs < lhs);
}
bool operator>=(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs)
{
    return !(lhs < rhs);
}

} // namespace FlowMesh