#ifndef FILAPP_WINDOW_HPP
#define FILAPP_WINDOW_HPP

#include "Application.hpp"
#include "FilAppView.hpp"
#include "WindowConfig.hpp"
#include <SDL_video.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filapp_export.h>
#include <memory>
#include <unordered_map>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT Window
{
    SDL_Window* m_sdlWindow = nullptr;
    Application* m_application = nullptr;
    filament::Renderer* m_renderer = nullptr;
    filament::Engine::Backend m_backend = filament::Engine::Backend::DEFAULT;
    filament::SwapChain* m_swapChain = nullptr;

    filament::Viewport m_viewport;
    std::vector<std::unique_ptr<FilAppView>> m_views;
    FilAppView* m_mainView;
    FilAppView* m_mouseEventTarget = nullptr;

    uint32_t m_width = 0;
    uint32_t m_height = 0;
    ssize_t m_lastX = 0;
    ssize_t m_lastY = 0;

    std::vector<AnimationCallBack> m_animationCallbacks;
    std::vector<ResizeCallback> m_resizeCallbacks;

    std::unordered_map<SDL_Scancode, FilAppView*> m_keyEventTarget;

  public:
    Window(const WindowConfig& windowConfig, Application* application);
    Window(Window&& window) = default;
    Window& operator=(Window&& window) = default;
    ~Window();

    void mouseDown(int button, ssize_t x, ssize_t y);
    void mouseUp(ssize_t x, ssize_t y);
    void mouseMoved(ssize_t x, ssize_t y);
    void mouseWheel(ssize_t x);
    void keyDown(SDL_Scancode scancode);
    void keyUp(SDL_Scancode scancode);
    void resize();

    void addAnimationCallback(const AnimationCallBack& animation);
    void addResizeCallback(const ResizeCallback& resizeCallback);

    [[nodiscard]] const std::vector<AnimationCallBack>&
    getAnimationCallbacks() const;
    [[nodiscard]] const std::vector<ResizeCallback>& getResizeCallbacks() const;

    void clearAnimationsCallbacks();
    void clearResizeCallbacks();

    [[nodiscard]] IView* getMainIView();
    [[nodiscard]] FilAppView* getMainFilAppView();
    [[nodiscard]] std::vector<std::unique_ptr<FilAppView>>& getViews();
    [[nodiscard]] filament::Renderer* getRenderer();
    [[nodiscard]] filament::SwapChain* getSwapChain();

    [[nodiscard]] uint32_t getWidth() const;
    [[nodiscard]] uint32_t getHeight() const;

  private:
    void fixupMouseCoordinatesForHdpi(ssize_t& x, ssize_t& y) const;
    void calcWindowViewport();
};

bool intersects(const filament::Viewport& viewport, ssize_t x, ssize_t y);
} // namespace FilApp

#endif // FILAPP_WINDOW_HPP
