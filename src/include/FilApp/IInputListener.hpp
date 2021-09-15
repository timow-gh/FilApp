#ifndef FILAPP_IINPUTLISTENER_HPP
#define FILAPP_IINPUTLISTENER_HPP

#include "FilApp/InputEvents.hpp"

namespace FilApp
{
class IInputListener
{
  public:
    virtual ~IInputListener() = default;

    virtual void mouseDown(const MouseDownEvent& mouseDownEvent) = 0;
    virtual void mouseUp(const MouseUpEvent& mouseUpEvent) const = 0;
    virtual void mouseMoved(const MouseMovedEvent& mouseMovedEvent) const = 0;
    virtual void mouseWheel(const MouseWheelEvent& mouseWheelEvent) const = 0;
    virtual void keyDown(const KeyDownEvent& keyDownEvent) const = 0;
    virtual void keyUp(const KeyUpEvent& keyUpEvent) const = 0;
};
} // namespace FilApp

#endif // FILAPP_IINPUTLISTENER_HPP
