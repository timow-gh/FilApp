#ifndef FILAPP_GRAPHICSCONTROLLER_HPP
#define FILAPP_GRAPHICSCONTROLLER_HPP

#include <GraphicsInterface/InputController.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>

namespace Graphics
{

class GraphicsController
    : public InputController
    , public RayPickEventListener {
  public:
    virtual ~GraphicsController() = default;
};

} // namespace Graphics

#endif // FILAPP_GRAPHICSCONTROLLER_HPP
