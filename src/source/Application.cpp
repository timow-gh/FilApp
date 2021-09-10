#include "FilApp/Application.hpp"
#include "FilApp/Window.hpp"
#include <SDL.h>
#include <memory>
#include <utils/Panic.h>

namespace FilApp
{
std::unique_ptr<Application> Application::m_app;

void Application::init(const AppConfig& appConfig,
                       const WindowConfig& windowConfig)
{
    ASSERT_POSTCONDITION(SDL_Init(SDL_INIT_EVENTS) == 0, "SDL_Init Failure");
    m_app = std::make_unique<Application>();
    m_app->m_engine = filament::Engine::create(appConfig.backend);
    m_app->m_window =
        std::make_unique<Window>(windowConfig, &Application::get());
}
Application::~Application()
{
    m_window.reset();
    filament::Engine::destroy(&m_engine);
    m_engine = nullptr;
    SDL_Quit();
}
Application& Application::get()
{
    return *m_app;
}
filament::Engine* Application::getEngine()
{
    return m_engine;
}
Window* Application::getWindow()
{
    return m_window.get();
}
void Application::run()
{
    m_prevTimeStep = (double_t)SDL_GetPerformanceCounter() /
                     (double_t)SDL_GetPerformanceFrequency();
    while (!m_closeApp)
    {
        double_t now = (double_t)SDL_GetPerformanceCounter() /
                       (double_t)SDL_GetPerformanceFrequency();
        double_t timeStep = now - m_prevTimeStep;

        for (const auto& animationCallBack: m_window->getAnimationCallbacks())
            if (animationCallBack)
                animationCallBack(m_engine,
                                  m_window->getMainView()->getFilamentView(),
                                  timeStep);

        constexpr Uint32 K_MAX_EVENTS = 4;
        SDL_Event events[K_MAX_EVENTS];
        Uint32 nevents = 0;
        while (nevents < K_MAX_EVENTS && SDL_PollEvent(&events[nevents]) != 0)
            nevents++;

        for (Uint32 i = 0; i < nevents; i++)
        {
            const SDL_Event& event = events[i];
            switch (event.type)
            {
            case SDL_QUIT: m_closeApp = true; break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    m_closeApp = true;
                m_window->keyDown(event.key.keysym.scancode);
                break;
            case SDL_KEYUP: m_window->keyUp(event.key.keysym.scancode); break;
            case SDL_MOUSEWHEEL: m_window->mouseWheel(event.wheel.y); break;
            case SDL_MOUSEBUTTONDOWN:
                m_window->mouseDown(event.button.button,
                                    event.button.x,
                                    event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                m_window->mouseUp(event.button.x, event.button.y);
                break;
            case SDL_MOUSEMOTION:
                m_window->mouseMoved(event.motion.x, event.motion.y);
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


        auto mainView = m_window->getMainView();
        if (auto mainViewManip = mainView->getCameraManipulator())
        {
            filament::math::float3 eye;
            filament::math::float3 center;
            filament::math::float3 up;
            mainViewManip->update(timeStep);
            mainViewManip->getLookAt(&eye, &center, &up);
            mainView->getCamera()->lookAt(eye, center, up);
        }

        // TODO SDL_Delay.
        SDL_Delay(1);

        filament::Renderer* renderer = m_window->getRenderer();
        if (renderer->beginFrame(m_window->getSwapChain()))
        {
            for (auto const& view: m_window->getViews())
                renderer->render(view->getFilamentView());
            renderer->endFrame();
        }
    }
}
} // namespace FilApp
