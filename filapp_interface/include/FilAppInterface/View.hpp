#ifndef FILAPP_VIEW_HPP
#define FILAPP_VIEW_HPP

#include <FilAppInterface/InputEvents/InputEventDispatcher.hpp>
#include <FilAppInterface/InputEvents/InputEventListener.hpp>
#include <FilAppInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <FilAppInterface/InputEvents/RayPickEventListener.hpp>
#include <FilAppInterface/Renderables/LineRenderable.hpp>
#include <FilAppInterface/Renderables/PointRenderable.hpp>
#include <FilAppInterface/Renderables/RendereableId.hpp>
#include <FilAppInterface/Renderables/TriangleRenderable.hpp>
#include <FilAppInterface/Vec.hpp>
#include <FilAppInterface/Viewport.hpp>

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
