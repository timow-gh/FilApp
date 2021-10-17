#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include <Core/Types/TSet.hpp>
#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshPoint.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/FlowMeshSegments.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace FlowMesh
{
class FlowMeshModel
{
    std::map<xg::Guid, FlowMeshPoint> m_spheres;
    std::map<xg::Guid, FlowMeshSegments> m_segments;

    FlowMeshPresenter* m_flowMeshPresenter;

  public:
    void setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter);

    void addSphere(const FlowMeshPoint& sphere);
    void addSegments(const FlowMeshSegments& flowMeshSegments);

    void remove(const xg::Guid& guid);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
