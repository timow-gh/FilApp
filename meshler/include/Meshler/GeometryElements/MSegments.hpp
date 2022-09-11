#ifndef MESHLER_MSEGMENTS_HPP
#define MESHLER_MSEGMENTS_HPP

#include <Core/Types/TVector.hpp>
#include <Geometry/Segment.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{
class MSegments : public GeometryElementBase<MSegments> {
  Core::TVector<Geometry::Segment3d> m_segments;

public:
  MSegments();
  MSegments(Core::TVector<Geometry::Segment3d> segments, const FGuid& guid, MGeometryConfigBase baseConfig);
  MSegments(const Geometry::Segment3d& segment, const FGuid& guid, MGeometryConfigBase baseConfig);

  CORE_NODISCARD const Core::TVector<Geometry::Segment3d>& getSegments() const;
  void setSegments(const Core::TVector<Geometry::Segment3d>& segments);
};
} // namespace Meshler

#endif // MESHLER_MSEGMENTS_HPP
