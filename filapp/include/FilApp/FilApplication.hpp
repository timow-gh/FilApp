#ifndef FILAPP_FILAPPLICATION_HPP
#define FILAPP_FILAPPLICATION_HPP

#include <Core/Utils/Compiler.hpp>
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

class FILAPP_EXPORT FilApplication : public Graphics::GraphicsApp {
  public:
    CORE_NODISCARD static std::shared_ptr<Graphics::GraphicsApp>
    getFilApp(const Graphics::AppConfig& appConfig, const Graphics::WindowConfig& windowConfig);

    FilApplication() = default;
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
    FilApplication(const Graphics::AppConfig& appConfig,
                   const Graphics::WindowConfig& windowConfig);

  private:
    filament::Engine* m_engine = nullptr;

    std::unique_ptr<FilAppWindow> m_window;

    bool m_closeApp = false;
    Graphics::AppConfig m_appConfig;
};
} // namespace FilApp

#endif // FILAPP_FILAPPLICATION_HPP
