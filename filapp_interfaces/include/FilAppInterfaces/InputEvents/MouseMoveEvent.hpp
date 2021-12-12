#ifndef FILAPP_MOUSEMOVEEVENT_HPP
#define FILAPP_MOUSEMOVEEVENT_HPP

#include <FilAppInterfaces/InputEvents/EvtPos.hpp>
#include <cmath>

namespace FilApp
{
struct MouseMoveEvent
{
    EvtPos pos;
    double_t time;

    MouseMoveEvent(size_t x, size_t y, double_t time)
        : pos(EvtPos(x, y)), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_MOUSEMOVEEVENT_HPP
