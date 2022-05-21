#include <Meshler/GeometryElements/MSegments.hpp>
#include <utility>

namespace Meshler
{
MSegments::MSegments() : GeometryElementBase<MSegments>(FGuid(), MGeometryConfigBase{})
{
}

MSegments::MSegments(Core::TVector<Geometry::Segment3d> segments,
                     const FGuid& guid,
                     MGeometryConfigBase baseConfig)
    : GeometryElementBase<MSegments>(guid, baseConfig), m_segments(std::move(segments))
{
}

MSegments::MSegments(const Geometry::Segment3d& segment,
                     const FGuid& guid,
                     MGeometryConfigBase baseConfig)
    : GeometryElementBase<MSegments>(guid, baseConfig), m_segments({segment})
{
}

const Core::TVector<Geometry::Segment3d>& MSegments::getSegments() const
{
    return m_segments;
}

void MSegments::setSegments(const Core::TVector<Geometry::Segment3d>& segments)
{
    m_segments = segments;
}

} // namespace Meshler
