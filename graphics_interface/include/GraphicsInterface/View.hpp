#ifndef FILAPP_VIEW_HPP
#define FILAPP_VIEW_HPP

#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>
#include <GraphicsInterface/Renderables/LineRenderable.hpp>
#include <GraphicsInterface/Renderables/PointRenderable.hpp>
#include <GraphicsInterface/Renderables/RendereableId.hpp>
#include <GraphicsInterface/Renderables/TriangleRenderable.hpp>
#include <GraphicsInterface/Vec.hpp>
#include <GraphicsInterface/Viewport.hpp>

namespace FilApp
{

class View
    : public InputEventListener
    , public InputEventDispatcher
    , public RayPickEventDispatcher {
  public:
    ~View() override = default;

    // clang-format off
    virtual auto addRenderable(TriangleRenderable&& renderable) -> RenderableId = 0;
    virtual auto addRenderable(PointRenderable&& renderable) -> RenderableId = 0;
    virtual auto addRenderable(LineRenderable&& renderable) -> RenderableId = 0;
    [[nodiscard]] virtual auto getRenderableIdentifiers() const -> std::vector<RenderableId> = 0;
    virtual void removeRenderable(RenderableId renderableId) = 0;
    virtual void updatePosition(RenderableId renderableId, const Vec3& position) = 0;
    virtual void clearRenderables() = 0;
    // clang-format on

    // Prototype. Filament specific, will be removed
    virtual void setUsePostprocessing(bool usePostProcessing) = 0;

    // Animation prototype
    virtual void addRotationAnimation(RenderableId renderableIdentifier,
                                      const Vec3& rotationAxis) = 0;
    virtual void animate(double deltaT) = 0;

    [[nodiscard]] virtual Viewport getViewport() const = 0;
    virtual void resize(const Viewport& viewport) = 0;
};
} // namespace FilApp

#endif // FILAPP_VIEW_HPP
