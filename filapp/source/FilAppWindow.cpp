#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppGuiContext.hpp>
#include <FilApp/FilAppWindow.hpp>
#include <Graphics/InputEvents/KeyEvent.hpp>
#include <Graphics/InputEvents/MouseButtonEvent.hpp>
#include <Graphics/InputEvents/MouseMoveEvent.hpp>
#include <Graphics/InputEvents/MouseWheelEvent.hpp>
#include <NativeWindowHelper.hpp>
#include <utils/EntityManager.h>

using namespace Graphics;

namespace FilApp
{
void FilAppWindow::event(const MouseButtonEvent& evt)
{
  if (intersects(m_guiContext.getViewport(), evt.x, evt.y))
  {
    m_guiContext.onEvent(makeMouseEventRelativeToViewport(evt, m_guiContext.getViewport()));
  }
  for (const auto& view: m_views)
  {
    if (intersects(view->getViewport(), evt.x, evt.y))
    {
      view->onEvent(makeMouseEventRelativeToViewport(evt, view->getViewport()));
      break;
    }
  }
}
void FilAppWindow::event(const MouseMoveEvent& evt)
{
  if (intersects(m_guiContext.getViewport(), evt.x, evt.y))
  {
    m_guiContext.onEvent(makeMouseEventRelativeToViewport(evt, m_guiContext.getViewport()));
  }
  for (const auto& view: m_views)
  {
    if (intersects(view->getViewport(), evt.x, evt.y))
    {
      view->onEvent(makeMouseEventRelativeToViewport(evt, view->getViewport()));
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
    for (auto const& view: m_views)
    {
      if (intersects(view->getViewport(), m_lastX, m_lastY))
      {
        view->onEvent(keyEvent);
        break;
      }
    }
    if (intersects(m_guiContext.getViewport(), m_lastX, m_lastY))
    {
      m_guiContext.onEvent(keyEvent);
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
  if (intersects(m_guiContext.getViewport(), m_lastX, m_lastY))
  {
    m_guiContext.onEvent(MouseWheelEvent{x, deltaT});
  }
  for (auto const& view: m_views)
  {
    if (intersects(view->getViewport(), m_lastX, m_lastY))
    {
      view->onEvent(MouseWheelEvent{x, deltaT});
      break;
    }
  }
}
FilAppWindow::~FilAppWindow()
{
  m_engine->destroy(m_skybox);
  m_engine->destroy(m_filamentGuiView);
  m_filAppScene->destroy();
  SDL_DestroyWindow(m_sdlWindow);
}
uint32_t FilAppWindow::getWidth() const
{
  return m_width;
}
uint32_t FilAppWindow::getHeight() const
{
  return m_height;
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
  x = x * static_cast<uint32_t>(dw / ww);
  y = y * static_cast<uint32_t>(dh / wh);
  y = m_height - y;
  return filament::math::int2{x, y};
}
void FilAppWindow::resizeWindow()
{
  if (m_sdlWindow)
  {
    auto viewPort = windowViewport(m_sdlWindow);
    m_width = viewPort.width;
    m_height = viewPort.height;
    calculateViewports();
  }
}
View& FilAppWindow::getMainIView()
{
  return *m_views.front();
}
void FilAppWindow::render(double_t timeInSeconds)
{
  if (m_renderer->beginFrame(getSwapChain()))
  {
    for (auto const& view: m_views)
      view->render(timeInSeconds);
    m_guiContext.render(timeInSeconds);
    m_renderer->endFrame();
  }
}
void FilAppWindow::animate(double_t deltaT)
{
  if (FilAppCameraView::CameraManipulator* mainViewManip = m_views.front()->getCameraManipulator())
  {
    filament::math::float3 eye;
    filament::math::float3 center;
    filament::math::float3 up;
    mainViewManip->update(static_cast<float_t>(deltaT));
    mainViewManip->getLookAt(&eye, &center, &up);
    m_views.front()->getCamera()->lookAt(eye, center, up);
  }

  for (auto& filappview: m_views)
    filappview->animate(deltaT);
}
void FilAppWindow::calculateViewports()
{
  uint32_t denominator = 3;
  uint32_t sideBarWidth = m_width / denominator;
  uint32_t contentWidth = m_width - sideBarWidth;

  m_contentViewport = Viewport(sideBarWidth, 0, contentWidth, m_height);
  m_views.front()->setViewport(m_contentViewport);

  m_guiViewport = Viewport(0, 0, sideBarWidth, m_height);
  m_guiContext.setViewPort(m_guiViewport);
}
void FilAppWindow::registerCommand(const Command& command)
{
  m_guiContext.registerPlacementButtonCommand(command);
}
Window::WindowId FilAppWindow::getWindowId() const
{
  return m_windowId;
}
FilAppWindow::FilAppWindow(SDL_Window* sdlWindow,
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
                           std::uint32_t height)
    : m_sdlWindow(sdlWindow)
    , m_windowId(windowId)
    , m_renderer(renderer)
    , m_swapChain(swapChain)
    , m_engine(engine)
    , m_skybox(skybox)
    , m_filAppScene(std::move(filAppScene))
    , m_contentViewport(contentViewport)
    , m_guiViewport(guiViewport)
    , m_filamentGuiView(filamentGuiView)
    , m_guiContext(std::move(guiContext))
    , m_views(std::move(views))
    , m_width(width)
    , m_height(height)
{
}
void FilAppWindow::onEvent(const WindowCloseEvent& event)
{
}
void FilAppWindow::onEvent(const WindowMinimizeEvent& event)
{
}
void FilAppWindow::onEvent(const WindowMaximizeEvent& event)
{
}
void FilAppWindow::onEvent(const WindowResizeEvent& event)
{
}
void FilAppWindow::onRemoveEventListener()
{
}
bool intersects(const Viewport& viewport, size_t x, size_t y)
{
  if (x >= viewport.left && x < viewport.left + viewport.width)
    if (y >= viewport.bottom && y < viewport.bottom + viewport.height)
      return true;
  return false;
}
Viewport windowViewport(SDL_Window* sdlWindow)
{
  int width;
  int height;
  SDL_GL_GetDrawableSize(sdlWindow, &width, &height);
  return {0, 0, static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
}

} // namespace FilApp