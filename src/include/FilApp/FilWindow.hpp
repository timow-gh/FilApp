#ifndef FILAPP_FILWINDOW_HPP
#define FILAPP_FILWINDOW_HPP

#include "FilApp/Interfaces/IWindow.hpp"
#include "FilApp/Interfaces/WindowConfig.hpp"
#include "FilAppView.hpp"
#include "FilApplication.hpp"
#include <SDL_video.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <memory>
#include <unordered_map>
#include <vector>

namespace FilApp
{

class FilWindow
    : public IWindow
{
    SDL_Window* m_sdlWindow = nullptr;
    IWindow::WindowId m_windowId{0};
    FilApplication* m_application = nullptr;
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
    FilWindow(const WindowConfig& windowConfig, FilApplication* application);
    FilWindow(FilWindow&& window) = default;
    FilWindow& operator=(FilWindow&& window) = default;
    ~FilWindow() override;

    void mouseDown(int button, size_t x, size_t y, double_t deltaT);
    void mouseUp(size_t x, size_t y, double_t deltaT);
    void mouseMoved(size_t x, size_t y, double_t deltaT);
    void mouseWheel(size_t x, double_t deltaT);
    void keyDown(SDL_Scancode scancode, double_t deltaT);
    void keyUp(SDL_Scancode scancode, double_t deltaT);

    void resize();
    void animate(double_t deltaT);
    void render();

    [[nodiscard]] IView* getMainIView() override;
    [[nodiscard]] std::vector<IView*> getIViews() override;

    WindowId getIWindowId() override;

    [[nodiscard]] uint32_t getWidth() const;
    [[nodiscard]] uint32_t getHeight() const;

    [[nodiscard]] FilAppView* getMainFilAppView();
    [[nodiscard]] filament::Renderer* getRenderer();
    [[nodiscard]] filament::SwapChain* getSwapChain();

  private:
    void fixupMouseCoordinatesForHdpi(size_t& x, size_t& y) const;
    void calcWindowViewport();
};

bool intersects(const Viewport& viewport, size_t x, size_t y);
} // namespace FilApp

#endif // FILAPP_FILWINDOW_HPP
