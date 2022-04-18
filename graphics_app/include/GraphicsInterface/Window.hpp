#ifndef FILAPP_WINDOW_HPP
#define FILAPP_WINDOW_HPP

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
    virtual ~Window() = default;

    using WindowId = uint32_t;

    CORE_NODISCARD virtual View* getMainIView() = 0;
    CORE_NODISCARD virtual std::vector<View*> getIViews() = 0;

    CORE_NODISCARD virtual InputEventDispatcher& getInputEventDispatcher() = 0;
    CORE_NODISCARD virtual RayPickEventDispatcher& getRayPickEventDispatcher() = 0;

    virtual WindowId getIWindowId() = 0;
};
} // namespace Graphics

#endif // FILAPP_WINDOW_HPP
