#ifndef GRAPHICS_WINDOW_HPP
#define GRAPHICS_WINDOW_HPP

#include <Core/Utils/Compiler.hpp>
#include <Graphics/Command.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/WindowEventListener.hpp>

namespace Graphics
{
class View;

class Window
    : public WindowEventListener
    , public InputEventListener {
public:
  Window(const Window&) = delete;
  ~Window() override;

  using WindowId = std::uint32_t;
  CORE_NODISCARD virtual WindowId getWindowId() const = 0;

  CORE_NODISCARD virtual View& getMainView() = 0;
  virtual void registerCommand(const Command& command) = 0;

protected:
  Window() = default;
};
} // namespace Graphics

#endif // GRAPHICS_WINDOW_HPP
