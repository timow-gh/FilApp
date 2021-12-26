#ifndef FILAPP_INPUTEVENTLISTENER_HPP
#define FILAPP_INPUTEVENTLISTENER_HPP

#include <FilAppInterfaces/InputEvents/KeyDownEvent.hpp>
#include <FilAppInterfaces/InputEvents/KeyUpEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseButtonEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseMoveEvent.hpp>
#include <FilAppInterfaces/InputEvents/MouseWheelEvent.hpp>

namespace FilApp
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
} // namespace FilApp

#endif // FILAPP_INPUTEVENTLISTENER_HPP
