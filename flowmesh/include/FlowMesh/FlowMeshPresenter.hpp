#ifndef FILAPP_FLOWMESHPRESENTER_HPP
#define FILAPP_FLOWMESHPRESENTER_HPP

#include "PresenterConfig.hpp"
#include <Core/Types/TMap.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGrid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <FlowMesh/ModelEventDispatcher.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <GraphicsInterface/GraphicsController.hpp>
#include <GraphicsInterface/Renderables/RendereableId.hpp>
#include <GraphicsInterface/View.hpp>

namespace Graphics
{
class View;
}

namespace FlowMesh
{

class FlowMeshPresenter : public ModelEventListener {
    Graphics::View* m_view{nullptr};
    PresenterConfig m_presenterConfig{};

    Core::TMap<FGuid, std::vector<Graphics::RenderableId>> m_fGuidRenderableMapping;

  public:
    explicit FlowMeshPresenter(Graphics::View* mainView);

    void registerListener(Graphics::GraphicsController* flowMeshController);
    void removeListener(Graphics::GraphicsController* flowMeshController);

    void onAdd(const FlowMeshSphere& flowMeshSphere) override;
    void onAdd(const FlowMeshCone& flowMeshCone) override;
    void onAdd(const FlowMeshCylinder& flowMeshCylinder) override;
    void onAdd(const FlowMeshSegments& flowMeshSegments) override;
    void onAdd(const FlowMeshCuboid& flowMeshCuboid) override;
    void onAdd(const FlowMeshGrid& flowMeshGrid) override;

    void onRemove(const FGuid& fGuid) override;
    void onPositionChanged(const PositionEvent& positionEvent) override;

    void setIdleAnimation(const Graphics::Vec3& rotationAxis);

  private:
    static Graphics::TriangleRenderable
    createTriangleRenderable(const Geometry::HalfedgeMesh<double_t>& halfedgeMesh,
                             std::uint32_t faceColor);
    static Graphics::LineRenderable createLineRenderables(const Core::TVector<Geometry::Segment3d>&,
                                                          std::uint32_t lineColor);
    void segmentGraphicsVertices(const Geometry::HalfedgeMesh<double_t>& heMesh,
                                 const std::vector<Geometry::SegmentIndices>& segIndices,
                                 std::vector<Graphics::Vertex>& vertices) const;
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHPRESENTER_HPP
