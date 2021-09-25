#ifndef FILAPP_FILAPPVIEW_HPP
#define FILAPP_FILAPPVIEW_HPP

#include "FilApp/Interfaces/IView.hpp"
#include "FilAppRenderable.hpp"
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
using AnimationCallBack = std::function<void(double now)>;

class FilAppView
    : public IView
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

    std::vector<std::unique_ptr<PointRenderable>> m_pointRenderables;
    std::vector<std::unique_ptr<TriangleRenderable>> m_triangleRenderables;

    std::vector<FilAppRenderable> m_renderables;

    std::vector<AnimationCallBack> m_animationCallbacks;

    std::string m_name;

  public:
    FilAppView(filament::Renderer& renderer,
               const std::string& name,
               const filament::Viewport& viewport,
               filament::math::float4 skyBoxDefaultColor,
               filament::camutils::Mode cameraMode);
    ~FilAppView() override;

    // clang-format off
    auto addRenderable(TriangleRenderable&& renderable) -> RenderableIdentifier override;
    auto addRenderable(PointRenderable && renderable) -> RenderableIdentifier override;
    auto getRenderableIdentifiers() const -> std::vector<RenderableIdentifier> override;
    void removeRenderable(RenderableIdentifier renderableIdentifier) override;
    void clearRenderables() override;
    // clang-format on
    void setUsePostprocessing(bool usePostProcessing) override;

    void addRotationAnimation(RenderableIdentifier renderableIdentifier,
                              const Vec3& rotationAxis) override;

    void animate(double deltaT) override;

    Viewport getViewport() const override;
    void resize(const Viewport& viewport) override;

    void mouseDown(const MouseDownEvent& mouseDownEvent) override;
    void mouseUp(const MouseUpEvent& mouseUpEvent) const override;
    void mouseMoved(const MouseMovedEvent& mouseMovedEvent) const override;
    void mouseWheel(const MouseWheelEvent& mouseWheelEvent) const override;
    void keyDown(const KeyDownEvent& keyDownEvent) const override;
    void keyUp(const KeyUpEvent& keyUpEvent) const override;

    void setViewport(const filament::Viewport& viewport);
    void setCamera(filament::Camera* camera);

    [[nodiscard]] filament::View* getFilamentView();
    [[nodiscard]] filament::Camera* getCamera();
    [[nodiscard]] CameraManipulator* getCameraManipulator();

  private:
    RenderableIdentifier addRenderable(FilAppRenderable&& filAppRenderable);
    void clearFilAppRenderables();
    bool manipulatorKeyFromKeycode(SDL_Scancode scancode,
                                   CameraManipulator::Key& key) const;
    void configureCameraProjection();
};
} // namespace FilApp

#endif // FILAPP_FILAPPVIEW_HPP
