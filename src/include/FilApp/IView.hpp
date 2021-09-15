#ifndef FILAPP_IVIEW_HPP
#define FILAPP_IVIEW_HPP

#include "FilApp/IInputListener.hpp"
#include "FilApp/Renderable.hpp"

namespace FilApp
{
class IView
    : public IInputListener
{
  public:
    ~IView() override = default;

    using RenderableIdentifier = uint32_t;

    // clang-format off
    virtual auto addRenderable(Renderable&& renderable) -> RenderableIdentifier = 0;
    virtual auto getRenderableIdentifiers() const -> std::vector<RenderableIdentifier> = 0;
    virtual void removeRenderable(RenderableIdentifier renderableIdentifier) = 0;
    virtual void clearRenderables() = 0;
    // clang-format on
};
} // namespace FilApp

#endif // FILAPP_IVIEW_HPP
