#ifndef FILAPP_KEYEVENT_HPP
#define FILAPP_KEYEVENT_HPP

#include <GraphicsInterface/InputEvents/KeyScancode.hpp>
#include <cmath>
#include <cstdint>

namespace Graphics
{

struct KeyEvent
{
    enum class Type
    {
        PUSH,
        RELEASE
    };

    Type type;
    Graphics::KeyScancode keyScancode;
    std::uint32_t timestamp; // in milliseconds
    std::uint32_t windowId;
    double_t deltaT;

    KeyEvent(Type type,
             KeyScancode keyScancode,
             uint32_t timestamp,
             uint32_t windowId,
             double_t deltaT)
        : type(type)
        , keyScancode(keyScancode)
        , timestamp(timestamp)
        , windowId(windowId)
        , deltaT(deltaT)
    {
    }
};

} // namespace Graphics

#endif // FILAPP_KEYEVENT_HPP
