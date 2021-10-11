#ifndef FILAPP_FLOWMESHPRESENTER_HPP
#define FILAPP_FLOWMESHPRESENTER_HPP

#include <Core/Types/TMap.hpp>
#include <CrossGuid/Guid.hpp>
#include <FilApp/FilAppView.hpp>
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

  private:
    FilApp::TriangleRenderable
    createTriangleRenderable(const FlowMeshSphere& flowMeshSphere);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHPRESENTER_HPP
