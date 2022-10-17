#ifndef FILAPP_FILAPPWINDOW_HPP
#define FILAPP_FILAPPWINDOW_HPP

#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <filament/Engine.h>
#include <filament/Renderer.h>
ENABLE_ALL_WARNINGS
#include <FilApp/FilAppCameraView.hpp>
#include <FilApp/FilAppGuiContext.hpp>
#include <FilApp/FilAppScene.hpp>
#include <FilApp/FilApplication.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/MouseButtonEvent.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/Window.hpp>
#include <Graphics/WindowConfig.hpp>
#include <SDL_video.h>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace FilApp
{

class FilAppWindow final : public Graphics::Window {
  SDL_Window* m_sdlWindow = nullptr;
  Window::WindowId m_windowId{0};
  filament::Renderer* m_renderer = nullptr;
  filament::SwapChain* m_swapChain = nullptr;
  filament::Engine* m_engine = nullptr;
  filament::Skybox* m_skybox = nullptr;

  std::unique_ptr<FilAppScene> m_filAppScene;

  Graphics::Viewport m_contentViewport;
  Graphics::Viewport m_guiViewport;
  filament::View* m_filamentGuiView;
  FilAppGuiContext m_guiContext;
  Core::TVector<std::unique_ptr<FilAppCameraView>> m_views;

  std::uint32_t m_width = 0;
  std::uint32_t m_height = 0;
  std::size_t m_lastX = 0;
  std::size_t m_lastY = 0;

  std::unordered_map<SDL_Scancode, FilAppCameraView*> m_keyEventTarget;

public:
  FilAppWindow(SDL_Window* sdlWindow,
               WindowId windowId,
               filament::Renderer* renderer,
               filament::SwapChain* swapChain,
               filament::Engine* engine,
               filament::Skybox* skybox,
               std::unique_ptr<FilAppScene>&& filAppScene,
               Graphics::Viewport contentViewport,
               Graphics::Viewport guiViewport,
               filament::View* filamentGuiView,
               FilAppGuiContext guiContext,
               Core::TVector<std::unique_ptr<FilAppCameraView>>&& views,
               std::uint32_t width,
               std::uint32_t height);

  ~FilAppWindow() override;

  void onEvent(const Graphics::WindowCloseEvent& event) override;
  void onEvent(const Graphics::WindowMinimizeEvent& event) override;
  void onEvent(const Graphics::WindowMaximizeEvent& event) override;
  void onEvent(const Graphics::WindowResizeEvent& event) override;
  void onRemoveEventListener() override;

  void onEvent(const Graphics::MouseButtonEvent&) override;
  void onEvent(const Graphics::MouseMoveEvent&) override;
  void onEvent(const Graphics::MouseWheelEvent&) override;
  void onEvent(const Graphics::KeyEvent&) override;

  void resizeWindow();
  void animate(double_t deltaT);
  void render(double_t timeInSeconds);

  WindowId getWindowId() const override;

  CORE_NODISCARD Graphics::View& getMainView() override;
  void registerCommand(const Graphics::Command& command) override;

  CORE_NODISCARD uint32_t getWidth() const;
  CORE_NODISCARD uint32_t getHeight() const;

  CORE_NODISCARD filament::SwapChain* getSwapChain();

  CORE_NODISCARD filament::math::int2 fixupMouseCoordinatesForHdpi(uint32_t x, uint32_t y) const;

private:
  void calculateViewports();
  template <typename TMouseEvent>
  TMouseEvent makeMouseEventRelativeToViewport(const TMouseEvent& mouseEvent, const Graphics::Viewport& viewport) const
  {
    TMouseEvent evtCopy = mouseEvent;
    evtCopy.x = mouseEvent.x - viewport.left;
    evtCopy.y = mouseEvent.y - viewport.bottom;
    return evtCopy;
  }
};

CORE_NODISCARD bool intersects(const Graphics::Viewport& viewport, size_t x, size_t y);
CORE_NODISCARD Graphics::Viewport windowViewport(SDL_Window* sdlWindow);

} // namespace FilApp

#endif // FILAPP_FILAPPWINDOW_HPP
