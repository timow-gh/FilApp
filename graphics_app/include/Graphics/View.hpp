#ifndef FILAPP_VIEW_HPP
#define FILAPP_VIEW_HPP

#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventListener.hpp>
#include <Graphics/Renderables/LineRenderable.hpp>
#include <Graphics/Renderables/PointRenderable.hpp>
#include <Graphics/Renderables/RendereableId.hpp>
#include <Graphics/Renderables/TriangleRenderable.hpp>
#include <Graphics/Vec.hpp>
#include <Graphics/Viewport.hpp>

namespace Graphics
{

class View : public InputEventListener {
  public:
    ~View() override = default;

    CORE_NODISCARD virtual InputEventDispatcher& getInputEventDispatcher() = 0;
    CORE_NODISCARD virtual RayPickEventDispatcher& getRayPickEventDispatcher() = 0;

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
} // namespace Graphics

#endif // FILAPP_VIEW_HPP
