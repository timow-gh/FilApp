#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppWindow.hpp>
#include <FilApp/FilApplication.hpp>
#include <SDL.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <memory>
#include <utils/Panic.h>

namespace Graphics
{
double_t FilApplication::m_prevTimeStep = 0;

std::shared_ptr<Graphics::GraphicsApp> FilApplication::getFilApp(const AppConfig& appConfig,
                                                                 const WindowConfig& windowConfig)
{
    ASSERT_POSTCONDITION(SDL_Init(SDL_INIT_EVENTS) == 0, "SDL_Init Failure");

    static std::shared_ptr<FilApplication> filApp =
        std::make_unique<FilApplication>(appConfig, windowConfig);
    return filApp;
}

FilApplication::~FilApplication()
{
    m_window.reset();
    SDL_Quit();
}

filament::Engine* FilApplication::getEngine()
{
    return m_engine;
}

Window* FilApplication::getWindow()
{
    return m_window.get();
}

double_t FilApplication::getDeltaT()
{
    return (double_t)SDL_GetPerformanceCounter() / (double_t)SDL_GetPerformanceFrequency() -
           m_prevTimeStep;
}

void FilApplication::run()
{
    m_prevTimeStep =
        (double_t)SDL_GetPerformanceCounter() / (double_t)SDL_GetPerformanceFrequency();

    EventPollingMode eventPollingMode = m_appConfig.eventPollingMode;
    while (!m_closeApp)
    {
        double_t deltaT = FilApplication::getDeltaT();

        SDL_Event sdlEvent;

        switch (eventPollingMode)
        {
        case EventPollingMode::POLL_EVENTS: SDL_PollEvent(&sdlEvent); break;
        case EventPollingMode::WAIT_EVENTS: SDL_WaitEvent(&sdlEvent); break;
        }

        switch (sdlEvent.type)
        {
        case SDL_QUIT: m_closeApp = true; break;
        case SDL_KEYDOWN:
        {
            if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                m_closeApp = true;
            m_window->event(KeyEvent(KeyEvent::Type::PUSH,
                                     toKeyScancode(sdlEvent.key.keysym.scancode),
                                     sdlEvent.key.timestamp,
                                     sdlEvent.key.windowID,
                                     deltaT));
            break;
        }
        case SDL_KEYUP:
        {
            m_window->event(KeyEvent(KeyEvent::Type::RELEASE,
                                     toKeyScancode(sdlEvent.key.keysym.scancode),
                                     sdlEvent.key.timestamp,
                                     sdlEvent.key.windowID,
                                     deltaT));
            break;
        }
        case SDL_MOUSEWHEEL:
            m_window->mouseWheel(static_cast<float_t>(sdlEvent.wheel.y), deltaT);
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            filament::math::int2 pos =
                                      m_window->fixupMouseCoordinatesForHdpi(sdlEvent.button.x, sdlEvent.button.y);
                                  m_window->event(MouseButtonEvent(MouseButtonEvent::Type::PUSH,
                                                                   sdlEvent.button.button,
                                                                   sdlEvent.button.timestamp,
                                                                   sdlEvent.button.windowID,
                                                                   sdlEvent.button.clicks,
                                                                   pos.x,
                                                                   pos.y,
                                             deltaT));
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            filament::math::int2 pos =
                m_window->fixupMouseCoordinatesForHdpi(sdlEvent.button.x, sdlEvent.button.y);
            m_window->event(MouseButtonEvent(MouseButtonEvent::Type::RELEASE,
                                             sdlEvent.button.button,
                                             sdlEvent.button.timestamp,
                                             sdlEvent.button.windowID,
                                             sdlEvent.button.clicks,
                                             pos.x,
                                             pos.y,
                                             deltaT));
            break;
        }
        case SDL_MOUSEMOTION:
        {
            filament::math::int2 pos =
                m_window->fixupMouseCoordinatesForHdpi(sdlEvent.button.x, sdlEvent.button.y);
            m_window->event(MouseMoveEvent(sdlEvent.button.timestamp,
                                           sdlEvent.button.windowID,
                                           pos.x,
                                           pos.y,
                                           deltaT));
            break;
        }
        case SDL_WINDOWEVENT:
        {
            if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                m_window->resize();
            break;
        }
        default:
        {
            break;
        }
        }

        m_window->animate(deltaT);
        m_window->render();
    }
}

FilApplication::FilApplication(const AppConfig& appConfig, const WindowConfig& windowConfig)
    : m_appConfig(appConfig)
{
    m_engine = filament::Engine::create(toFilamentBackend(appConfig.backendMode));
    m_window = std::make_unique<FilAppWindow>(windowConfig, m_engine);
    m_appConfig = appConfig;
}

} // namespace Graphics
