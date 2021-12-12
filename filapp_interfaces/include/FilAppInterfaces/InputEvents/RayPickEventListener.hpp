#ifndef FILAPP_RAYPICKEVENTLISTENER_HPP
#define FILAPP_RAYPICKEVENTLISTENER_HPP

#include <FilAppInterfaces/InputEvents/PickRayEvent.hpp>

namespace FilApp
{
class RayPickEventListener {
  public:
    virtual ~RayPickEventListener() = default;

    virtual void pickRayEvent(const PickRayEvent& pickRayEvent) = 0;
};
} // namespace FilApp

#endif // FILAPP_RAYPICKEVENTLISTENER_HPP
