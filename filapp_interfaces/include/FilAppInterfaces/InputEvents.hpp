#ifndef FILAPP_INPUTEVENTS_HPP
#define FILAPP_INPUTEVENTS_HPP

#include "InputEvents.hpp"
#include <SDL_scancode.h>
#include <cmath>
#include <cstddef>
#include <cstdint>


namespace FilApp
{
struct  EvtPos
{
    size_t x;
    size_t y;

    EvtPos(size_t x, size_t y) : x(x), y(y) {}
};

struct  MouseDownEvent
{
    int button;
    EvtPos pos;
    double_t time;

    MouseDownEvent(int button, size_t x, size_t y, double_t time)
        : button(button), pos(EvtPos(x, y)), time(time)
    {
    }
};

struct  MouseUpEvent
{
    EvtPos pos;
    double_t time;

    MouseUpEvent(size_t x, size_t y, double_t time)
        : pos(EvtPos(x, y)), time(time)
    {
    }
};

struct  MouseMovedEvent
{
    EvtPos pos;
    double_t time;

    MouseMovedEvent(size_t x, size_t y, double_t time)
        : pos(EvtPos(x, y)), time(time)
    {
    }
};

struct  MouseWheelEvent
{
    float_t x;
    double_t time;

    MouseWheelEvent(float_t x, double_t time) : x(x), time(time) {}
};

struct  KeyDownEvent
{
    SDL_Scancode sdlScancode;
    double_t time;

    KeyDownEvent(SDL_Scancode sdlScancode, double_t time)
        : sdlScancode(sdlScancode), time(time)
    {
    }
};

struct  KeyUpEvent
{
    SDL_Scancode sdlScancode;
    double_t time;

    KeyUpEvent(SDL_Scancode sdlScancode, double_t time)
        : sdlScancode(sdlScancode), time(time)
    {
    }
};

} // namespace FilApp

#endif // FILAPP_INPUTEVENTS_HPP
