#ifndef FILAPP_KEYUPEVENT_HPP
#define FILAPP_KEYUPEVENT_HPP

#include <SDL_scancode.h>
#include <cmath>

namespace Graphics
{
struct KeyUpEvent
{
    SDL_Scancode sdlScancode;
    double_t deltaT;

    KeyUpEvent(SDL_Scancode sdlScancode, double_t deltaT)
        : sdlScancode(sdlScancode), deltaT(deltaT)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_KEYUPEVENT_HPP
