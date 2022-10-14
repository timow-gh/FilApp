#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <SDL.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <utils/Panic.h>
ENABLE_ALL_WARNINGS
#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <FilApp/FilAppWindow.hpp>
#include <FilApp/FilApplication.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/KeyEvent.hpp>
#include <Graphics/InputEvents/MouseButtonEvent.hpp>
#include <Graphics/InputEvents/MouseMoveEvent.hpp>
#include <Graphics/WindowEventDispatcher.hpp>
#include <NativeWindowHelper.hpp>
#include <memory>

using namespace Graphics;

namespace FilApp
{
double_t FilApplication::m_prevTimeStep = 0;

std::shared_ptr<Graphics::GraphicsApp> FilApplication::getFilApp(const AppConfig& appConfig)
{
  ASSERT_POSTCONDITION(SDL_Init(SDL_INIT_EVENTS) == 0, "SDL_Init Failure");

  static std::shared_ptr<FilApplication> filApp = std::make_shared<FilApplication>(appConfig);
  return filApp;
}

FilApplication::~FilApplication()
{
  for (auto& window: m_windows)
  {
    window->onEvent(WindowCloseEvent{});
  }
  SDL_Quit();
}

filament::Engine* FilApplication::getEngine()
{
  return m_engine;
}

double_t FilApplication::getDeltaT()
{
  return static_cast<double_t>(SDL_GetPerformanceCounter()) / static_cast<double_t>(SDL_GetPerformanceFrequency()) - m_prevTimeStep;
}

void FilApplication::run()
{
  m_prevTimeStep = static_cast<double_t>(SDL_GetPerformanceCounter()) / static_cast<double_t>(SDL_GetPerformanceFrequency());

  EventPollingMode eventPollingMode = m_appConfig.eventPollingMode;

  while (!m_closeApp)
  {
    for (auto& window: m_windows)
    {
      double_t deltaT = FilApplication::getDeltaT();

      SDL_Event sdlEvent;

      switch (eventPollingMode)
      {
      case EventPollingMode::POLL_EVENTS: SDL_PollEvent(&sdlEvent); break;
      case EventPollingMode::WAIT_EVENTS: SDL_WaitEvent(&sdlEvent); break;
      }

      switch (sdlEvent.type)
      {
      case SDL_QUIT: m_closeApp = true; break;
      case SDL_KEYDOWN:
      {
        if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
          m_closeApp = true;
        window->event(KeyEvent(KeyEvent::Type::PUSH,
                               toKeyScancode(sdlEvent.key.keysym.scancode),
                               sdlEvent.key.timestamp,
                               sdlEvent.key.windowID,
                               deltaT));
        break;
      }
      case SDL_KEYUP:
      {
        window->event(KeyEvent(KeyEvent::Type::RELEASE,
                               toKeyScancode(sdlEvent.key.keysym.scancode),
                               sdlEvent.key.timestamp,
                               sdlEvent.key.windowID,
                               deltaT));
        break;
      }
      case SDL_MOUSEWHEEL: window->mouseWheel(static_cast<float_t>(sdlEvent.wheel.y), deltaT); break;
      case SDL_MOUSEBUTTONDOWN:
      {
        filament::math::int2 pos =
            window->fixupMouseCoordinatesForHdpi(static_cast<uint32_t>(sdlEvent.button.x), static_cast<uint32_t>(sdlEvent.button.y));
        window->event(MouseButtonEvent{MouseButtonEvent::Type::PUSH,
                                       sdlEvent.button.button,
                                       sdlEvent.button.timestamp,
                                       sdlEvent.button.windowID,
                                       sdlEvent.button.clicks,
                                       static_cast<uint32_t>(pos.x),
                                       static_cast<uint32_t>(pos.y),
                                       deltaT});
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        filament::math::int2 pos =
            window->fixupMouseCoordinatesForHdpi(static_cast<uint32_t>(sdlEvent.button.x), static_cast<uint32_t>(sdlEvent.button.y));
        window->event(MouseButtonEvent{MouseButtonEvent::Type::RELEASE,
                                       sdlEvent.button.button,
                                       sdlEvent.button.timestamp,
                                       sdlEvent.button.windowID,
                                       sdlEvent.button.clicks,
                                       static_cast<uint32_t>(pos.x),
                                       static_cast<uint32_t>(pos.y),
                                       deltaT});
        break;
      }
      case SDL_MOUSEMOTION:
      {
        filament::math::int2 pos =
            window->fixupMouseCoordinatesForHdpi(static_cast<uint32_t>(sdlEvent.button.x), static_cast<uint32_t>(sdlEvent.button.y));
        window->event(MouseMoveEvent{sdlEvent.button.timestamp,
                                     sdlEvent.button.windowID,
                                     static_cast<uint32_t>(pos.x),
                                     static_cast<uint32_t>(pos.y),
                                     deltaT});
        break;
      }
      case SDL_WINDOWEVENT:
      {
        if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
          window->resizeWindow();
        break;
      }
      default:
      {
        break;
      }
      }

      window->render(deltaT);
    }
  }
}

FilApplication::FilApplication(const AppConfig& appConfig)
    : m_appConfig(appConfig)
    , m_engine(filament::Engine::create(toFilamentBackend(appConfig.backendMode)))
    , m_renderableCreator(std::make_unique<FilAppRenderableCreator>(FilAppRenderableCreator::create(m_engine)))
    , m_windowEventDispatcher(std::make_unique<WindowEventDispatcher>())
    , m_inputEventDispatcher(std::make_unique<InputEventDispatcher>())
{
}
Window& FilApplication::createWindow(const WindowConfig& windowConfig)
{
  std::uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
  if (windowConfig.isResizable)
    windowFlags |= SDL_WINDOW_RESIZABLE;
  if (windowConfig.isHeadless)
    windowFlags |= SDL_WINDOWEVENT_HIDDEN;

  const std::int32_t x = SDL_WINDOWPOS_CENTERED;
  const std::int32_t y = SDL_WINDOWPOS_CENTERED;
  auto sdlWindow = SDL_CreateWindow(windowConfig.windowName.c_str(),
                                    x,
                                    y,
                                    static_cast<std::int32_t>(windowConfig.width),
                                    static_cast<std::int32_t>(windowConfig.height),
                                    windowFlags);

  std::size_t width = 0;
  std::size_t height = 0;
  filament::SwapChain* swapChain = nullptr;
  if (windowConfig.isHeadless)
  {
    width = windowConfig.width;
    height = windowConfig.height;
    swapChain = m_engine->createSwapChain(width, height);
  }
  else
  {
    void* nativeWindow = ::getNativeWindow(sdlWindow);
    void* nativeSwapChain = nativeWindow;
    swapChain = m_engine->createSwapChain(nativeSwapChain);
  }

  auto renderer = m_engine->createRenderer();

  ViewConfig viewConfig;
  viewConfig.name = "MainView";
  viewConfig.viewport = windowViewport(sdlWindow);
  width = viewConfig.viewport.width;
  height = viewConfig.viewport.height;

  uint32_t denominator = 3;
  uint32_t sideBarWidth = width / denominator;
  uint32_t contentWidth = width - sideBarWidth;

  auto filAppScene = std::make_unique<FilAppScene>(FilAppScene::create(m_engine, *m_renderableCreator));

  auto view = std::make_unique<FilAppCameraView>(viewConfig, *filAppScene, renderer);
  auto contentViewport = Viewport(sideBarWidth, 0, contentWidth, height);
  view->setViewport(contentViewport);

  constexpr float_t pixelRatio = 1.0f;
  auto filamentGuiView = m_engine->createView();
  auto guiContext = createFilAppGuiContext(filamentGuiView, m_engine, renderer, pixelRatio);
  auto guiViewport = Viewport(0, 0, sideBarWidth, height);
  guiContext.setViewPort(guiViewport);

  auto colorVec = Vec4{viewConfig.skyBoxColor.getRed(),
                       viewConfig.skyBoxColor.getGreen(),
                       viewConfig.skyBoxColor.getBlue(),
                       viewConfig.skyBoxColor.getAlpha()};
  auto skybox = filament::Skybox::Builder().color(vec4ToFloat4(colorVec)).build(*m_engine);
  filAppScene->setSkybox(skybox);

  Core::TVector<std::unique_ptr<FilAppCameraView>> views;
  views.push_back(std::move(view));
  CORE_POSTCONDITION_DEBUG_ASSERT(views.empty() == false, "No views created");
  auto windowId = SDL_GetWindowID(sdlWindow);
  auto window = std::make_unique<FilAppWindow>(sdlWindow,
                                               windowId,
                                               renderer,
                                               swapChain,
                                               m_engine,
                                               skybox,
                                               std::move(filAppScene),
                                               contentViewport,
                                               guiViewport,
                                               filamentGuiView,
                                               std::move(guiContext),
                                               std::move(views),
                                               width,
                                               height);
  m_windows.push_back(std::move(window));
  m_windowEventDispatcher->registerEventListener(m_windows.back().get());
  m_inputEventDispatcher->registerInputEventListener(m_windows.back().get());
  return *m_windows.back();
}
Core::TVector<GraphicsApp::WindowId> FilApplication::getWindowIds()
{
  Core::TVector<WindowId> windowIds;
  for (auto& window: m_windows)
    windowIds.push_back(window->getWindowId());
  return windowIds;
}
Window& FilApplication::getWindow(GraphicsApp::WindowId windowId)
{
  CORE_PRECONDITION_ASSERT(!m_windows.empty(), "No windows created");
  auto iter =
      std::find_if(m_windows.begin(), m_windows.end(), [windowId](const auto& window) { return window->getWindowId() == windowId; });
  if (iter != m_windows.end())
  {
    return **iter;
  }
  CORE_POSTCONDITION_ASSERT(false, "Window not found");
}
WindowEventDispatcher& FilApplication::getWindowEventDispatcher()
{
  CORE_PRECONDITION_ASSERT(m_windowEventDispatcher, "WindowEventDispatcher is not initialized");
  return *m_windowEventDispatcher;
}
InputEventDispatcher& FilApplication::getInputEventDispatcher()
{
  CORE_PRECONDITION_ASSERT(m_inputEventDispatcher, "Inputeventdispatcher is not initialized");
  return *m_inputEventDispatcher;
}

} // namespace FilApp
