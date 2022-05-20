#ifndef GRAPHICS_PICKRAYMOVEEVENT_HPP
#define GRAPHICS_PICKRAYMOVEEVENT_HPP

#include <Graphics/InputEvents/PickRayEvent.hpp>

namespace Graphics
{
struct PickRayMoveEvent : public PickRayEvent
{
    PickRayMoveEvent(const Vec3& origin, const Vec3& direction, double_t time)
        : PickRayEvent(origin, direction, time)
    {
    }
};
} // namespace Graphics

#endif // GRAPHICS_PICKRAYMOVEEVENT_HPP
