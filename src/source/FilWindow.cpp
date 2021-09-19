#include "FilApp/FilWindow.hpp"
#include "FilAppConversion.hpp"
#include "NativeWindowHelper.hpp"
#include <SDL_video.h>
#include <utils/EntityManager.h>

namespace FilApp
{
FilWindow::FilWindow(const WindowConfig& windowConfig,
                     FilApplication* application)
{
    m_application = application;

    uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
    if (windowConfig.isResizable)
        windowFlags |= SDL_WINDOW_RESIZABLE;
    if (windowConfig.isHeadless)
        windowFlags |= SDL_WINDOWEVENT_HIDDEN;

    const int x = SDL_WINDOWPOS_CENTERED;
    const int y = SDL_WINDOWPOS_CENTERED;
    m_sdlWindow = SDL_CreateWindow(windowConfig.title.c_str(),
                                   x,
                                   y,
                                   windowConfig.width,
                                   windowConfig.height,
                                   windowFlags);

    m_windowId = SDL_GetWindowID(m_sdlWindow);

    if (windowConfig.isHeadless)
    {
        m_width = windowConfig.width;
        m_height = windowConfig.height;
        m_swapChain =
            m_application->getEngine()->createSwapChain(m_width, m_height);
    }
    else
    {
        m_backend = m_application->getEngine()->getBackend();

        void* nativeWindow = ::getNativeWindow(m_sdlWindow);
        void* nativeSwapChain = nativeWindow;

#if defined(__APPLE__)
        ::prepareNativeWindow(mWindow);

        void* metalLayer = nullptr;
        if (config.backend == filament::Engine::Backend::METAL)
        {
            metalLayer = setUpMetalLayer(nativeWindow);
            // The swap chain on Metal is a CAMetalLayer.
            nativeSwapChain = metalLayer;
        }

#if defined(FILAMENT_DRIVER_SUPPORTS_VULKAN)
        if (config.backend == filament::Engine::Backend::VULKAN)
        {
            // We request a Metal layer for rendering via MoltenVK.
            setUpMetalLayer(nativeWindow);
        }
#endif
#endif
        m_swapChain =
            m_application->getEngine()->createSwapChain(nativeSwapChain);
    }

    m_renderer = m_application->getEngine()->createRenderer();

    calcWindowViewport();
    m_views.emplace_back(std::make_unique<FilAppView>(
        *m_renderer,
        "Main Window",
        m_viewport,
        filament::math::float4{0.1, 0.125, 0.25, 1.0},
        calcCameraMode(windowConfig.cameraMode)));
    m_mainView = m_views.back().get();
}
void FilWindow::mouseDown(int button, size_t x, size_t y, double_t deltaT)
{
    fixupMouseCoordinatesForHdpi(x, y);
    y = m_height - y;
    for (const auto& view: m_views)
    {
        if (intersects(view->getViewport(), x, y))
        {
            m_mouseEventTarget = view.get();
            view->mouseDown(
                MouseDownEvent(button,
                               x,
                               y,
                               deltaT));
            break;
        }
    }
}
void FilWindow::mouseUp(size_t x, size_t y, double_t deltaT)
{
    fixupMouseCoordinatesForHdpi(x, y);
    if (m_mouseEventTarget)
    {
        y = m_height - y;
        m_mouseEventTarget->mouseUp(
            MouseUpEvent(x, y, deltaT));
        m_mouseEventTarget = nullptr;
    }
}
void FilWindow::mouseMoved(size_t x, size_t y, double_t deltaT)
{
    fixupMouseCoordinatesForHdpi(x, y);
    y = m_height - y;
    if (m_mouseEventTarget)
        m_mouseEventTarget->mouseMoved(
            MouseMovedEvent(x, y, deltaT));
    m_lastX = x;
    m_lastY = y;
}
void FilWindow::mouseWheel(size_t x, double_t deltaT)
{
    if (m_mouseEventTarget)
        m_mouseEventTarget->mouseWheel(
            MouseWheelEvent(x, deltaT));
    else
    {
        for (auto const& view: m_views)
        {
            if (intersects(view->getViewport(), m_lastX, m_lastY))
            {
                view->mouseWheel(
                    MouseWheelEvent(x, deltaT));
                break;
            }
        }
    }
}
void FilWindow::keyDown(SDL_Scancode scancode, double_t deltaT)
{
    auto& eventTarget = m_keyEventTarget[scancode];

    // keyDown events can be sent multiple times per key (for key repeat)
    // If this key is already down, do nothing.
    if (eventTarget)
    {
        return;
    }

    // Decide which view will get this key's corresponding keyUp event.
    // If we're currently in a mouse grap session, it should be the mouse grab's
    // target view. Otherwise, it should be whichever view we're currently
    // hovering over.
    FilAppView* targetView = nullptr;
    if (m_mouseEventTarget)
        targetView = m_mouseEventTarget;
    else
    {
        for (auto const& view: m_views)
        {
            if (intersects(view->getViewport(), m_lastX, m_lastY))
            {
                targetView = view.get();
                break;
            }
        }
    }

    if (targetView)
    {
        targetView->keyDown(
            KeyDownEvent(scancode, deltaT));
        eventTarget = targetView;
    }
}
void FilWindow::keyUp(SDL_Scancode scancode, double_t deltaT)
{
    auto& eventTargetView = m_keyEventTarget[scancode];
    if (!eventTargetView)
        return;
    eventTargetView->keyUp(KeyUpEvent(scancode, deltaT));
    eventTargetView = nullptr;
}
FilWindow::~FilWindow()
{
    m_views.clear();
    m_application->getEngine()->destroy(m_renderer);
    m_application->getEngine()->destroy(m_swapChain);
    SDL_DestroyWindow(m_sdlWindow);
}
std::vector<IView*> FilWindow::getIViews()
{
    std::vector<IView*> views;
    for (const auto& filappview: m_views)
        views.push_back(filappview.get());
    return views;
}
IWindow::WindowId FilWindow::getIWindowId()
{
    return m_windowId;
}
uint32_t FilWindow::getWidth() const
{
    return m_width;
}
uint32_t FilWindow::getHeight() const
{
    return m_height;
}
FilAppView* FilWindow::getMainFilAppView()
{
    return m_mainView;
}
filament::Renderer* FilWindow::getRenderer()
{
    return m_renderer;
}
filament::SwapChain* FilWindow::getSwapChain()
{
    return m_swapChain;
}
void FilWindow::resize()
{
    void* nativeWindow = ::getNativeWindow(m_sdlWindow);

#if defined(__APPLE__)
    if (mBackend == filament::Engine::Backend::METAL)
    {
        resizeMetalLayer(nativeWindow);
    }

#if defined(FILAMENT_DRIVER_SUPPORTS_VULKAN)
    if (mBackend == filament::Engine::Backend::VULKAN)
    {
        resizeMetalLayer(nativeWindow);
    }
#endif
#endif

    if (m_sdlWindow)
    {
        calcWindowViewport();
        m_mainView->resize(Viewport(m_viewport.left,
                                    m_viewport.bottom,
                                    m_viewport.width,
                                    m_viewport.height));
    }
}
IView* FilWindow::getMainIView()
{
    return m_mainView;
}
void FilWindow::render()
{
    if (m_renderer->beginFrame(getSwapChain()))
    {
        for (auto const& view: m_views)
            m_renderer->render(view->getFilamentView());
        m_renderer->endFrame();
    }
}
void FilWindow::animate(double_t deltaT)
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
void FilWindow::fixupMouseCoordinatesForHdpi(size_t& x, size_t& y) const
{
    int dw, dh, ww, wh;
    SDL_GL_GetDrawableSize(m_sdlWindow, &dw, &dh);
    SDL_GetWindowSize(m_sdlWindow, &ww, &wh);
    x = x * dw / ww;
    y = y * dh / wh;
}
void FilWindow::calcWindowViewport()
{
    SDL_GL_GetDrawableSize(m_sdlWindow, (int*)&m_width, (int*)&m_height);
    m_viewport = {0,
                  0,
                  static_cast<uint32_t>(m_width),
                  static_cast<uint32_t>(m_height)};
}
} // namespace FilApp