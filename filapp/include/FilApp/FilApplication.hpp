#ifndef FILAPP_FILAPPLICATION_HPP
#define FILAPP_FILAPPLICATION_HPP

#include "FilAppInterfaces/AppConfig.hpp"
#include "FilAppInterfaces/IApplication.hpp"
#include "FilAppInterfaces/IWindow.hpp"
#include "FilAppInterfaces/WindowConfig.hpp"
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

class FILAPP_EXPORT FilApplication
    : public IApplication
{
  public:
    static void init(const AppConfig& appConfig,
                     const WindowConfig& windowConfig);
    static FilApplication& get();

    FilApplication() = default;
    ~FilApplication() override;
    FilApplication(const FilApplication& application) = delete;
    FilApplication(FilApplication&& application) = delete;
    FilApplication& operator=(const FilApplication& application) = delete;
    FilApplication& operator=(FilApplication&& application) = delete;

    [[nodiscard]] filament::Engine* getEngine();
    [[nodiscard]] IWindow* getWindow() override;

    static double_t getDeltaT();

    void run();

  private:
    static std::unique_ptr<FilApplication> m_app;
    static double_t m_prevTimeStep;

    filament::Engine* m_engine = nullptr;

    std::unique_ptr<FilAppWindow> m_window;

    bool m_closeApp = false;
    AppConfig m_appConfig;
};
} // namespace FilApp

#endif // FILAPP_FILAPPLICATION_HPP
