#ifndef FILAPP_FLOWMESHPRESENTER_HPP
#define FILAPP_FLOWMESHPRESENTER_HPP

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
class FlowMeshPresenter {
    Graphics::View* m_mainView{nullptr};
    PresenterConfig m_presenterConfig{};

    std::map<FGuid, std::vector<Graphics::RenderableId>> m_fGuidRenderableMapping;

  public:
    explicit FlowMeshPresenter(Graphics::View* mainView);

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

#endif // FILAPP_FLOWMESHPRESENTER_HPP
