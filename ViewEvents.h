#ifndef FILAPP_VIEWEVENTS_H
#define FILAPP_VIEWEVENTS_H

#include <SDL_scancode.h>
#include <math/vec2.h>
#include <utils/compiler.h>

namespace FilApp
{
using vec2 = filament::math::vec2<ssize_t>;

struct MouseDownEvent
{
    int button;
    vec2 pos;
    std::uint64_t timeStamp;

    MouseDownEvent(int button, ssize_t x, ssize_t y, uint64_t timeStamp)
        : button(button), pos(vec2(x, y)), timeStamp(timeStamp)
    {
    }
};

struct MouseUpEvent
{
    vec2 pos;
    std::uint64_t timeStamp;

    MouseUpEvent(ssize_t x, ssize_t y, uint64_t timeStamp)
        : pos(vec2(x, y)), timeStamp(timeStamp)
    {
    }
};

struct MouseMovedEvent
{
    vec2 pos;
    std::uint64_t timeStamp;

    MouseMovedEvent(ssize_t x, ssize_t y, uint64_t timeStamp)
        : pos(vec2(x, y)), timeStamp(timeStamp)
    {
    }
};

struct KeyDownEvent
{
    SDL_Scancode sdlScancode;
    std::uint64_t timeStamp;

    KeyDownEvent(SDL_Scancode sdlScancode, uint64_t timeStamp)
        : sdlScancode(sdlScancode), timeStamp(timeStamp)
    {
    }
};

struct KeyUpEvent
{
    SDL_Scancode sdlScancode;
    std::uint64_t timeStamp;

    KeyUpEvent(SDL_Scancode sdlScancode, uint64_t timeStamp)
        : sdlScancode(sdlScancode), timeStamp(timeStamp)
    {
    }
};

struct MouseScrollEvent
{
    float_t x;
    std::uint64_t timeStamp;

    MouseScrollEvent(float_t x, uint64_t timeStamp) : x(x), timeStamp(timeStamp)
    {
    }
};

} // namespace FilApp

#endif // FILAPP_VIEWEVENTS_H
