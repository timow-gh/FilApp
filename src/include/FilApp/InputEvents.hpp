#ifndef FILAPP_INPUTEVENTS_HPP
#define FILAPP_INPUTEVENTS_HPP

#include "FilApp/EvtPos.hpp"
#include "FilApp/InputEvents.hpp"
#include <SDL_scancode.h>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filapp_export.h>

namespace FilApp
{
struct FILAPP_EXPORT MouseDownEvent
{
    int button;
    EvtPos pos;
    uint64_t timeStamp;

    MouseDownEvent(int button, size_t x, size_t y, uint64_t timeStamp)
        : button(button), pos(EvtPos(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseUpEvent
{
    EvtPos pos;
    uint64_t timeStamp;

    MouseUpEvent(size_t x, size_t y, uint64_t timeStamp)
        : pos(EvtPos(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseMovedEvent
{
    EvtPos pos;
    uint64_t timeStamp;

    MouseMovedEvent(size_t x, size_t y, uint64_t timeStamp)
        : pos(EvtPos(x, y)), timeStamp(timeStamp)
    {
    }
};

struct FILAPP_EXPORT MouseWheelEvent
{
    size_t x;
    uint64_t timeStamp;

    MouseWheelEvent(size_t x, uint64_t timeStamp) : x(x), timeStamp(timeStamp)
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

} // namespace FilApp

#endif // FILAPP_INPUTEVENTS_HPP
