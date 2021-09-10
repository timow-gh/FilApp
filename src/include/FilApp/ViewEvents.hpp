#ifndef FILAPP_VIEWEVENTS_HPP
#define FILAPP_VIEWEVENTS_HPP

#include <SDL_scancode.h>
#include <filapp_export.h>
#include <math/vec2.h>
#include <utils/compiler.h>

namespace FilApp
{
using vec2 = filament::math::vec2<ssize_t>;

struct FILAPP_EXPORT MouseDownEvent
{
    int button;
    vec2 pos;
    std::uint64_t timeStamp;

    MouseDownEvent(int button, ssize_t x, ssize_t y, uint64_t timeStamp)
        : button(button), pos(vec2(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseUpEvent
{
    vec2 pos;
    std::uint64_t timeStamp;

    MouseUpEvent(ssize_t x, ssize_t y, uint64_t timeStamp)
        : pos(vec2(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseMovedEvent
{
    vec2 pos;
    std::uint64_t timeStamp;

    MouseMovedEvent(ssize_t x, ssize_t y, uint64_t timeStamp)
        : pos(vec2(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT KeyDownEvent
{
    SDL_Scancode sdlScancode;
    std::uint64_t timeStamp;

    KeyDownEvent(SDL_Scancode sdlScancode, uint64_t timeStamp)
        : sdlScancode(sdlScancode), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT KeyUpEvent
{
    SDL_Scancode sdlScancode;
    std::uint64_t timeStamp;

    KeyUpEvent(SDL_Scancode sdlScancode, uint64_t timeStamp)
        : sdlScancode(sdlScancode), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseScrollEvent
{
    float_t x;
    std::uint64_t timeStamp;

    MouseScrollEvent(float_t x, uint64_t timeStamp) : x(x), timeStamp(timeStamp)
    {
    }
};

} // namespace FilApp

#endif // FILAPP_VIEWEVENTS_HPP
