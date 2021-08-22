#ifndef FILAPP_APPLICATION_H
#define FILAPP_APPLICATION_H

#include "WindowConfig.h"
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
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

    struct AppConfig
    {
        filament::VertexBuffer* vb = nullptr;
        filament::IndexBuffer* ib = nullptr;
        filament::Material* mat = nullptr;
        filament::Skybox* skybox = nullptr;
        utils::Entity renderable;
    };

    ~Application();

    static Application& get();

    [[nodiscard]] filament::Engine* getEngine() const;
    [[nodiscard]] filament::Scene* getScene() const;

    void run(const WindowConfig& windowConfig);

  private:
    friend class Window;
    filament::Engine* m_engine = nullptr;
    filament::Scene* m_scene = nullptr;

    float_t m_timeStep = 0;
    bool m_closeApp = false;

    Application();
    void initSDL();
};
} // namespace FilApp

#endif // FILAPP_APPLICATION_H
