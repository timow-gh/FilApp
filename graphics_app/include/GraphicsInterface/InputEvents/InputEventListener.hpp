#ifndef FILAPP_INPUTEVENTLISTENER_HPP
#define FILAPP_INPUTEVENTLISTENER_HPP

#include <GraphicsInterface/InputEvents/KeyEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseButtonEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/MouseWheelEvent.hpp>

namespace Graphics
{
class InputEventListener {
  public:
    virtual ~InputEventListener() = default;

    virtual void onRemoveInputEventListener(){};

    virtual void onEvent(const MouseButtonEvent& mouseButtonEvent){};
    virtual void onEvent(const MouseMoveEvent& mouseMovedEvent){};
    virtual void onEvent(const MouseWheelEvent& mouseWheelEvent){};
    virtual void onEvent(const KeyEvent& keyEvent){};
};
} // namespace Graphics

#endif // FILAPP_INPUTEVENTLISTENER_HPP
