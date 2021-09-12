#ifndef FILAPP_VIEWEVENTS_HPP
#define FILAPP_VIEWEVENTS_HPP

#include <SDL_scancode.h>
#include <filapp_export.h>
#include <math/vec2.h>
#include <utils/compiler.h>

namespace FilApp
{

struct FILAPP_EXPORT MouseDownEvent
{
    int button;
    filament::math::vec2<ssize_t> pos;
    uint64_t timeStamp;

    MouseDownEvent(int button, ssize_t x, ssize_t y, uint64_t timeStamp)
        : button(button)
        , pos(filament::math::vec2<ssize_t>(x, y))
        , timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseUpEvent
{
    filament::math::vec2<ssize_t> pos;
    uint64_t timeStamp;

    MouseUpEvent(ssize_t x, ssize_t y, uint64_t timeStamp)
        : pos(filament::math::vec2<ssize_t>(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseMovedEvent
{
    filament::math::vec2<ssize_t> pos;
    uint64_t timeStamp;

    MouseMovedEvent(ssize_t x, ssize_t y, uint64_t timeStamp)
        : pos(filament::math::vec2<ssize_t>(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT KeyDownEvent
{
    SDL_Scancode sdlScancode;
    uint64_t timeStamp;

    KeyDownEvent(SDL_Scancode sdlScancode, uint64_t timeStamp)
        : sdlScancode(sdlScancode), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT KeyUpEvent
{
    SDL_Scancode sdlScancode;
    uint64_t timeStamp;

    KeyUpEvent(SDL_Scancode sdlScancode, uint64_t timeStamp)
        : sdlScancode(sdlScancode), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseScrollEvent
{
    float_t x;
    uint64_t timeStamp;

    MouseScrollEvent(float_t x, uint64_t timeStamp) : x(x), timeStamp(timeStamp)
    {
    }
};

} // namespace FilApp

#endif // FILAPP_VIEWEVENTS_HPP
