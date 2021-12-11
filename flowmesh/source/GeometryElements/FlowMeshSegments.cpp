#include "FlowMesh/GeometryElements/FlowMeshSegments.hpp"
#include <utility>

namespace FlowMesh
{

FlowMeshSegments::FlowMeshSegments(Core::TVector<Geometry::Segment3d> segments,
                                   const xg::Guid& guid)
    : m_segments(std::move(segments)), m_fGuid(guid)
{
}
const Core::TVector<Geometry::Segment3d>& FlowMeshSegments::getSegments() const
{
    return m_segments;
}
void FlowMeshSegments::setSegments(
    const Core::TVector<Geometry::Segment3d>& segments)
{
    m_segments = segments;
}
const xg::Guid& FlowMeshSegments::getFGuid() const
{
    return m_fGuid;
}
bool operator==(const FlowMeshSegments& lhs, const FlowMeshSegments& rhs)
{
    return std::tie(lhs.m_segments, lhs.m_fGuid) ==
           std::tie(rhs.m_segments, rhs.m_fGuid);
}
bool operator!=(const FlowMeshSegments& lhs, const FlowMeshSegments& rhs)
{
    return !(rhs == lhs);
}
bool operator<(const FlowMeshSegments& lhs, const FlowMeshSegments& rhs)
{
    return lhs.m_fGuid < rhs.m_fGuid;
}
bool operator>(const FlowMeshSegments& lhs, const FlowMeshSegments& rhs)
{
    return rhs < lhs;
}
bool operator<=(const FlowMeshSegments& lhs, const FlowMeshSegments& rhs)
{
    return !(rhs < lhs);
}
bool operator>=(const FlowMeshSegments& lhs, const FlowMeshSegments& rhs)
{
    return !(lhs < rhs);
}

} // namespace FlowMesh
