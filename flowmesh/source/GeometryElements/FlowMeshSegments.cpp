#include "FlowMesh/GeometryElements/FlowMeshSegments.hpp"
#include <utility>

namespace FlowMesh
{
FlowMeshSegments::FlowMeshSegments()
    : GeometryElementBase<FlowMeshSegments>(FGuid(), FlowMeshGeometryConfigBase{})
{
}

FlowMeshSegments::FlowMeshSegments(Core::TVector<Geometry::Segment3d> segments,
                                   const FGuid& guid,
                                   FlowMeshGeometryConfigBase baseConfig)
    : GeometryElementBase<FlowMeshSegments>(guid, baseConfig), m_segments(std::move(segments))
{
}

FlowMeshSegments::FlowMeshSegments(const Geometry::Segment3d& segment,
                                   const FGuid& guid,
                                   FlowMeshGeometryConfigBase baseConfig)
    : GeometryElementBase<FlowMeshSegments>(guid, baseConfig), m_segments({segment})
{
}

const Core::TVector<Geometry::Segment3d>& FlowMeshSegments::getSegments() const
{
    return m_segments;
}

void FlowMeshSegments::setSegments(const Core::TVector<Geometry::Segment3d>& segments)
{
    m_segments = segments;
}

} // namespace FlowMesh
