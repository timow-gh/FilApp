#ifndef FILAPP_FLOWMESHPRESENTER_HPP
#define FILAPP_FLOWMESHPRESENTER_HPP

#include <Core/Types/TMap.hpp>
#include <FilApp/FilAppView.hpp>
#include <FilAppInterfaces/Renderables/RendereableIdentifier.hpp>
#include "FlowMesh/GeometryElements/FlowMeshCone.hpp"
#include "FlowMesh/GeometryElements/FlowMeshCylinder.hpp"
#include "FlowMesh/GeometryElements/FlowMeshSegments.hpp"
#include "FlowMesh/GeometryElements/FlowMeshSphere.hpp"
#include <FlowMesh/TypeId.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>

namespace FilApp
{
class IView;
}

namespace FlowMesh
{
class FlowMeshPresenter
{
    FilApp::IView* m_mainView{nullptr};

    std::map<TypeId, std::vector<FilApp::RenderableIdentifier>>
        m_typeIdRenderableMapping;

  public:
    void setMainView(FilApp::IView* mainView) { m_mainView = mainView; }

    void add(const FlowMeshSphere& flowMeshSphere);
    void add(const FlowMeshCone& flowMeshCone);
    void add(const FlowMeshCylinder& flowMeshCylinder);
    void add(const FlowMeshSegments& flowMeshSegments);

    void remove(const TypeId& typeId);

    void setIdleAnimation(const FilApp::Vec3& rotationAxis);

  private:
    static FilApp::TriangleRenderable createTriangleRenderable(
        const Geometry::HalfedgeMesh<double_t>& halfedgeMesh);
    static FilApp::LineRenderable
    createLineRenderables(const FlowMeshSegments& flowMeshSegments);

    LinAl::Matrix3d m_mathLcsToFilamentLcs;
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHPRESENTER_HPP
