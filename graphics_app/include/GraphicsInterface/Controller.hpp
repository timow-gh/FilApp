#ifndef FILAPP_CONTROLLER_HPP
#define FILAPP_CONTROLLER_HPP

#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>

namespace Graphics
{

class Controller
    : public InputEventListener
    , public RayPickEventListener {
  public:
    ~Controller() override = default;
};

} // namespace Graphics

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
