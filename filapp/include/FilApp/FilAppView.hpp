#ifndef FILAPP_FILAPPVIEW_HPP
#define FILAPP_FILAPPVIEW_HPP

#include "FilAppConversion.hpp"
#include <FilApp/FilAppRenderable.hpp>
#include <FilApp/FilAppRenderableCreator.hpp>
#include <FilApp/IOHelper.hpp>
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
    utils::Entity m_globalTrafoComponent;

    ViewConfig m_viewConfig;
    filament::Viewport m_filamentViewport;

    std::map<RenderableId, std::unique_ptr<PointRenderable>> m_pointRenderables;
    std::map<RenderableId, std::unique_ptr<LineRenderable>> m_lineRenderables;
    std::map<RenderableId, std::unique_ptr<TriangleRenderable>>
        m_triangleRenderables;

    FilAppRenderableCreator m_renderableCreator;
    std::vector<FilAppRenderable> m_filAppRenderables;

    std::vector<AnimationCallBack> m_animationCallbacks;

  public:
    FilAppView(const ViewConfig& viewConfig, filament::Renderer& renderer);
    ~FilAppView() override;

    // clang-format off
    [[nodiscard]] auto addRenderable(TriangleRenderable&& renderable) -> RenderableId override;
    [[nodiscard]] auto addRenderable(PointRenderable && renderable) -> RenderableId override;
    [[nodiscard]] auto addRenderable(LineRenderable && lineRenderable) -> RenderableId override;
    [[nodiscard]] auto getRenderableIdentifiers() const -> std::vector<RenderableId> override;
    void removeRenderable(RenderableId id) override;
    void updatePosition(RenderableId renderableId, const Vec3 & position) override;
    void clearRenderables() override;
    // clang-format on

    void setUsePostprocessing(bool usePostProcessing) override;

    void addRotationAnimation(RenderableId renderableIdentifier,
                              const Vec3& rotationAxis) override;

    [[nodiscard]] Viewport getViewport() const override;
    void updateViewPort(const Viewport& viewport);
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

    //! Adds the global to filament transformation to all renderables.
    [[nodiscard]] RenderableId
    addRenderable(const FilAppRenderable& filAppRenderable);
    void clearFilAppRenderables();
    void configureCameraProjection();

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

    [[nodiscard]] PickRayEvent
    getPickRayMoveEvent(std::size_t x, std::size_t y, double_t time) const
    {
        filament::math::float3 origin = m_camera->getPosition();
        filament::math::float3 direction;
//#define MATMUL
#ifdef MATMUL
        const float_t width = m_filamentViewport.width;
        const float_t height = m_filamentViewport.height;

        // Normalized device coordinates
        //        float ndcX = (2.0f * x) / width - 1.0f;
        //        float ndcY = 1.0 - (2.0f * y) / height;
        const float_t ndcX = 2.0 * (0.5 + x) / width - 1.0;
        const float_t ndcY = 2.0 * (0.5 + y) / height - 1.0;
        std::cout << "---------------------------------- " << std::endl;
        std::cout << "ndcX: " << ndcX << std::endl;
        std::cout << "ndcY: " << ndcY << std::endl << std::endl;

        // Homogeneous clip coordinates
        // No correct depth information needed for a picking ray.
        // Setting w = 1.0
        filament::math::float4 clipSpaceVec{ndcX, ndcY, -1.0, 1.0};

        // Camera coordinates
        filament::math::mat4 inverseProj =
            m_camera->inverseProjection(m_camera->getProjectionMatrix());
        filament::math::float4 cameraSpaceVec = inverseProj * clipSpaceVec;
        std::cout << "cameraSpaceVec: " << cameraSpaceVec[0] << ", "
                  << cameraSpaceVec[1] << ", " << cameraSpaceVec[2] << ", "
                  << cameraSpaceVec[3] << std::endl
                  << std::endl;

        // Filament coordinates
        filament::math::mat4 inverseCameraTrafo = m_camera->getViewMatrix();
        filament::math::float4 modelSpaceVec =
            inverseCameraTrafo * cameraSpaceVec;
        std::cout << "modelSpaceVec: " << modelSpaceVec[0] << ", "
                  << modelSpaceVec[1] << ", " << modelSpaceVec[2] << ", "
                  << modelSpaceVec[3] << std::endl
                  << std::endl;

        direction = {modelSpaceVec[0], modelSpaceVec[1], modelSpaceVec[2]};
        result = normalize(result);
        std::cout << "result: " << result[0] << ", " << result[1] << ", "
                  << result[2] << std::endl
                  << std::endl;

#endif

//#define asdf
#ifdef asdf
        filament::math::float3 const filament::math::float3 gaze =
            normalize(mTarget - mEye);
        const filament::math::float3 right =
            normalize(cross(gaze, mProps.upVector));
        const filament::math::float3 upward = cross(right, gaze);
        const flato_t width = m_filamentViewport.width;
        const flato_t height = m_filamentViewport.height;
        const flato_t fov = *F_PI / 180.0;

        // Remap the grid coordinate into [-1, +1] and shift it to the pixel
        // center.
        const FLOAT u = 2.0 * (0.5 + x) / width - 1.0;
        const FLOAT v = 2.0 * (0.5 + y) / height - 1.0;

        // Compute the tangent of the field-of-view angle as well as the aspect
        // ratio.
        const FLOAT tangent = tan(fov / 2.0);
        const FLOAT aspect = width / height;

        // Adjust the gaze so it goes through the pixel of interest rather than
        // the grid center.
        vec3 dir = gaze;
        if (mProps.fovDirection == Fov::VERTICAL)
        {
            dir += right * tangent * u * aspect;
            dir += upward * tangent * v;
        }
        else
        {
            dir += right * tangent * u;
            dir += upward * tangent * v / aspect;
        }
        dir = normalize(dir);

        *porigin = mEye;
        *pdir = dir;
#endif
        return PickRayEvent{float3ToVec3(origin),
                            float3ToVec3(direction),
                            time};
    }
};
} // namespace FilApp

#endif // FILAPP_FILAPPVIEW_HPP
