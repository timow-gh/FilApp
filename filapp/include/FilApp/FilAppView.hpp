#ifndef FILAPP_FILAPPVIEW_HPP
#define FILAPP_FILAPPVIEW_HPP

#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppRenderable.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <GraphicsInterface/View.hpp>
#include <GraphicsInterface/ViewConfig.hpp>
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

namespace Graphics
{
using AnimationCallBack = std::function<void(double now)>;

class FilAppView : public View {
  public:
    using CameraManipulator = filament::camutils::Manipulator<float_t>;

  private:
    std::string m_name;
    filament::Engine* m_engine = nullptr;
    filament::View* m_filamentView = nullptr;
    filament::Scene* m_scene = nullptr;
    filament::Skybox* m_skybox = nullptr;

    std::unique_ptr<CameraManipulator> m_cameraManipulator = nullptr;
    filament::Camera* m_camera = nullptr;
    utils::Entity m_cameraEntity;
    utils::Entity m_globalTrafoComponent;

    ViewConfig m_viewConfig;
    filament::Viewport m_filamentViewport;

    std::map<RenderableId, std::unique_ptr<PointRenderable>> m_pointRenderables;
    std::map<RenderableId, std::unique_ptr<LineRenderable>> m_lineRenderables;
    std::map<RenderableId, std::unique_ptr<TriangleRenderable>> m_triangleRenderables;

    FilAppRenderableCreator m_renderableCreator;
    std::vector<FilAppRenderable> m_filAppRenderables;

    std::vector<AnimationCallBack> m_animationCallbacks;

    InputEventDispatcher m_inputEventDispatcher;
    RayPickEventDispatcher m_rayPickEventDispatcher;

  public:
    FilAppView() = default;
    FilAppView(const ViewConfig& viewConfig, filament::Renderer& renderer);
    ~FilAppView() override;

    CORE_NODISCARD InputEventDispatcher& getInputEventDispatcher() override;
    CORE_NODISCARD RayPickEventDispatcher& getRayPickEventDispatcher() override;

    // clang-format off
    CORE_NODISCARD auto addRenderable(TriangleRenderable&& renderable) -> RenderableId override;
    CORE_NODISCARD auto addRenderable(PointRenderable && renderable) -> RenderableId override;
    CORE_NODISCARD auto addRenderable(LineRenderable && lineRenderable) -> RenderableId override;
    CORE_NODISCARD auto getRenderableIdentifiers() const -> std::vector<RenderableId> override;
    void removeRenderable(RenderableId id) override;
    void updatePosition(RenderableId renderableId, const Vec3 & position) override;
    void clearRenderables() override;
    // clang-format on

    void setUsePostprocessing(bool usePostProcessing) override;

    void addRotationAnimation(RenderableId renderableIdentifier, const Vec3& rotationAxis) override;

    CORE_NODISCARD Viewport getViewport() const override;
    void updateViewPort(const Viewport& viewport);
    void setCamera(filament::Camera* camera);
    void resize(const Viewport& viewport) override;

    void event(const MouseButtonEvent& mouseButtonEvent) override;
    void event(const MouseMoveEvent& mouseMoveEvent) override;
    void event(const MouseWheelEvent& mouseWheelEvent) override;
    void event(const KeyEvent& keyEvent) override;

    void animate(double deltaT) override;

    CORE_NODISCARD filament::View* getFilamentView();
    CORE_NODISCARD filament::Camera* getCamera();
    CORE_NODISCARD CameraManipulator* getCameraManipulator();

  private:
    CORE_NODISCARD static bool manipulatorKeyFromKeycode(Graphics::KeyScancode scancode,
                                                         CameraManipulator::Key& key);

    //! Adds the global to filament transformation to all renderables.
    CORE_NODISCARD RenderableId addRenderable(const FilAppRenderable& filAppRenderable);
    void clearFilAppRenderables();
    void configureCameraProjection();

    template <typename V>
    void eraseFromMap(std::map<RenderableId, V>& map, RenderableId id)
    {
        auto idIter = map.find(id);
        if (idIter != map.end())
            map.erase(idIter);
    }

    void eraseRenderable(RenderableId id);
    CORE_NODISCARD FilAppRenderable* findFilAppRenderable(RenderableId id);
    CORE_NODISCARD PickRayEvent getPickRayMoveEvent(std::size_t x,
                                                    std::size_t y,
                                                    double_t time) const;
};
} // namespace Graphics

#endif // FILAPP_FILAPPVIEW_HPP
