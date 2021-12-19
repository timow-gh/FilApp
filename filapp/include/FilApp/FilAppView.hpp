#ifndef FILAPP_FILAPPVIEW_HPP
#define FILAPP_FILAPPVIEW_HPP

#include "FilAppConversion.hpp"
#include <FilApp/FilAppRenderable.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <FilAppInterfaces/View.hpp>
#include <FilAppInterfaces/ViewConfig.hpp>
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
    filament::Viewport m_viewport;
    utils::Entity m_globalTrafoComponent;

    std::map<RenderableId, std::unique_ptr<PointRenderable>> m_pointRenderables;
    std::map<RenderableId, std::unique_ptr<LineRenderable>> m_lineRenderables;
    std::map<RenderableId, std::unique_ptr<TriangleRenderable>>
        m_triangleRenderables;

    FilAppRenderableCreator m_renderableCreator;
    std::vector<FilAppRenderable> m_filAppRenderables;

    float_t m_near{0.1f};
    float_t m_far{100.0f};
    float_t m_orthogonalCameraZoom{3.0f};

    std::vector<AnimationCallBack> m_animationCallbacks;

  public:
    FilAppView(const ViewConfig& viewConfig, filament::Renderer& renderer);
    ~FilAppView() override;

    // clang-format off
    [[nodiscard]] auto addRenderable(TriangleRenderable&& renderable) -> RenderableId override;
    [[nodiscard]] auto addRenderable(PointRenderable && renderable) -> RenderableId override;
    [[nodiscard]] auto addRenderable(LineRenderable && renderable) -> RenderableId override;
    [[nodiscard]] auto getRenderableIdentifiers() const -> std::vector<RenderableId> override;
    void removeRenderable(RenderableId id) override;
    void updatePosition(RenderableId renderableId, const Vec3 & position) override;
    void clearRenderables() override;
    // clang-format on

    void setUsePostprocessing(bool usePostProcessing) override;

    void addRotationAnimation(RenderableId renderableIdentifier,
                              const Vec3& rotationAxis) override;

    [[nodiscard]] Viewport getViewport() const override;
    void setViewport(const Viewport& viewport);
    void setCamera(filament::Camera* camera);
    void resize(const Viewport& viewport) override;

    void event(const MouseDownEvent& mouseDownEvent) override;
    void event(const MouseUpEvent& mouseUpEvent) override;
    void event(const MouseMoveEvent& mouseMoveEvent) override;
    void event(const MouseWheelEvent& mouseWheelEvent) override;
    void event(const KeyDownEvent& keyDownEvent) override;
    void event(const KeyUpEvent& keyUpEvent) override;

    void animate(double deltaT) override;

    [[nodiscard]] filament::View* getFilamentView();
    [[nodiscard]] filament::Camera* getCamera();
    [[nodiscard]] CameraManipulator* getCameraManipulator();

  private:
    [[nodiscard]] static bool
    manipulatorKeyFromKeycode(SDL_Scancode scancode,
                              CameraManipulator::Key& key);

    [[nodiscard]] RenderableId
    addRenderable(const FilAppRenderable& filAppRenderable);
    void clearFilAppRenderables();
    void configureOrthogonalProjection(float_t near, float_t far, float_t zoom);

    template <typename V>
    void eraseFromMap(std::map<RenderableId, V>& map, RenderableId id)
    {
        auto idIter = map.find(id);
        if (idIter != map.end())
            map.erase(idIter);
    }

    void eraseRenderable(RenderableId id)
    {
        eraseFromMap(m_pointRenderables, id);
        eraseFromMap(m_lineRenderables, id);
        eraseFromMap(m_triangleRenderables, id);
    }

    FilAppRenderable* findFilAppRenderable(RenderableId id)
    {
        if (!std::is_sorted(m_filAppRenderables.begin(),
                            m_filAppRenderables.end()))
            std::sort(m_filAppRenderables.begin(), m_filAppRenderables.end());

        utils::Entity entity = utils::Entity::import(id.getId());
        auto iter = std::lower_bound(
            m_filAppRenderables.begin(),
            m_filAppRenderables.end(),
            entity,
            [](const FilAppRenderable& filAppRenderable, utils::Entity entity)
            {
                return filAppRenderable.renderableEntity < entity;
            });
        if (iter != m_filAppRenderables.cend())
            return &(*iter);
        return nullptr;
    }

    void translateRenderable(RenderableId id,
                             const filament::math::float3 translation)
    {
    }

    [[nodiscard]] PickRayEvent
    getPickRayMoveEvent(std::size_t x, std::size_t y, double_t time) const
    {
        filament::math::float3 origin;
        filament::math::float3 direction;
        m_cameraManipulator->getRay(static_cast<int>(x),
                                    static_cast<int>(y),
                                    &origin,
                                    &direction);
        return {toGlobalCS(origin), toGlobalCS(direction),
                time};
    }
};
} // namespace FilApp

#endif // FILAPP_FILAPPVIEW_HPP
