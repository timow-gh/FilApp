#ifndef FILAPP_VIEW_HPP
#define FILAPP_VIEW_HPP

#include "Renderable.hpp"
#include "ViewEvents.hpp"
#include <camutils/Manipulator.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/View.h>
#include <filament/Viewport.h>
#include <filapp_export.h>
#include <memory>
#include <string>
#include <utils/Entity.h>
#include <vector>

namespace FilApp
{
class FILAPP_EXPORT View
{
  public:
    using CameraManipulator = filament::camutils::Manipulator<float_t>;

  private:
    filament::Engine* m_engine = nullptr;
    filament::View* m_filamentView = nullptr;
    filament::Scene* m_scene = nullptr;
    filament::Skybox* m_skybox = nullptr;
    std::unique_ptr<CameraManipulator> m_cameraManipulator = nullptr;
    filament::Camera* m_camera = nullptr;
    utils::Entity m_cameraEntity;

    filament::Viewport m_viewport;

    std::vector<Renderable> m_renderables;

    std::string m_name;

  public:
    View(filament::Renderer& renderer,
         const std::string& name,
         const filament::Viewport& viewport,
         filament::math::float4 skyBoxDefaultColor,
         filament::camutils::Mode cameraMode);
    ~View();

    void setViewport(const filament::Viewport& viewport);
    void setCamera(filament::Camera* camera);
    // Resets the unique_ptr m_cameraManipulator and creates a new one using the
    // parameter cameraManipulator
    void setCameraManipulator(CameraManipulator* cameraManipulator);

    [[nodiscard]] filament::View* getFilamentView();
    [[nodiscard]] filament::Camera* getCamera();
    [[nodiscard]] CameraManipulator* getCameraManipulator();
    [[nodiscard]] const filament::Viewport& getViewport();

    void addRenderable(const Renderable& renderable);
    void clearRenderables();

    virtual void mouseDown(int button, ssize_t x, ssize_t y);
    virtual void mouseUp(ssize_t x, ssize_t y);
    virtual void mouseMoved(ssize_t x, ssize_t y);
    virtual void mouseWheel(ssize_t x);
    virtual void keyDown(SDL_Scancode scancode);
    virtual void keyUp(SDL_Scancode scancode);

    void resize(const filament::Viewport& viewport);

  private:
    bool manipulatorKeyFromKeycode(SDL_Scancode scancode,
                                   CameraManipulator::Key& key) const;
    void configureCameraProjection();
};
} // namespace FilApp

#endif // FILAPP_VIEW_HPP
