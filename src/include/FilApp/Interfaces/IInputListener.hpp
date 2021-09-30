#ifndef FILAPP_IINPUTLISTENER_HPP
#define FILAPP_IINPUTLISTENER_HPP

#include "InputEvents.hpp"
#include <filapp_export.h>

namespace FilApp
{
class FILAPP_EXPORT IInputListener
{
  public:
    virtual ~IInputListener() = default;

    virtual void mouseDown(const MouseDownEvent& mouseDownEvent) = 0;
    virtual void mouseUp(const MouseUpEvent& mouseUpEvent) = 0;
    virtual void mouseMoved(const MouseMovedEvent& mouseMovedEvent) = 0;
    virtual void mouseWheel(const MouseWheelEvent& mouseWheelEvent) = 0;
    virtual void keyDown(const KeyDownEvent& keyDownEvent) = 0;
    virtual void keyUp(const KeyUpEvent& keyUpEvent) = 0;
};
} // namespace FilApp

#endif // FILAPP_IINPUTLISTENER_HPP
