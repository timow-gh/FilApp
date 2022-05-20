#ifndef GRAPHICS_GRAPHICSCONTROLLER_HPP
#define GRAPHICS_GRAPHICSCONTROLLER_HPP

#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/InputEvents/RayPickEventListener.hpp>

namespace Graphics
{

class GraphicsController
    : public InputEventListener
    , public RayPickEventListener {
  public:
    ~GraphicsController() override = default;
};

} // namespace Graphics

#endif // GRAPHICS_GRAPHICSCONTROLLER_HPP
