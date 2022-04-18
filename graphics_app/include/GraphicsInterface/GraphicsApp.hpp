#ifndef FILAPP_GRAPHICSAPP_HPP
#define FILAPP_GRAPHICSAPP_HPP

#include <Core/Utils/Compiler.hpp>
#include <GraphicsInterface/AppConfig.hpp>
#include <GraphicsInterface/InputEvents/InputEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <GraphicsInterface/Window.hpp>
#include <GraphicsInterface/WindowConfig.hpp>
#include <memory>

namespace Graphics
{

class GraphicsApp {
  public:
    virtual ~GraphicsApp() = default;
    CORE_NODISCARD virtual Window& getWindow() = 0;
    virtual void run() = 0;
};

} // namespace Graphics

#endif // FILAPP_GRAPHICSAPP_HPP
