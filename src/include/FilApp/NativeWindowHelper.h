#ifndef FILAPP_NATIVEWINDOWHELPER_H
#define FILAPP_NATIVEWINDOWHELPER_H

struct SDL_Window;

extern "C" void* getNativeWindow(SDL_Window* sdlWindow);

#endif // FILAPP_NATIVEWINDOWHELPER_H
