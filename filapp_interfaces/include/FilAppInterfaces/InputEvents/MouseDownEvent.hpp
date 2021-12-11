#ifndef FILAPP_MOUSEDOWNEVENT_HPP
#define FILAPP_MOUSEDOWNEVENT_HPP

#include <FilAppInterfaces/InputEvents/EvtPos.hpp>
#include <cmath>

namespace FilApp
{
struct MouseDownEvent
{
    int32_t button;
    EvtPos pos;
    double_t time;

    MouseDownEvent(int32_t button, size_t x, size_t y, double_t time)
        : button(button), pos(EvtPos(x, y)), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_MOUSEDOWNEVENT_HPP
