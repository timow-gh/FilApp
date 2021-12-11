#include "FlowMesh/GeometryElements/FlowMeshSegments.hpp"
#include <utility>

namespace FlowMesh
{
FlowMeshSegments::FlowMeshSegments() : FGuidBase<FlowMeshSegments>(FGuid())
{
}
FlowMeshSegments::FlowMeshSegments(Core::TVector<Geometry::Segment3d> segments,
                                   const FGuid& guid)
    : FGuidBase<FlowMeshSegments>(guid), m_segments(std::move(segments))
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
} // namespace FlowMesh
