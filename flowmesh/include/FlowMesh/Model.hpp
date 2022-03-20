#ifndef FILAPP_MODEL_HPP
#define FILAPP_MODEL_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <FlowMesh/GeometryElements/GeometryElements.hpp>
#include <FlowMesh/Interactors/SnapGeometries.hpp>
#include <FlowMesh/Presenter.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace FlowMesh
{

class Model {
    GeometryElements m_geometryElements;
    Presenter* m_flowMeshPresenter{nullptr};

  public:
    explicit Model(Presenter* presenter);

    CORE_NODISCARD Core::TVector<FGuid> calcFGuids() const;

    template <typename TFlowMeshGeometry>
    void add(const TFlowMeshGeometry& flowMeshGeometry)
    {
        if (m_geometryElements.add(flowMeshGeometry))
            m_flowMeshPresenter->add(flowMeshGeometry);
    }

    template <typename TFlowMeshGeometry>
    bool get(FGuid guid, TFlowMeshGeometry& result)
    {
        return m_geometryElements.get(guid, result);
    }

    void remove(const FGuid& fGuid);
    void setPosition(const FGuid& fGuid, LinAl::Vec3d& position);

    CORE_NODISCARD SnapGeometries calcModelSnapGeometries() const;
};

} // namespace FlowMesh

#endif // FILAPP_MODEL_HPP
