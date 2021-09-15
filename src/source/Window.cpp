#include "FilApp/Window.hpp"
#include "FilApp/FilAppConversion.hpp"
#include "FilApp/NativeWindowHelper.hpp"
#include <SDL_video.h>
#include <utils/EntityManager.h>

namespace FilApp
{
void Window::fixupMouseCoordinatesForHdpi(ssize_t& x, ssize_t& y) const
{
    int dw, dh, ww, wh;
    SDL_GL_GetDrawableSize(m_sdlWindow, &dw, &dh);
    SDL_GetWindowSize(m_sdlWindow, &ww, &wh);
    x = x * dw / ww;
    y = y * dh / wh;
}
void Window::calcWindowViewport()
{
    SDL_GL_GetDrawableSize(m_sdlWindow, (int*)&m_width, (int*)&m_height);
    m_viewport = {0,
                  0,
                  static_cast<uint32_t>(m_width),
                  static_cast<uint32_t>(m_height)};
}
Window::Window(const WindowConfig& windowConfig, Application* application)
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
    m_views.emplace_back(
        std::make_unique<FilAppView>(*m_renderer,
                               "Main Window",
                               m_viewport,
                               filament::math::float4{0.1, 0.125, 0.25, 1.0},
                               calcCameraMode(windowConfig.cameraMode)));
    m_mainView = m_views.back().get();
}
void Window::mouseDown(int button, ssize_t x, ssize_t y)
{
    fixupMouseCoordinatesForHdpi(x, y);
    y = m_height - y;
    for (const auto& view: m_views)
    {
        if (intersects(view->getViewport(), x, y))
        {
            m_mouseEventTarget = view.get();
            view->mouseDown(button, x, y);
            break;
        }
    }
}
void Window::mouseUp(ssize_t x, ssize_t y)
{
    fixupMouseCoordinatesForHdpi(x, y);
    if (m_mouseEventTarget)
    {
        y = m_height - y;
        m_mouseEventTarget->mouseUp(x, y);
        m_mouseEventTarget = nullptr;
    }
}
void Window::mouseMoved(ssize_t x, ssize_t y)
{
    fixupMouseCoordinatesForHdpi(x, y);
    y = m_height - y;
    if (m_mouseEventTarget)
        m_mouseEventTarget->mouseMoved(x, y);
    m_lastX = x;
    m_lastY = y;
}
void Window::mouseWheel(ssize_t x)
{
    if (m_mouseEventTarget)
        m_mouseEventTarget->mouseWheel(x);
    else
    {
        for (auto const& view: m_views)
        {
            if (intersects(view->getViewport(), m_lastX, m_lastY))
            {
                view->mouseWheel(x);
                break;
            }
        }
    }
}
void Window::keyDown(SDL_Scancode scancode)
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
        targetView->keyDown(scancode);
        eventTarget = targetView;
    }
}
void Window::keyUp(SDL_Scancode scancode)
{
    auto& eventTargetView = m_keyEventTarget[scancode];
    if (!eventTargetView)
        return;
    eventTargetView->keyUp(scancode);
    eventTargetView = nullptr;
}
Window::~Window()
{
    m_views.clear();
    m_application->getEngine()->destroy(m_renderer);
    m_application->getEngine()->destroy(m_swapChain);
    SDL_DestroyWindow(m_sdlWindow);
}
FilAppView* Window::getMainFilAppView()
{
    return m_mainView;
}
std::vector<std::unique_ptr<FilAppView>>& Window::getViews()
{
    return m_views;
}
filament::Renderer* Window::getRenderer()
{
    return m_renderer;
}
filament::SwapChain* Window::getSwapChain()
{
    return m_swapChain;
}
void Window::resize()
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
        m_mainView->resize(m_viewport);
    }

    for (auto& resizeCallback: m_resizeCallbacks)
        if (resizeCallback)
            resizeCallback(m_application->getEngine(),
                           m_mainView->getFilamentView());
}
void Window::addAnimationCallback(const AnimationCallBack& animation)
{
    m_animationCallbacks.push_back(animation);
}
void Window::addResizeCallback(const ResizeCallback& resizeCallback)
{
    m_resizeCallbacks.push_back(resizeCallback);
}
const std::vector<AnimationCallBack>& Window::getAnimationCallbacks() const
{
    return m_animationCallbacks;
}
const std::vector<ResizeCallback>& Window::getResizeCallbacks() const
{
    return m_resizeCallbacks;
}
void Window::clearAnimationsCallbacks()
{
    m_animationCallbacks.clear();
}
void Window::clearResizeCallbacks()
{
    m_resizeCallbacks.clear();
}
uint32_t Window::getWidth() const
{
    return m_width;
}
uint32_t Window::getHeight() const
{
    return m_height;
}
IView* Window::getMainIView()
{
    return m_mainView;
}
bool intersects(const filament::Viewport& viewport, ssize_t x, ssize_t y)
{
    if (x >= viewport.left && x < viewport.left + viewport.width)
        if (y >= viewport.bottom && y < viewport.bottom + viewport.height)
            return true;
    return false;
}
} // namespace FilApp