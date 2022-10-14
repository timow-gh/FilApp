#ifndef FILAPP_FILAPPLICATION_HPP
#define FILAPP_FILAPPLICATION_HPP

#include <Core/Utils/Compiler.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <Graphics/AppConfig.hpp>
#include <Graphics/GraphicsApp.hpp>
#include <Graphics/Window.hpp>
#include <Graphics/WindowConfig.hpp>
#include <cmath>
#include <filapp_export.h>
#include <memory>

namespace filament
{
class Engine;
}

namespace FilApp
{

class FilAppWindow;

// This class is the main entry point for the FilApp application.
// It is responsible for creating the window and the filament engine.
// The filament engine keeps track of all resources created by the application
// and manages the rendering thread as well as the hardware renderer.
class FILAPP_EXPORT FilApplication final : public Graphics::GraphicsApp {
public:
  CORE_NODISCARD static std::shared_ptr<Graphics::GraphicsApp> getFilApp(const Graphics::AppConfig& appConfig);

  explicit FilApplication(const Graphics::AppConfig& appConfig);
  FilApplication(const FilApplication& application) = delete;
  FilApplication& operator=(const FilApplication& application) = delete;
  ~FilApplication() override;

  Graphics::Window& createWindow(const Graphics::WindowConfig& windowConfig) override;
  Core::TVector<WindowId> getWindowIds() override;
  Graphics::Window& getWindow(WindowId windowId) override;
  Graphics::WindowEventDispatcher& getWindowEventDispatcher() override;
  Graphics::InputEventDispatcher& getInputEventDispatcher() override;

  CORE_NODISCARD filament::Engine* getEngine();
  CORE_NODISCARD static double_t getDeltaT();

  void run() override;

private:
  static std::unique_ptr<FilApplication> m_app;
  static double_t m_prevTimeStep;
  Graphics::AppConfig m_appConfig;
  filament::Engine* m_engine{nullptr};
  bool m_closeApp{false};
  std::unique_ptr<FilAppRenderableCreator> m_renderableCreator;
  Core::TVector<std::unique_ptr<FilAppWindow>> m_windows;
  std::unique_ptr<Graphics::WindowEventDispatcher> m_windowEventDispatcher;
  std::unique_ptr<Graphics::InputEventDispatcher> m_inputEventDispatcher;
};
} // namespace FilApp

#endif // FILAPP_FILAPPLICATION_HPP
