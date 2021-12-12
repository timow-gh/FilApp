#ifndef FILAPP_VIEW_HPP
#define FILAPP_VIEW_HPP

#include <FilAppInterfaces/InputEvents/InputEventDispatcher.hpp>
#include <FilAppInterfaces/InputEvents/InputEventListener.hpp>
#include <FilAppInterfaces/InputEvents/RayPickEventDispatcher.hpp>
#include <FilAppInterfaces/InputEvents/RayPickEventListener.hpp>
#include <FilAppInterfaces/Renderables/LineRenderable.hpp>
#include <FilAppInterfaces/Renderables/PointRenderable.hpp>
#include <FilAppInterfaces/Renderables/RendereableId.hpp>
#include <FilAppInterfaces/Renderables/TriangleRenderable.hpp>
#include <FilAppInterfaces/Vec.hpp>
#include <FilAppInterfaces/Viewport.hpp>

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
    virtual void removeRenderable(RenderableId renderableIdentifier) = 0;
    virtual void clearRenderables() = 0;
    // clang-format on

    virtual void setUsePostprocessing(bool usePostProcessing) = 0;

    virtual void addRotationAnimation(RenderableId renderableIdentifier,
                                      const Vec3& rotationAxis) = 0;

    virtual void animate(double deltaT) = 0;
    [[nodiscard]] virtual Viewport getViewport() const = 0;
    virtual void resize(const Viewport& viewport) = 0;
};
} // namespace FilApp

#endif // FILAPP_VIEW_HPP
