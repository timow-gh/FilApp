#ifndef FILAPP_NATIVEWINDOWHELPER_HPP
#define FILAPP_NATIVEWINDOWHELPER_HPP

struct SDL_Window;

extern "C" void* getNativeWindow(SDL_Window* sdlWindow);

#endif // FILAPP_NATIVEWINDOWHELPER_HPP
