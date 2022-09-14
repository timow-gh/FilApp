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
// and manages the rendering tread as well as the hardware renderer.
class FILAPP_EXPORT FilApplication final : public Graphics::GraphicsApp {
public:
  CORE_NODISCARD static std::shared_ptr<Graphics::GraphicsApp> getFilApp(const Graphics::AppConfig& appConfig,
                                                                         const Graphics::WindowConfig& windowConfig);

  ~FilApplication() override;
  FilApplication(const FilApplication& application) = delete;
  FilApplication(FilApplication&& application) = delete;
  FilApplication& operator=(const FilApplication& application) = delete;
  FilApplication& operator=(FilApplication&& application) = delete;

  CORE_NODISCARD filament::Engine* getEngine();
  CORE_NODISCARD static double_t getDeltaT();

  CORE_NODISCARD Graphics::Window& getWindow() override;
  void run() override;

private:
  static std::unique_ptr<FilApplication> m_app;
  static double_t m_prevTimeStep;

public:
  FilApplication(const Graphics::AppConfig& appConfig, const Graphics::WindowConfig& windowConfig);

private:
  Graphics::AppConfig m_appConfig;
  filament::Engine* m_engine{nullptr};
  FilAppRenderableCreator m_renderableCreator;
  std::unique_ptr<FilAppWindow> m_window;
  bool m_closeApp{false};
};
} // namespace FilApp

#endif // FILAPP_FILAPPLICATION_HPP
