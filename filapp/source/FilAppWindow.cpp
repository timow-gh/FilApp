#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppWindow.hpp>
#include <NativeWindowHelper.hpp>
#include <SDL_video.h>
#include <utils/EntityManager.h>

using namespace Graphics;

namespace FilApp
{

FilAppWindow::FilAppWindow(const WindowConfig& windowConfig, filament::Engine* engine)
{
    m_engine = engine;

    std::uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
    if (windowConfig.isResizable)
        windowFlags |= SDL_WINDOW_RESIZABLE;
    if (windowConfig.isHeadless)
        windowFlags |= SDL_WINDOWEVENT_HIDDEN;

    const std::int32_t x = SDL_WINDOWPOS_CENTERED;
    const std::int32_t y = SDL_WINDOWPOS_CENTERED;
    m_sdlWindow = SDL_CreateWindow(windowConfig.windowName.c_str(),
                                   x,
                                   y,
                                   static_cast<std::int32_t>(windowConfig.width),
                                   static_cast<std::int32_t>(windowConfig.height),
                                   windowFlags);

    m_windowId = SDL_GetWindowID(m_sdlWindow);

    if (windowConfig.isHeadless)
    {
        m_width = windowConfig.width;
        m_height = windowConfig.height;
        m_swapChain = m_engine->createSwapChain(m_width, m_height);
    }
    else
    {
        m_backend = m_engine->getBackend();

        void* nativeWindow = ::getNativeWindow(m_sdlWindow);
        void* nativeSwapChain = nativeWindow;
        m_swapChain = m_engine->createSwapChain(nativeSwapChain);
    }

    m_renderer = m_engine->createRenderer();

    ViewConfig viewConfig;
    viewConfig.name = "MainView";
    viewConfig.viewport = calcWindowViewport();
    m_mainView = std::make_unique<FilAppCameraView>(viewConfig, *m_renderer);
}

InputEventDispatcher& FilAppWindow::getInputEventDispatcher()
{
    return m_inputEventDispatcher;
}

RayPickEventDispatcher& FilAppWindow::getRayPickEventDispatcher()
{
    return m_rayPickEventDispatcher;
}

void FilAppWindow::event(const MouseButtonEvent& evt)
{
    m_mainView->onEvent(evt);
    for (const auto& view: m_views)
    {
        if (intersects(view->getViewport(), evt.x, evt.y))
        {
            view->onEvent(evt);
            break;
        }
    }
}

void FilAppWindow::event(const MouseMoveEvent& evt)
{
    m_mainView->onEvent(evt);
    for (const auto& view: m_views)
    {
        if (intersects(view->getViewport(), evt.x, evt.y))
        {
            view->onEvent(evt);
            break;
        }
    }
    m_lastX = evt.x;
    m_lastY = evt.y;
}

void FilAppWindow::event(const KeyEvent& keyEvent)
{
    switch (keyEvent.type)
    {
    case KeyEvent::Type::PUSH:
    {
        auto& eventTarget = m_keyEventTarget[toSDLScancode(keyEvent.keyScancode)];

        // onEvent events can be sent multiple times per key (for key repeat)
        // If this key is already down, do nothing.
        if (eventTarget)
            return;

        // Decide which view will get this key's corresponding event onEvent.
        // If we're currently in a mouse grap session, it should be the mouse grab's
        // target view. Otherwise, it should be whichever view we're currently
        // hovering over.
        m_mainView->onEvent(keyEvent);

        for (auto const& view: m_views)
        {
            if (intersects(view->getViewport(), m_lastX, m_lastY))
            {
                view->onEvent(keyEvent);
                break;
            }
        }
        break;
    }
    case KeyEvent::Type::RELEASE:
    {
        auto& eventTargetView = m_keyEventTarget[toSDLScancode(keyEvent.keyScancode)];
        if (!eventTargetView)
            return;
        eventTargetView->onEvent(keyEvent);
        eventTargetView = nullptr;
        break;
    }
    default: CORE_POSTCONDITION_DEBUG_ASSERT(false, "Key type not implemented.");
    }
}

void FilAppWindow::mouseWheel(float_t x, double_t deltaT)
{
    m_mainView->onEvent(MouseWheelEvent(x, deltaT));
    for (auto const& view: m_views)
    {
        if (intersects(view->getViewport(), m_lastX, m_lastY))
        {
            view->onEvent(MouseWheelEvent(x, deltaT));
            break;
        }
    }
}

FilAppWindow::~FilAppWindow()
{
    SDL_DestroyWindow(m_sdlWindow);
}

std::vector<View*> FilAppWindow::getViews()
{
    std::vector<View*> views;
    views.push_back(m_mainView.get());
    for (const auto& filappview: m_views)
        views.push_back(filappview.get());
    return views;
}

Window::WindowId FilAppWindow::getIWindowId()
{
    return m_windowId;
}

SDL_Window* FilAppWindow::getSdlWindow() const
{
    return m_sdlWindow;
}

uint32_t FilAppWindow::getWidth() const
{
    return m_width;
}

uint32_t FilAppWindow::getHeight() const
{
    return m_height;
}

filament::Renderer* FilAppWindow::getRenderer()
{
    return m_renderer;
}

filament::SwapChain* FilAppWindow::getSwapChain()
{
    return m_swapChain;
}

filament::math::int2 FilAppWindow::fixupMouseCoordinatesForHdpi(uint32_t x, uint32_t y) const

{
    int dw, dh, ww, wh;
    SDL_GL_GetDrawableSize(m_sdlWindow, &dw, &dh);
    SDL_GetWindowSize(m_sdlWindow, &ww, &wh);
    x = x * dw / ww;
    y = y * dh / wh;
    y = m_height - y;
    return filament::math::int2{x, y};
}

void FilAppWindow::resize()
{
    if (m_sdlWindow)
        m_mainView->resize(calcWindowViewport());
}

View* FilAppWindow::getMainIView()
{
    return m_mainView.get();
}

void FilAppWindow::render()
{
    if (m_renderer->beginFrame(getSwapChain()))
    {
        m_renderer->render(m_mainView->getFilamentView());
        for (auto const& view: m_views)
            m_renderer->render(view->getFilamentView());
        m_renderer->endFrame();
    }
}

void FilAppWindow::animate(double_t deltaT)
{
    if (auto mainViewManip = m_mainView->getCameraManipulator())
    {
        filament::math::float3 eye;
        filament::math::float3 center;
        filament::math::float3 up;
        mainViewManip->update(static_cast<float_t>(deltaT));
        mainViewManip->getLookAt(&eye, &center, &up);
        m_mainView->getCamera()->lookAt(eye, center, up);
    }

    for (auto& filappview: m_views)
        filappview->animate(deltaT);
}

bool intersects(const Viewport& viewport, size_t x, size_t y)
{
    if (x >= viewport.left && x < viewport.left + viewport.width)
        if (y >= viewport.bottom && y < viewport.bottom + viewport.height)
            return true;
    return false;
}

Viewport FilAppWindow::calcWindowViewport()
{
    SDL_GL_GetDrawableSize(m_sdlWindow, (int*)&m_width, (int*)&m_height);
    return {0, 0, static_cast<uint32_t>(m_width), static_cast<uint32_t>(m_height)};
}

} // namespace FilApp