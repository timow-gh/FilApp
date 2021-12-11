#ifndef FILAPP_KEYUPEVENT_HPP
#define FILAPP_KEYUPEVENT_HPP

#include <SDL_scancode.h>
#include <cmath>

namespace FilApp
{
struct KeyUpEvent
{
    SDL_Scancode sdlScancode;
    double_t time;

    KeyUpEvent(SDL_Scancode sdlScancode, double_t time)
        : sdlScancode(sdlScancode), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_KEYUPEVENT_HPP
