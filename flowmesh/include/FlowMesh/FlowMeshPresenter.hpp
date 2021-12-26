#ifndef FILAPP_FLOWMESHPRESENTER_HPP
#define FILAPP_FLOWMESHPRESENTER_HPP

#include <Core/Types/TMap.hpp>
#include <FilApp/FilAppView.hpp>
#include <FilAppInterface/Renderables/RendereableId.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>

namespace FilApp
{
class View;
}

namespace FlowMesh
{
class FlowMeshPresenter {
    FilApp::View* m_mainView{nullptr};

    std::map<FGuid, std::vector<FilApp::RenderableId>> m_fGuidRenderableMapping;

  public:
    void setMainView(FilApp::View* mainView) { m_mainView = mainView; }

    void add(const FlowMeshSphere& flowMeshSphere);
    void add(const FlowMeshCone& flowMeshCone);
    void add(const FlowMeshCylinder& flowMeshCylinder);
    void add(const FlowMeshSegments& flowMeshSegments);

    void remove(const FGuid& fGuid);
    void updatePosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    void setIdleAnimation(const FilApp::Vec3& rotationAxis);

  private:
    static FilApp::TriangleRenderable createTriangleRenderable(
        const Geometry::HalfedgeMesh<double_t>& halfedgeMesh);
    static FilApp::LineRenderable
    createLineRenderables(const FlowMeshSegments& flowMeshSegments);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHPRESENTER_HPP
