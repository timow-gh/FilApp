#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <FlowMesh/GeometryElements/GeometryElements.hpp>
#include <FlowMesh/Interactors/SnapGeometries.hpp>
#include <FlowMesh/ModelEventDispatcher.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace FlowMesh
{

class FlowMeshModel {
    GeometryElements m_geometryElements;
    ModelEventDispatcher m_modelEventDispatcher;

  public:
    FlowMeshModel() = default;
    explicit FlowMeshModel(ModelEventListener* modelEventListener);

    void registerListener(ModelEventListener* modelEventListener)
    {
        m_modelEventDispatcher.registerListener(modelEventListener);
    }

    void removeListener(ModelEventListener* modelEventListener)
    {
        m_modelEventDispatcher.removeListener(modelEventListener);
    }

    template <typename TFlowMeshGeometry>
    void add(const TFlowMeshGeometry& flowMeshGeometry)
    {
        if (m_geometryElements.add(flowMeshGeometry))
            m_modelEventDispatcher.dispatchAdd(flowMeshGeometry);
    }

    void remove(const FGuid& fGuid);
    void setPosition(const FGuid& fGuid, LinAl::Vec3d& position);

    CORE_NODISCARD SnapGeometries calcModelSnapGeometries() const;
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
