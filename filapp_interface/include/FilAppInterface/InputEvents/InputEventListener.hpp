#ifndef FILAPP_INPUTEVENTLISTENER_HPP
#define FILAPP_INPUTEVENTLISTENER_HPP

#include <FilAppInterface/InputEvents/KeyDownEvent.hpp>
#include <FilAppInterface/InputEvents/KeyUpEvent.hpp>
#include <FilAppInterface/InputEvents/MouseButtonEvent.hpp>
#include <FilAppInterface/InputEvents/MouseMoveEvent.hpp>
#include <FilAppInterface/InputEvents/MouseWheelEvent.hpp>

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
