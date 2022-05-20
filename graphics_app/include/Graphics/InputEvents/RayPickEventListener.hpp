#ifndef GRAPHICS_RAYPICKEVENTLISTENER_HPP
#define GRAPHICS_RAYPICKEVENTLISTENER_HPP

#include <Graphics/InputEvents/PickRayEvent.hpp>
#include <Graphics/InputEvents/PickRayMoveEvent.hpp>

namespace Graphics
{

class RayPickEventListener {
  public:
    virtual ~RayPickEventListener() = default;

    virtual void onRemoveRayPickEventListener(){};

    virtual void onEvent(const PickRayEvent& pickRayEvent){};
    virtual void onEvent(const PickRayMoveEvent& pickRayMoveEvent){};
};

} // namespace Graphics

#endif // GRAPHICS_RAYPICKEVENTLISTENER_HPP
