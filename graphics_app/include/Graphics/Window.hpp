#ifndef GRAPHICS_WINDOW_HPP
#define GRAPHICS_WINDOW_HPP

#include <Core/Utils/Compiler.hpp>
#include <vector>

namespace Graphics
{
class View;
class InputEventDispatcher;
class RayPickEventDispatcher;
class WindowId;

class Window {
public:
  Window(const Window&) = delete;

  virtual ~Window();

  using WindowId = uint32_t;

  CORE_NODISCARD virtual View* getMainIView() = 0;
  CORE_NODISCARD virtual std::vector<View*> getViews() = 0;

  CORE_NODISCARD virtual InputEventDispatcher& getInputEventDispatcher() = 0;
  CORE_NODISCARD virtual RayPickEventDispatcher& getRayPickEventDispatcher() = 0;

  virtual WindowId getIWindowId() = 0;

protected:
  Window() = default;
};
} // namespace Graphics

#endif // GRAPHICS_WINDOW_HPP
