#ifndef FILAPP_INPUTEVENTDISPATCHER_HPP
#define FILAPP_INPUTEVENTDISPATCHER_HPP

#include <GraphicsInterface/InputEvents/DispatcherBase.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/KeyDownEvent.hpp>
#include <GraphicsInterface/InputEvents/KeyUpEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseButtonEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseWheelEvent.hpp>

namespace Graphics
{
class InputEventDispatcher : public DispatcherBase<InputEventListener> {
  public:
    using DispatcherBase<InputEventListener>::DispatcherBase;

    void dispatch(const MouseButtonEvent& mouseButtonEvent) { dispatchImpl(mouseButtonEvent); };
    void dispatch(const MouseMoveEvent& mouseMovedEvent) { dispatchImpl(mouseMovedEvent); };
    void dispatch(const MouseWheelEvent& mouseWheelEvent) { dispatchImpl(mouseWheelEvent); };
    void dispatch(const KeyUpEvent& keyUpEvent) { dispatchImpl(keyUpEvent); };
    void dispatch(const KeyDownEvent& keyUpEvent) { dispatchImpl(keyUpEvent); };
};
} // namespace Graphics

#endif // FILAPP_INPUTEVENTDISPATCHER_HPP
