#ifndef FILAPP_MOUSEBUTTONEVENT_HPP
#define FILAPP_MOUSEBUTTONEVENT_HPP

#include <cmath>
#include <cstdint>

namespace FilApp
{

struct MouseButtonEvent
{
    enum class Type
    {
        PUSH,
        REPEAT,
        RELEASE
    };

    Type type;
    std::uint32_t buttonIndex;
    std::uint32_t timestamp; // in milliseconds
    std::uint32_t windowId;
    std::uint32_t clicks; // 1: single-click, 2: double-click
    std::uint32_t x;
    std::uint32_t y;
    double_t deltaT;

    MouseButtonEvent(Type type,
                     uint32_t buttonIndex,
                     uint32_t timestamp,
                     uint32_t windowId,
                     uint32_t clicks,
                     uint32_t x,
                     uint32_t y,
                     double_t deltaT)
        : type(type)
        , buttonIndex(buttonIndex)
        , timestamp(timestamp)
        , windowId(windowId)
        , clicks(clicks)
        , x(x)
        , y(y)
        , deltaT(deltaT)
    {
    }
};

} // namespace FilApp

#endif // FILAPP_MOUSEBUTTONEVENT_HPP
