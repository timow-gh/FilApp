#ifndef FILAPP_GRAPHICSCONTROLLER_HPP
#define FILAPP_GRAPHICSCONTROLLER_HPP

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

#endif // FILAPP_GRAPHICSCONTROLLER_HPP
