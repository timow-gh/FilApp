#ifndef FILAPP_IINPUTEVENTLISTENER_HPP
#define FILAPP_IINPUTEVENTLISTENER_HPP

#include <FilAppInterfaces/InputEvents/InputEvents.hpp>

namespace FilApp
{
class IInputEventListener {
  public:
    virtual ~IInputEventListener() = default;

    virtual void mouseDown(const MouseDownEvent& mouseDownEvent) = 0;
    virtual void mouseUp(const MouseUpEvent& mouseUpEvent) = 0;
    virtual void mouseMoved(const MouseMovedEvent& mouseMovedEvent) = 0;
    virtual void mouseWheel(const MouseWheelEvent& mouseWheelEvent) = 0;
    virtual void keyDown(const KeyDownEvent& keyDownEvent) = 0;
    virtual void keyUp(const KeyUpEvent& keyUpEvent) = 0;
};
} // namespace FilApp

#endif // FILAPP_IINPUTEVENTLISTENER_HPP
