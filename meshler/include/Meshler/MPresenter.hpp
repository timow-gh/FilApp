#ifndef MESHLER_MPRESENTER_HPP
#define MESHLER_MPRESENTER_HPP

#include "PresenterConfig.hpp"
#include <Core/Types/TMap.hpp>
#include <Meshler/MGuid.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/MModelEventDispatcher.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <Graphics/GraphicsController.hpp>
#include <Graphics/Renderables/RendereableId.hpp>
#include <Graphics/View.hpp>

namespace Graphics
{
class View;
}

namespace Meshler
{

class MPresenter : public MModelEventListener {
    Graphics::View* m_view{nullptr};
    PresenterConfig m_presenterConfig{};

    Core::TMap<FGuid, std::vector<Graphics::RenderableId>> m_fGuidRenderableMapping;

  public:
    explicit MPresenter(Graphics::View* mainView);

    void registerListener(Graphics::GraphicsController* meshlerController);
    void removeListener(Graphics::GraphicsController* meshlerController);

    void registerInputEventListener(Graphics::InputEventListener* inputEventListener);
    void removeInputEventListener(Graphics::InputEventListener* inputEventListener);

    void registerRayPickEventListener(Graphics::RayPickEventListener* rayPickEventListener);
    void removeRayPickEventListener(Graphics::RayPickEventListener* rayPickEventListener);

    void onAdd(const MSphere& meshlerSphere) override;
    void onAdd(const MCone& meshlerCone) override;
    void onAdd(const MCylinder& meshlerCylinder) override;
    void onAdd(const MSegments& meshlerSegments) override;
    void onAdd(const MCuboid& meshlerCuboid) override;
    void onAdd(const MGrid& meshlerGrid) override;

    void onRemove(const FGuid& fGuid) override;

    void onUpdate(const MCylinder& meshlerCylinder) override;
    void onUpdate(const MCone& meshlerCone) override;
    void onUpdate(const MSegments& meshlerSegments) override;
    void onUpdate(const MSphere& meshlerSphere) override;
    void onUpdate(const MCuboid& meshlerCuboid) override;
    void onUpdate(const MGrid& meshlerGrid) override;

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

    template <typename TGeometryElement>
    void onUpdateImpl(const TGeometryElement& elem)
    {
        onRemove(elem.getFGuid());
        onAdd(elem);
    }
};

} // namespace Meshler

#endif // MESHLER_MPRESENTER_HPP
