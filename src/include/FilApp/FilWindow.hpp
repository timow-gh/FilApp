#ifndef FILAPP_FILWINDOW_HPP
#define FILAPP_FILWINDOW_HPP

#include "Application.hpp"
#include "FilApp/Interfaces/WindowConfig.hpp"
#include "FilAppView.hpp"
#include <SDL_video.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <memory>
#include <unordered_map>
#include <vector>

namespace FilApp
{

class FilWindow
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
    size_t m_lastX = 0;
    size_t m_lastY = 0;

    std::unordered_map<SDL_Scancode, FilAppView*> m_keyEventTarget;

  public:
    FilWindow(const WindowConfig& windowConfig, Application* application);
    FilWindow(FilWindow&& window) = default;
    FilWindow& operator=(FilWindow&& window) = default;
    ~FilWindow();

    void mouseDown(int button, size_t x, size_t y);
    void mouseUp(size_t x, size_t y);
    void mouseMoved(size_t x, size_t y);
    void mouseWheel(size_t x);
    void keyDown(SDL_Scancode scancode);
    void keyUp(SDL_Scancode scancode);

    void resize();

    void animate(double_t deltaT);
    void render();

    [[nodiscard]] IView* getMainIView();
    [[nodiscard]] FilAppView* getMainFilAppView();
    [[nodiscard]] std::vector<IView*> getViews() const;
    [[nodiscard]] filament::Renderer* getRenderer();
    [[nodiscard]] filament::SwapChain* getSwapChain();

    [[nodiscard]] uint32_t getWidth() const;
    [[nodiscard]] uint32_t getHeight() const;

  private:
    void fixupMouseCoordinatesForHdpi(size_t& x, size_t& y) const;
    void calcWindowViewport();
};

bool intersects(const Viewport& viewport, size_t x, size_t y);
} // namespace FilApp

#endif // FILAPP_FILWINDOW_HPP
