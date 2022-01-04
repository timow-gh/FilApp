#ifndef FILAPP_INPUTEVENTLISTENER_HPP
#define FILAPP_INPUTEVENTLISTENER_HPP

#include <GraphicsInterface/InputEvents/KeyDownEvent.hpp>
#include <GraphicsInterface/InputEvents/KeyUpEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseButtonEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseWheelEvent.hpp>

namespace Graphics
{
class InputEventListener {
  public:
    virtual ~InputEventListener() = default;

    virtual void event(const MouseButtonEvent& mouseButtonEvent){};
    virtual void event(const MouseMoveEvent& mouseMovedEvent){};
    virtual void event(const MouseWheelEvent& mouseWheelEvent){};
    virtual void event(const KeyUpEvent& keyUpEvent){};
    virtual void event(const KeyDownEvent& keyUpEvent){};
};
} // namespace Graphics

#endif // FILAPP_INPUTEVENTLISTENER_HPP
