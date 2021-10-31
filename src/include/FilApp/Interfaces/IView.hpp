#ifndef FILAPP_IVIEW_HPP
#define FILAPP_IVIEW_HPP

#include <FilApp/Interfaces/IInputEventDispatcher.hpp>
#include <FilApp/Interfaces/IInputListener.hpp>
#include <FilApp/Interfaces/Viewport.hpp>
#include <FilApp/Renderables/LineRenderable.hpp>
#include <FilApp/Renderables/PointRenderable.hpp>
#include <FilApp/Renderables/RendereableIdentifier.hpp>
#include <FilApp/Renderables/TriangleRenderable.hpp>
#include <FilApp/Vec3.hpp>
#include <filapp_export.h>

namespace FilApp
{

class FILAPP_EXPORT IView
    : public IInputListener
    , public IInputEventDispatcher
{
  public:
    ~IView() override = default;

    // clang-format off
    virtual auto addRenderable(TriangleRenderable&& renderable) -> RenderableIdentifier = 0;
    virtual auto addRenderable(PointRenderable&& renderable) -> RenderableIdentifier = 0;
    virtual auto addRenderable(LineRenderable&& renderable) -> RenderableIdentifier = 0;
    [[nodiscard]] virtual auto getRenderableIdentifiers() const -> std::vector<RenderableIdentifier> = 0;
    virtual void removeRenderable(RenderableIdentifier renderableIdentifier) = 0;
    virtual void clearRenderables() = 0;
    // clang-format on

    virtual void setUsePostprocessing(bool usePostProcessing) = 0;

    virtual void addRotationAnimation(RenderableIdentifier renderableIdentifier,
                                      const Vec3& rotationAxis) = 0;

    virtual void animate(double deltaT) = 0;
    [[nodiscard]] virtual Viewport getViewport() const = 0;
    virtual void resize(const Viewport& viewport) = 0;
};
} // namespace FilApp

#endif // FILAPP_IVIEW_HPP
