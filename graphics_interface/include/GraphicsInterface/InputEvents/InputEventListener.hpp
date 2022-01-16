#ifndef FILAPP_INPUTEVENTLISTENER_HPP
#define FILAPP_INPUTEVENTLISTENER_HPP

#include <GraphicsInterface/InputEvents/KeyEvent.hpp>
#include <GraphicsInterface/InputEvents/ListenerBase.hpp>
#include <GraphicsInterface/InputEvents/MouseButtonEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseWheelEvent.hpp>

namespace Graphics
{
class InputEventListener : public ListenerBase {
  public:
    virtual void event(const MouseButtonEvent& mouseButtonEvent){};
    virtual void event(const MouseMoveEvent& mouseMovedEvent){};
    virtual void event(const MouseWheelEvent& mouseWheelEvent){};
    virtual void event(const KeyEvent& keyEvent){};
};
} // namespace Graphics

#endif // FILAPP_INPUTEVENTLISTENER_HPP
