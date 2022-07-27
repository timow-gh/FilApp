#ifndef GRAPHICS_GRAPHICSAPP_HPP
#define GRAPHICS_GRAPHICSAPP_HPP

#include <Core/Utils/Compiler.hpp>

namespace Graphics
{

class Window;

class GraphicsApp {
  public:
    GraphicsApp(const GraphicsApp&) = default;

    virtual ~GraphicsApp();
    CORE_NODISCARD virtual Window& getWindow() = 0;
    virtual void run() = 0;

  protected:
    GraphicsApp() = default;
};

} // namespace Graphics

#endif // GRAPHICS_GRAPHICSAPP_HPP
