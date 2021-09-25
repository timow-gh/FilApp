#include "FilApp/FilApplication.hpp"
#include "FilApp/FilAppWindow.hpp"
#include "FilAppConversion.hpp"
#include <SDL.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <memory>
#include <utils/Panic.h>

namespace FilApp
{
std::unique_ptr<FilApplication> FilApplication::m_app;
double_t FilApplication::m_prevTimeStep = 0;

void FilApplication::init(const AppConfig& appConfig,
                          const WindowConfig& windowConfig)
{
    ASSERT_POSTCONDITION(SDL_Init(SDL_INIT_EVENTS) == 0, "SDL_Init Failure");
    m_app = std::make_unique<FilApplication>();
    m_app->m_engine =
        filament::Engine::create(calcFilamentBackend(appConfig.backendMode));
    m_app->m_window =
        std::make_unique<FilAppWindow>(windowConfig, &FilApplication::get());
}
FilApplication::~FilApplication()
{
    m_window.reset();
    filament::Engine::destroy(&m_engine);
    m_engine = nullptr;
    SDL_Quit();
}
FilApplication& FilApplication::get()
{
    return *m_app;
}
filament::Engine* FilApplication::getEngine()
{
    return m_engine;
}
IWindow* FilApplication::getWindow()
{
    return m_window.get();
}
double_t FilApplication::getDeltaT()
{
    return (double_t)SDL_GetPerformanceCounter() /
               (double_t)SDL_GetPerformanceFrequency() -
           m_prevTimeStep;
}
void FilApplication::run()
{
    m_prevTimeStep = (double_t)SDL_GetPerformanceCounter() /
                     (double_t)SDL_GetPerformanceFrequency();

    while (!m_closeApp)
    {
        double_t deltaT = FilApplication::getDeltaT();

        constexpr Uint32 K_MAX_EVENTS = 4;
        SDL_Event events[K_MAX_EVENTS];
        Uint32 nevents = 0;
        while (nevents < K_MAX_EVENTS && SDL_PollEvent(&events[nevents]) != 0)
            nevents++;

        for (Uint32 i = 0; i < nevents; i++)
        {
            const SDL_Event& event = events[i];

            // TODO Support for multiple windows. Use IWindow::WindowId

            switch (event.type)
            {
            case SDL_QUIT: m_closeApp = true; break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    m_closeApp = true;
                m_window->keyDown(event.key.keysym.scancode, deltaT);
                break;
            case SDL_KEYUP:
                m_window->keyUp(event.key.keysym.scancode, deltaT);
                break;
            case SDL_MOUSEWHEEL:
                m_window->mouseWheel(event.wheel.y, deltaT);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_window->mouseDown(event.button.button,
                                    event.button.x,
                                    event.button.y,
                                    deltaT);
                break;
            case SDL_MOUSEBUTTONUP:
                m_window->mouseUp(event.button.x, event.button.y, deltaT);
                break;
            case SDL_MOUSEMOTION:
                m_window->mouseMoved(event.motion.x, event.motion.y, deltaT);
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED: m_window->resize(); break;
                default: break;
                }
                break;
            default: break;
            }
        }

        // TODO SDL_Delay.
        SDL_Delay(1);

        m_window->animate(deltaT);
        m_window->render();
    }
}
} // namespace FilApp
