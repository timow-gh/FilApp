#ifndef FILAPP_FLOWMESHSEGMENTS_HPP
#define FILAPP_FLOWMESHSEGMENTS_HPP

#include "_deps/core-src/src/types/Core/Types/TVector.hpp"
#include "FlowMesh/FlowMeshGuid.hpp"
#include "_deps/geometry-src/src/include/Geometry/Segment.hpp"

namespace FlowMesh
{
class FlowMeshSegments
{
    Core::TVector<Geometry::Segment3d> m_segments;

  public:
    FlowMeshSegments() = default;
    FlowMeshSegments(Core::TVector<Geometry::Segment3d> segments,
                     const FGuid& guid);

    [[nodiscard]] const Core::TVector<Geometry::Segment3d>& getSegments() const;
    void setSegments(const Core::TVector<Geometry::Segment3d>& segments);

    [[nodiscard]] const FGuid& getFGuid() const;

    friend bool operator==(const FlowMeshSegments& lhs,
                           const FlowMeshSegments& rhs);
    friend bool operator!=(const FlowMeshSegments& lhs,
                           const FlowMeshSegments& rhs);

    friend bool operator<(const FlowMeshSegments& lhs,
                          const FlowMeshSegments& rhs);
    friend bool operator>(const FlowMeshSegments& lhs,
                          const FlowMeshSegments& rhs);
    friend bool operator<=(const FlowMeshSegments& lhs,
                           const FlowMeshSegments& rhs);
    friend bool operator>=(const FlowMeshSegments& lhs,
                           const FlowMeshSegments& rhs);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHSEGMENTS_HPP
