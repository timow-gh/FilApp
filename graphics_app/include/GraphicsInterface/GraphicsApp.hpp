#ifndef FILAPP_GRAPHICSAPP_HPP
#define FILAPP_GRAPHICSAPP_HPP

#include <GraphicsInterface/Window.hpp>

namespace Graphics
{
class GraphicsApp {
  public:
    virtual ~GraphicsApp() = default;

    virtual Window* getWindow() = 0;
};
} // namespace Graphics

#endif // FILAPP_GRAPHICSAPP_HPP
