#ifndef FILAPP_FILAPPLICATION_HPP
#define FILAPP_FILAPPLICATION_HPP

#include <Core/Utils/Compiler.hpp>
#include <GraphicsInterface/AppConfig.hpp>
#include <GraphicsInterface/GraphicsApp.hpp>
#include <GraphicsInterface/Window.hpp>
#include <GraphicsInterface/WindowConfig.hpp>
#include <cmath>
#include <filapp_export.h>
#include <memory>

namespace filament
{
class Engine;
}

// TODO Fix namespace
namespace Graphics
{

class FilAppWindow;

class FILAPP_EXPORT FilApplication : public GraphicsApp {
  public:
    CORE_NODISCARD static std::shared_ptr<Graphics::GraphicsApp>
    getFilApp(const AppConfig& appConfig, const WindowConfig& windowConfig);

    FilApplication() = default;
    ~FilApplication() override;
    FilApplication(const FilApplication& application) = delete;
    FilApplication(FilApplication&& application) = delete;
    FilApplication& operator=(const FilApplication& application) = delete;
    FilApplication& operator=(FilApplication&& application) = delete;

    CORE_NODISCARD filament::Engine* getEngine();
    CORE_NODISCARD static double_t getDeltaT();

    CORE_NODISCARD Window* getWindow() override;
    void run() override;

  private:
    static std::unique_ptr<FilApplication> m_app;
    static double_t m_prevTimeStep;

  public:
    FilApplication(const AppConfig& appConfig, const WindowConfig& windowConfig);

  private:
    filament::Engine* m_engine = nullptr;

    std::unique_ptr<FilAppWindow> m_window;

    bool m_closeApp = false;
    AppConfig m_appConfig;
};
} // namespace Graphics

#endif // FILAPP_FILAPPLICATION_HPP
