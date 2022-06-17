#ifndef GRAPHICS_PICKRAYMOVEEVENT_HPP
#define GRAPHICS_PICKRAYMOVEEVENT_HPP

#include <Graphics/InputEvents/PickRayEvent.hpp>

namespace Graphics
{
struct PickRayMoveEvent : public PickRayEvent
{
    PickRayMoveEvent(const Vec3& originVec, const Vec3& directionVec, double_t ttime)
        : PickRayEvent(originVec, directionVec, ttime)
    {
    }
};
} // namespace Graphics

#endif // GRAPHICS_PICKRAYMOVEEVENT_HPP
