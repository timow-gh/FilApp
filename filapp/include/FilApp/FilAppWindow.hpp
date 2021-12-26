#ifndef FILAPP_FILAPPWINDOW_HPP
#define FILAPP_FILAPPWINDOW_HPP

#include "FilAppInterfaces/InputEvents/KeyDownEvent.hpp"
#include "FilAppInterfaces/InputEvents/MouseButtonEvent.hpp"
#include "FilAppInterfaces/Window.hpp"
#include "FilAppInterfaces/WindowConfig.hpp"
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

class FilAppWindow : public Window {
    SDL_Window* m_sdlWindow = nullptr;
    Window::WindowId m_windowId{0};
    FilApplication* m_application = nullptr;
    filament::Renderer* m_renderer = nullptr;
    filament::Engine::Backend m_backend = filament::Engine::Backend::DEFAULT;
    filament::SwapChain* m_swapChain = nullptr;

    std::vector<std::unique_ptr<FilAppView>> m_views;

    FilAppView* m_mainView{nullptr};

    uint32_t m_width = 0;
    uint32_t m_height = 0;
    size_t m_lastX = 0;
    size_t m_lastY = 0;

    std::unordered_map<SDL_Scancode, FilAppView*> m_keyEventTarget;

  public:
    FilAppWindow(const WindowConfig& windowConfig, FilApplication* application);
    FilAppWindow(FilAppWindow&& window) = default;
    FilAppWindow& operator=(FilAppWindow&& window) = default;
    ~FilAppWindow() override;

    void event(const MouseButtonEvent& mouseButtonEvent);
    void event(const MouseMoveEvent& mouseMoveEvent);
    void event(const KeyUpEvent& keyUpEvent);
    void event(const KeyDownEvent& keyDownEvent);
    void mouseWheel(float_t x, double_t deltaT);

    void resize();
    void animate(double_t deltaT);
    void render();

    CORE_NODISCARD View* getMainIView() override;
    CORE_NODISCARD std::vector<View*> getIViews() override;

    WindowId getIWindowId() override;

    CORE_NODISCARD SDL_Window* getSdlWindow() const;
    CORE_NODISCARD uint32_t getWidth() const;
    CORE_NODISCARD uint32_t getHeight() const;

    CORE_NODISCARD FilAppView* getMainFilAppView();
    CORE_NODISCARD filament::Renderer* getRenderer();
    CORE_NODISCARD filament::SwapChain* getSwapChain();

    filament::math::int2 fixupMouseCoordinatesForHdpi(uint32_t x,
                                                      uint32_t y) const;

  private:
    CORE_NODISCARD Viewport calcWindowViewport();
};

bool intersects(const Viewport& viewport, size_t x, size_t y);
} // namespace FilApp

#endif // FILAPP_FILAPPWINDOW_HPP
