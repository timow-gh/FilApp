#ifndef FILAPP_IVIEW_H
#define FILAPP_IVIEW_H

#include "IInputListener.h"

namespace FilApp
{
class IView
    : public IInputListener
{
  public:
    virtual ~IView() = default;

    using RenderableIdentifier = uint32_t;
    virtual RenderableIdentifier
    addRenderable(const Renderable& renderable) = 0;
    virtual removeRenderable(RenderableIdentifier renderableIdentifier) = 0;
};
} // namespace FilApp

#endif // FILAPP_IVIEW_H
