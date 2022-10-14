#ifndef GRAPHICS_GRAPHICSAPP_HPP
#define GRAPHICS_GRAPHICSAPP_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <cstdint>

namespace Graphics
{

class Window;
class WindowEventDispatcher;
class InputEventDispatcher;
class WindowConfig;

class GraphicsApp {
public:
  using WindowId = std::uint32_t;

  GraphicsApp(const GraphicsApp&) = default;

  virtual ~GraphicsApp();

  CORE_NODISCARD virtual Window& createWindow(const Graphics::WindowConfig& windowConfig) = 0;
  CORE_NODISCARD virtual Core::TVector<WindowId> getWindowIds() = 0;
  CORE_NODISCARD virtual Window& getWindow(WindowId windowId) = 0;

  CORE_NODISCARD virtual WindowEventDispatcher& getWindowEventDispatcher() = 0;
  CORE_NODISCARD virtual InputEventDispatcher& getInputEventDispatcher() = 0;

  virtual void run() = 0;

protected:
  GraphicsApp() = default;
};

} // namespace Graphics

#endif // GRAPHICS_GRAPHICSAPP_HPP
