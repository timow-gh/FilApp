#ifndef FILAPP_FLOWMESHSEGMENTS_HPP
#define FILAPP_FLOWMESHSEGMENTS_HPP

#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FGuidBase.hpp>
#include <Geometry/Segment.hpp>

namespace FlowMesh
{
class FlowMeshSegments : public FGuidBase<FlowMeshSegments> {
    Core::TVector<Geometry::Segment3d> m_segments;

  public:
    FlowMeshSegments();
    FlowMeshSegments(Core::TVector<Geometry::Segment3d> segments,
                     const FGuid& guid);

    [[nodiscard]] const Core::TVector<Geometry::Segment3d>& getSegments() const;
    void setSegments(const Core::TVector<Geometry::Segment3d>& segments);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHSEGMENTS_HPP
