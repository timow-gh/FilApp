#ifndef GRAPHICS_RAYPICKEVENTLISTENER_HPP
#define GRAPHICS_RAYPICKEVENTLISTENER_HPP

#include <Graphics/InputEvents/PickRayEvent.hpp>
#include <Graphics/InputEvents/PickRayMoveEvent.hpp>

namespace Graphics
{

class RayPickEventListener {
public:
  RayPickEventListener(const RayPickEventListener& view) = delete;

  virtual ~RayPickEventListener() = default;

  virtual void onRemoveRayPickEventListener() {}

  virtual void onEvent(const PickRayEvent&) {}
  virtual void onEvent(const PickRayMoveEvent&) {}

protected:
  RayPickEventListener() = default;
};

} // namespace Graphics

#endif // GRAPHICS_RAYPICKEVENTLISTENER_HPP
