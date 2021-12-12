#ifndef FILAPP_PICKRAYEVENT_HPP
#define FILAPP_PICKRAYEVENT_HPP

#include <FilAppInterfaces/Vec.hpp>
#include <cmath>

namespace FilApp
{
struct PickRayEvent
{
    Vec3 origin;
    Vec3 direction;
    double_t time;

    PickRayEvent(const Vec3& origin, const Vec3& direction, double_t time)
        : origin(origin), direction(direction), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_PICKRAYEVENT_HPP
