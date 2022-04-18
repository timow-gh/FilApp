#ifndef FILAPP_GRAPHICSCONTROLLER_HPP
#define FILAPP_GRAPHICSCONTROLLER_HPP

#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>

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
