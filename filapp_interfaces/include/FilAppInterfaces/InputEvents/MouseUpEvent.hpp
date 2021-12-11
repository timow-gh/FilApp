#ifndef FILAPP_MOUSEUPEVENT_HPP
#define FILAPP_MOUSEUPEVENT_HPP

#include <FilAppInterfaces/InputEvents/EvtPos.hpp>
#include <cmath>

namespace FilApp
{
struct MouseUpEvent
{
    EvtPos pos;
    double_t time;

    MouseUpEvent(size_t x, size_t y, double_t time)
        : pos(EvtPos(x, y)), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_MOUSEUPEVENT_HPP
