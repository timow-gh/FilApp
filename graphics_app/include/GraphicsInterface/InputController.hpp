#ifndef FILAPP_INPUTCONTROLLER_HPP
#define FILAPP_INPUTCONTROLLER_HPP

#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>

namespace Graphics
{

class InputController : public InputEventListener {
  public:
    ~InputController() override = default;
};

} // namespace Graphics

#endif // FILAPP_FLOWMESHCONTROLLER_HPP
