#ifndef FILAPP_MOUSEWHEELEVENT_HPP
#define FILAPP_MOUSEWHEELEVENT_HPP

#include <cmath>

namespace Graphics
{
struct MouseWheelEvent
{
    float_t x;
    double_t time;

    MouseWheelEvent(float_t x, double_t time) : x(x), time(time) {}
};
} // namespace FilApp

#endif // FILAPP_MOUSEWHEELEVENT_HPP
