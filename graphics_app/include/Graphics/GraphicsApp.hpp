#ifndef FILAPP_GRAPHICSAPP_HPP
#define FILAPP_GRAPHICSAPP_HPP

#include <Core/Utils/Compiler.hpp>
#include <Graphics/AppConfig.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/Window.hpp>
#include <Graphics/WindowConfig.hpp>
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
