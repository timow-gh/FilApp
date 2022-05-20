#ifndef GRAPHICS_INPUTEVENTLISTENER_HPP
#define GRAPHICS_INPUTEVENTLISTENER_HPP

#include <Graphics/InputEvents/KeyEvent.hpp>
#include <Graphics/InputEvents/MouseButtonEvent.hpp>
#include <Graphics/InputEvents/MouseMoveEvent.hpp>
#include <Graphics/InputEvents/MouseWheelEvent.hpp>

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

#endif // GRAPHICS_INPUTEVENTLISTENER_HPP
