#ifndef FILAPP_FILAPPCAMERAVIEW_HPP
#define FILAPP_FILAPPCAMERAVIEW_HPP

#include <Core/Utils/Warnings.h>
DISABLE_ALL_WARNINGS
#include <camutils/Manipulator.h>
#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/View.h>
#include <filament/Viewport.h>
#include <utils/Entity.h>
ENABLE_ALL_WARNINGS
#include <Core/Types/TString.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppGuiContext.hpp>
#include <FilApp/FilAppRenderable.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <FilApp/FilAppScene.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/View.hpp>
#include <Graphics/ViewConfig.hpp>
#include <filapp_export.h>
#include <functional>
#include <memory>

extern template class filament::camutils::Manipulator<float>;

namespace FilApp
{

using AnimationCallBack = std::function<void(double_t now)>;

class FilAppCameraView final : public Graphics::View {
public:
  using CameraManipulator = filament::camutils::Manipulator<float_t>;

private:
  Core::TString m_name;
  filament::Renderer* m_renderer{nullptr};
  filament::Engine* m_engine = nullptr;
  filament::View* m_filamentView = nullptr;
  std::reference_wrapper<FilAppScene> m_filAppScene;
  std::unique_ptr<Graphics::Gui> m_gui;

  std::unique_ptr<CameraManipulator> m_cameraManipulator = nullptr;
  filament::Camera* m_camera = nullptr;
  utils::Entity m_cameraEntity;
  CameraManipulator::Bookmark m_cameraHomeBookMark{};

  Graphics::ViewConfig m_viewConfig;
  filament::Viewport m_filamentViewport;

  Graphics::InputEventDispatcher m_inputEventDispatcher;
  Graphics::RayPickEventDispatcher m_rayPickEventDispatcher;

  Core::TVector<AnimationCallBack> m_animationCallbacks;

public:
  FilAppCameraView(const Graphics::ViewConfig& viewConfig, FilAppScene& filAppScene, filament::Renderer* renderer);

  ~FilAppCameraView() override;

  CORE_NODISCARD Graphics::InputEventDispatcher& getInputEventDispatcher() override;
  CORE_NODISCARD Graphics::RayPickEventDispatcher& getRayPickEventDispatcher() override;

  // clang-format off
    CORE_NODISCARD auto addRenderable(Graphics::TriangleRenderable&& renderable) -> Graphics::RenderableId override;
    CORE_NODISCARD auto addRenderable(Graphics::PointRenderable&& renderable) -> Graphics::RenderableId override;
    CORE_NODISCARD auto addRenderable(Graphics::LineRenderable&& lineRenderable) -> Graphics::RenderableId override;
    CORE_NODISCARD auto getRenderableIdentifiers() const -> Core::TVector<Graphics::RenderableId> override;
    void removeRenderable(Graphics::RenderableId id) override;
    void updatePosition(Graphics::RenderableId renderableId, const Graphics::Vec3 & position) override;
    void clearRenderables() override;
  // clang-format on

  void addRotationAnimation(Graphics::RenderableId renderableIdentifier, const Graphics::Vec3& rotationAxis) override;

  CORE_NODISCARD Graphics::Viewport getViewport() const override;
  void setViewport(const Graphics::Viewport& viewport) override;

  void onEvent(const Graphics::MouseButtonEvent& mouseButtonEvent) override;
  void onEvent(const Graphics::MouseMoveEvent& mouseMoveEvent) override;
  void onEvent(const Graphics::MouseWheelEvent& mouseWheelEvent) override;
  void onEvent(const Graphics::KeyEvent& keyEvent) override;

  void animate(double_t deltaT) override;

  void render(double_t timeStepInSeconds) override;

  void setCamera(filament::Camera* camera);

  void setFilAppScene(FilAppScene& filAppScene);

  CORE_NODISCARD filament::View* getFilamentView();
  CORE_NODISCARD filament::Camera* getCamera();
  CORE_NODISCARD CameraManipulator* getCameraManipulator();

private:
  void configureCameraProjection();
  CORE_NODISCARD static bool manipulatorKeyFromKeycode(Graphics::KeyScancode scancode, CameraManipulator::Key& key);

  CORE_NODISCARD Graphics::PickRayEvent getPickRayMoveEvent(std::size_t x, std::size_t y, double_t time) const;
};
} // namespace FilApp

#endif // FILAPP_FILAPPCAMERAVIEW_HPP
