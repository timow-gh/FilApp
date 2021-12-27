#ifndef FILAPP_KEYDOWNEVENT_HPP
#define FILAPP_KEYDOWNEVENT_HPP

#include <GraphicsInterface/InputEvents/KeyScancode.hpp>
#include <cmath>

namespace Graphics
{

struct KeyDownEvent
{
    KeyScancode keyScanCode;
    double_t time;

    KeyDownEvent(KeyScancode scanCode, double_t time)
        : keyScanCode(scanCode), time(time)
    {
    }
};

} // namespace Graphics

#endif // FILAPP_KEYDOWNEVENT_HPP
