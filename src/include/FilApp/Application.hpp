#ifndef FILAPP_APPLICATION_HPP
#define FILAPP_APPLICATION_HPP

#include "FilApp/Interfaces/AppConfig.hpp"
#include "FilApp/Interfaces/WindowConfig.hpp"
#include <cmath>
#include <filapp_export.h>
#include <memory>

namespace filament
{
class Engine;
}

namespace FilApp
{
class FilWindow;

class FILAPP_EXPORT Application
{
  public:
    static void init(const AppConfig& appConfig,
                     const WindowConfig& windowConfig);
    static Application& get();

    Application() = default;
    Application(const Application& application) = delete;
    Application& operator=(const Application& application) = delete;
    Application(Application&& application) = delete;
    Application& operator=(Application&& application) = delete;
    ~Application();

    [[nodiscard]] filament::Engine* getEngine();
    [[nodiscard]] FilWindow* getWindow();

    static double_t getDeltaT();

    void run();

  private:
    static std::unique_ptr<Application> m_app;
    static double_t m_prevTimeStep;

    filament::Engine* m_engine = nullptr;

    std::unique_ptr<FilWindow> m_window;

    bool m_closeApp = false;
};
} // namespace FilApp

#endif // FILAPP_APPLICATION_HPP
