#ifndef GRAPHICS_PICKRAYEVENT_HPP
#define GRAPHICS_PICKRAYEVENT_HPP

#include <Graphics/Vec.hpp>
#include <cmath>

namespace Graphics
{
struct PickRayEvent
{
  Vec3 origin;
  Vec3 direction;
  double_t time;

  PickRayEvent(const Vec3& origin, const Vec3& direction, double_t time)
      : origin(origin)
      , direction(direction)
      , time(time)
  {
  }
};
} // namespace Graphics

#endif // GRAPHICS_PICKRAYEVENT_HPP
