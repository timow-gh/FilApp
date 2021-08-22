#ifndef FILAPP_APPLICATION_H
#define FILAPP_APPLICATION_H

#include "AppConfig.h"
#include "WindowConfig.h"
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
#include <memory>
#include <utils/Entity.h>

namespace FilApp
{
using ResizeCallback = std::function<void(filament::Engine*, filament::View*)>;
using AnimationCallBack = std::function<
    void(filament::Engine* engine, filament::View* view, double now)>;

class Application
{
  public:
    // clang-format off
    using SetupCallback = std::function<void(filament::Engine*, filament::View*, filament::Scene*)>;
    using CleanupCallback = std::function<void(filament::Engine*, filament::View*, filament::Scene*)>;
    // clang-format on

    struct AppData
    {
        filament::VertexBuffer* vb = nullptr;
        filament::IndexBuffer* ib = nullptr;
        filament::Material* mat = nullptr;
        filament::Skybox* skybox = nullptr;
        utils::Entity renderable;
    };

    static void init(const AppConfig& appConfig);
    static Application& get();

    Application() = default;
    Application(const Application& application) = delete;
    Application& operator=(const Application& application) = delete;
    Application(Application&& application) = delete;
    Application& operator=(Application&& application) = delete;
    ~Application();

    [[nodiscard]] filament::Engine* getEngine();
    [[nodiscard]] filament::Scene* getScene();

    void run(const WindowConfig& windowConfig);

  private:
    static std::unique_ptr<Application> m_app;
    filament::Engine* m_engine = nullptr;
    filament::Scene* m_scene = nullptr;

    float_t m_timeStep = 0;
    bool m_closeApp = false;
};
} // namespace FilApp

#endif // FILAPP_APPLICATION_H
