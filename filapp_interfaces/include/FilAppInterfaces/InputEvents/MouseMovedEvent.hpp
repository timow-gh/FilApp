#ifndef FILAPP_MOUSEMOVEDEVENT_HPP
#define FILAPP_MOUSEMOVEDEVENT_HPP

#include <FilAppInterfaces/InputEvents/EvtPos.hpp>
#include <cmath>

namespace FilApp
{
struct MouseMovedEvent
{
    EvtPos pos;
    double_t time;

    MouseMovedEvent(size_t x, size_t y, double_t time)
        : pos(EvtPos(x, y)), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_MOUSEMOVEDEVENT_HPP
