#ifndef MESHLER_WINDOWEVENTLISTENER_HPP
#define MESHLER_WINDOWEVENTLISTENER_HPP

namespace Graphics
{

struct WindowCloseEvent;
struct WindowMinimizeEvent;
struct WindowMaximizeEvent;
struct WindowResizeEvent;

class WindowEventListener {
public:
  WindowEventListener() = default;
  WindowEventListener(const WindowEventListener&) = delete;
  virtual ~WindowEventListener();

  virtual void onEvent(const WindowCloseEvent&) = 0;
  virtual void onEvent(const WindowMinimizeEvent&) = 0;
  virtual void onEvent(const WindowMaximizeEvent&) = 0;
  virtual void onEvent(const WindowResizeEvent&) = 0;

  virtual void onRemoveEventListener() = 0;
};

} // namespace Graphics

#endif // MESHLER_WINDOWEVENTLISTENER_HPP
