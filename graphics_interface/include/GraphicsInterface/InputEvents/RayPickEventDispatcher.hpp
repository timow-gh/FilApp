#ifndef FILAPP_RAYPICKEVENTDISPATCHER_HPP
#define FILAPP_RAYPICKEVENTDISPATCHER_HPP

#include <GraphicsInterface/InputEvents/DispatcherBase.hpp>
#include <GraphicsInterface/InputEvents/PickRayEvent.hpp>
#include <GraphicsInterface/InputEvents/PickRayMoveEvent.hpp>

namespace Graphics
{
class RayPickEventListener;

class RayPickEventDispatcher : public DispatcherBase<RayPickEventListener> {
  public:
    using DispatcherBase<RayPickEventListener>::DispatcherBase;

    void dispatch(const PickRayEvent& pickRayEvent) { dispatchImpl(pickRayEvent); }
    void dispatch(const PickRayMoveEvent& pickRayMoveEvent) { dispatchImpl(pickRayMoveEvent); }
};
} // namespace Graphics

#endif // FILAPP_RAYPICKEVENTDISPATCHER_HPP
