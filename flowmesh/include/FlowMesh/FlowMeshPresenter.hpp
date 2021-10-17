#ifndef FILAPP_FLOWMESHPRESENTER_HPP
#define FILAPP_FLOWMESHPRESENTER_HPP

#include <Core/Types/TMap.hpp>
#include <CrossGuid/Guid.hpp>
#include <FilApp/FilAppView.hpp>
#include <FlowMesh/FlowMeshSegments.hpp>
#include <FlowMesh/FlowMeshSphere.hpp>

namespace FilApp
{
class IView;
}

namespace FlowMesh
{
class FlowMeshPresenter
{
    FilApp::IView* m_mainView{nullptr};

  public:
    void setMainView(FilApp::IView* mainView) { m_mainView = mainView; }

    void add(const FlowMeshSphere& flowMeshSphere);
    void add(const FlowMeshSegments& flowMeshSegments);

  private:
    static FilApp::TriangleRenderable
    createTriangleRenderable(const FlowMeshSphere& flowMeshSphere);
    static FilApp::LineRenderable
    createLineRenderables(const FlowMeshSegments& flowMeshSegments);

    LinAl::Matrix3d m_mathLcsToFilamentLcs;
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHPRESENTER_HPP
