#include "FlowMesh/FlowMeshPoint.hpp"

namespace FlowMesh
{
FlowMeshPoint::FlowMeshPoint()
    : m_sphere(Geometry::Sphere<double_t>(LinAl::ZERO_VEC3D, 1.0)), m_guid()
{
}
FlowMeshPoint::FlowMeshPoint(Geometry::Sphere<double_t> sphere,
                             const xg::Guid& guid)
    : m_sphere(std::move(sphere)), m_guid(guid)
{
}
const Geometry::Sphere<double_t>& FlowMeshPoint::getSphere() const
{
    return m_sphere;
}
void FlowMeshPoint::setSphere(const Geometry::Sphere<double_t>& sphere)
{
    m_sphere = sphere;
}
const xg::Guid& FlowMeshPoint::getGuid() const
{
    return m_guid;
}
bool operator==(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs)
{
    return std::tie(lhs.m_sphere, lhs.m_guid) ==
           std::tie(rhs.m_sphere, rhs.m_guid);
}
bool operator!=(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs)
{
    return lhs.m_guid < rhs.m_guid;
}
bool operator>(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs)
{
    return rhs < lhs;
}
bool operator<=(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs)
{
    return !(rhs < lhs);
}
bool operator>=(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs)
{
    return !(lhs < rhs);
}

} // namespace FlowMesh