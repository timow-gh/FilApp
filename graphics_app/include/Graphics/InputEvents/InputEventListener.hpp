#ifndef GRAPHICS_INPUTEVENTLISTENER_HPP
#define GRAPHICS_INPUTEVENTLISTENER_HPP

namespace Graphics
{

class MouseButtonEvent;
class MouseMoveEvent;
class MouseWheelEvent;
class KeyEvent;

class InputEventListener {
public:
  InputEventListener(const InputEventListener& view) = delete;

  virtual ~InputEventListener();

  virtual void onRemoveInputEventListener() {}

  virtual void onEvent(const MouseButtonEvent&) {}
  virtual void onEvent(const MouseMoveEvent&) {}
  virtual void onEvent(const MouseWheelEvent&) {}
  virtual void onEvent(const KeyEvent&) {}

protected:
  InputEventListener() = default;
};
} // namespace Graphics

#endif // GRAPHICS_INPUTEVENTLISTENER_HPP
