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

  FilAppScene m_filAppScene;

  Graphics::Viewport m_contentViewport;
  Graphics::Viewport m_guiViewport;
  FilAppGuiContext m_guiContext;
  Core::TVector<std::unique_ptr<FilAppCameraView>> m_views;

  std::uint32_t m_width = 0;
  std::uint32_t m_height = 0;
  std::size_t m_lastX = 0;
  std::size_t m_lastY = 0;

  std::unordered_map<SDL_Scancode, FilAppCameraView*> m_keyEventTarget;

public:
  FilAppWindow(const Graphics::WindowConfig& windowConfig, FilAppRenderableCreator& filAppRenderableCreator, filament::Engine* engine);

  ~FilAppWindow() override;

  void event(const Graphics::MouseButtonEvent& mouseButtonEvent);
  void event(const Graphics::MouseMoveEvent& mouseMoveEvent);
  void event(const Graphics::KeyEvent& keyEvent);
  void mouseWheel(float_t x, double_t deltaT);

  void resizeWindow();
  void animate(double_t deltaT);
  void render(double_t timeInSeconds);

  CORE_NODISCARD Graphics::View& getMainIView() override;

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
