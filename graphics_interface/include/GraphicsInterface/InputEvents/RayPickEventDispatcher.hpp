#ifndef FILAPP_RAYPICKEVENTDISPATCHER_HPP
#define FILAPP_RAYPICKEVENTDISPATCHER_HPP

#include <GraphicsInterface/InputEvents/DispatcherBase.hpp>

namespace Graphics
{
class RayPickEventListener;

class RayPickEventDispatcher : public DispatcherBase<RayPickEventListener> {
  public:
    using DispatcherBase<RayPickEventListener>::DispatcherBase;
};
} // namespace FilApp

#endif // FILAPP_RAYPICKEVENTDISPATCHER_HPP
