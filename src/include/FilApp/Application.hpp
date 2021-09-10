#ifndef FILAPP_APPLICATION_HPP
#define FILAPP_APPLICATION_HPP

#include "AppConfig.hpp"
#include "WindowConfig.hpp"
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/View.h>
#include <filapp_export.h>
#include <memory>
#include <utils/Entity.h>

namespace FilApp
{
class Window;

using ResizeCallback = std::function<void(filament::Engine*, filament::View*)>;
using AnimationCallBack = std::function<
    void(filament::Engine* engine, filament::View* view, double now)>;

class FILAPP_EXPORT Application
{
  public:
    // clang-format off
    using SetupCallback = std::function<void(filament::Engine*, filament::View*, filament::Scene*)>;
    using CleanupCallback = std::function<void(filament::Engine*, filament::View*, filament::Scene*)>;
    // clang-format on

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
    [[nodiscard]] Window* getWindow();

    void run();

  private:
    static std::unique_ptr<Application> m_app;
    filament::Engine* m_engine = nullptr;

    std::unique_ptr<Window> m_window;

    bool m_closeApp = false;
    double_t m_prevTimeStep = 0;
};
} // namespace FilApp

#endif // FILAPP_APPLICATION_HPP
