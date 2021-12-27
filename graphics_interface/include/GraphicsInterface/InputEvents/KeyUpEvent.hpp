#ifndef FILAPP_KEYUPEVENT_HPP
#define FILAPP_KEYUPEVENT_HPP

#include <GraphicsInterface/InputEvents/KeyScancode.hpp>
#include <cmath>

namespace Graphics
{
struct KeyUpEvent
{
    KeyScancode keyScancode;
    double_t deltaT;

    KeyUpEvent(KeyScancode keyScancode, double_t deltaT)
        : keyScancode(keyScancode), deltaT(deltaT)
    {
    }
};
} // namespace Graphics

#endif // FILAPP_KEYUPEVENT_HPP
