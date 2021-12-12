#ifndef FILAPP_IINPUTEVENTLISTENER_HPP
#define FILAPP_IINPUTEVENTLISTENER_HPP

#include <FilAppInterfaces/InputEvents/KeyDownEvent.hpp>
#include <FilAppInterfaces/InputEvents/KeyUpEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseDownEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseMoveEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseUpEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseWheelEvent.hpp>

namespace FilApp
{
class IInputEventListener {
  public:
    virtual ~IInputEventListener() = default;

    virtual void mouseDown(const MouseDownEvent& mouseDownEvent) = 0;
    virtual void mouseUp(const MouseUpEvent& mouseUpEvent) = 0;
    virtual void mouseMove(const MouseMoveEvent& mouseMovedEvent) = 0;
    virtual void mouseWheel(const MouseWheelEvent& mouseWheelEvent) = 0;
    virtual void keyDown(const KeyDownEvent& keyDownEvent) = 0;
    virtual void keyUp(const KeyUpEvent& keyUpEvent) = 0;
};
} // namespace FilApp

#endif // FILAPP_IINPUTEVENTLISTENER_HPP
