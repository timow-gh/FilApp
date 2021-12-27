#ifndef FILAPP_RAYPICKEVENTLISTENER_HPP
#define FILAPP_RAYPICKEVENTLISTENER_HPP

#include <GraphicsInterface/InputEvents/PickRayEvent.hpp>
#include <GraphicsInterface/InputEvents/PickRayMoveEvent.hpp>

namespace FilApp
{

class RayPickEventListener {
  public:
    virtual ~RayPickEventListener() = default;

    virtual void event(const PickRayEvent& pickRayEvent){};
    virtual void event(const PickRayMoveEvent& pickRayMoveEvent){};
};

} // namespace FilApp

#endif // FILAPP_RAYPICKEVENTLISTENER_HPP
