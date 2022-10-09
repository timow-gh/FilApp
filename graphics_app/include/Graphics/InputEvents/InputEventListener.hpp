#ifndef GRAPHICS_INPUTEVENTLISTENER_HPP
#define GRAPHICS_INPUTEVENTLISTENER_HPP

namespace Graphics
{

struct MouseButtonEvent;
struct MouseMoveEvent;
struct MouseWheelEvent;
struct KeyEvent;

class InputEventListener {
public:
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
