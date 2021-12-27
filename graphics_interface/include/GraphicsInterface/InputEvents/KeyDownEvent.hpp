#ifndef FILAPP_KEYDOWNEVENT_HPP
#define FILAPP_KEYDOWNEVENT_HPP

#include <SDL_scancode.h>

namespace Graphics
{
struct KeyDownEvent
{
    SDL_Scancode sdlScancode;
    double_t time;

    KeyDownEvent(SDL_Scancode sdlScancode, double_t time)
        : sdlScancode(sdlScancode), time(time)
    {
    }
};
} // namespace FilApp

#endif // FILAPP_KEYDOWNEVENT_HPP
