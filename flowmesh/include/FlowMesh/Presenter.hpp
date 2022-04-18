#ifndef FILAPP_PRESENTER_HPP
#define FILAPP_PRESENTER_HPP

#include "PresenterConfig.hpp"
#include <Core/Types/TMap.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <GraphicsInterface/Renderables/RendereableId.hpp>
#include <GraphicsInterface/View.hpp>

namespace Graphics
{
class View;
}

namespace FlowMesh
{
// TODO Presenter is actually doint the job a FilAppModel should do
// TODO Create FilAppModel, FilAppModelEvents, FilAppModelEventListener, FilAppModelEventDispatcher?
// TODO FilAppView only takes FilAppRenderables?
class Presenter {
    Graphics::View* m_mainView{nullptr};
    PresenterConfig m_presenterConfig{};

    Core::TMap<FGuid, std::vector<Graphics::RenderableId>> m_fGuidRenderableMapping;

  public:
    explicit Presenter(Graphics::View* mainView);

    void add(const FlowMeshSphere& flowMeshSphere);
    void add(const FlowMeshCone& flowMeshCone);
    void add(const FlowMeshCylinder& flowMeshCylinder);
    void add(const FlowMeshSegments& flowMeshSegments);

    void remove(const FGuid& fGuid);
    void updatePosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    void setIdleAnimation(const Graphics::Vec3& rotationAxis);

  private:
    static Graphics::TriangleRenderable
    createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh,
                             std::uint32_t faceColor);
    static Graphics::LineRenderable createLineRenderables(const FlowMeshSegments& flowMeshSegments,
                                                          std::uint32_t lineColor);
    void segmentFilAppVertices(const Geometry::HalfedgeMesh<double_t>& heMesh,
                               const std::vector<Geometry::SegmentIndices>& segIndices,
                               std::vector<Graphics::Vertex>& vertices) const;
};
} // namespace FlowMesh

#endif // FILAPP_PRESENTER_HPP
