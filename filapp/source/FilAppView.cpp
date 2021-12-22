#include "FilApp/FilAppView.hpp"
#include "FilApp/FilAppConversion.hpp"
#include <Core/Utils/Assert.hpp>
#include <FilApp/FilamentCoordinateSystem.hpp>
#include <camutils/Bookmark.h>
#include <filament/Options.h>
#include <filament/TransformManager.h>
#include <math/mat4.h>
#include <math/mathfwd.h>
#include <math/vec3.h>
#include <utility>

namespace FilApp
{
FilAppView::FilAppView(const ViewConfig& viewConfig,
                       filament::Renderer& renderer)
    : m_engine(renderer.getEngine())
    , m_name(viewConfig.name)
    , m_viewConfig(viewConfig)
{
    m_filamentView = m_engine->createView();
    m_filamentView->setName(m_name.c_str());

    if (viewConfig.useFXAA)
    {
        m_filamentView->setAntiAliasing(filament::AntiAliasing::FXAA);
        m_filamentView->setSampleCount(viewConfig.fxaaSampleCount);
    }

    m_scene = m_engine->createScene();
    m_filamentView->setScene(m_scene);

    m_skybox = filament::Skybox::Builder()
                   .color(vec4ToFloat4(viewConfig.skyBoxColor))
                   .build(*m_engine);
    m_scene->setSkybox(m_skybox);

    utils::EntityManager& entityManager = utils::EntityManager::get();
    m_cameraEntity = entityManager.create();
    m_camera = m_engine->createCamera(m_cameraEntity);

    const filament::math::float3 eye = toFilamentCS(viewConfig.eye);
    const filament::math::float3 center = toFilamentCS(viewConfig.center);
    const filament::math::float3 up = toFilamentCS(viewConfig.up);
    m_camera->lookAt(eye, center, up);
    m_filamentView->setCamera(m_camera);

    filament::camutils::Mode cameraMode =
        toFilamentCameraMode(viewConfig.cameraMode);
    const Viewport& vport = viewConfig.viewport;
    if (cameraMode == filament::camutils::Mode::ORBIT)
        m_cameraManipulator = std::unique_ptr<CameraManipulator>(
            CameraManipulator::Builder()
                // TODO Settings
                .fovDegrees(m_viewConfig.fieldOfViewInDegree)
                .fovDirection(toFilamentFovDirection(m_viewConfig.fovDirection,
                                                     FilamentCamUtilsTag()))
                .farPlane(m_viewConfig.far)
                .orbitHomePosition(eye[0], eye[1], eye[2])
                .targetPosition(center[0], center[1], center[2])
                .upVector(up[0], up[1], up[2])
                .zoomSpeed(0.01)
                // TODO mapExtent
                // .mapExtent()
                .build(toFilamentCameraMode(m_viewConfig.cameraMode)));
    else
        CORE_POSTCONDITION_ASSERT(false, "Camera not implemented.");

    m_renderableCreator = FilAppRenderableCreator::create(m_engine);

    m_globalTrafoComponent = utils::EntityManager::get().create();
    auto& tcm = m_engine->getTransformManager();
    tcm.create(m_globalTrafoComponent);
    auto globalInstance = tcm.getInstance(m_globalTrafoComponent);
    tcm.setTransform(globalInstance, filCSToGlobalCS4());

    updateViewPort(m_viewConfig.viewport);
}

FilAppView::~FilAppView()
{
    utils::EntityManager& entityManager = utils::EntityManager::get();
    clearFilAppRenderables();
    entityManager.destroy(m_cameraEntity);
    m_engine->destroyCameraComponent(m_cameraEntity);
    m_engine->destroy(m_skybox);
    m_engine->destroy(m_filamentView);
    m_engine->destroy(m_scene);
    auto& tcm = utils::EntityManager::get();
    tcm.destroy(m_globalTrafoComponent);
}

void FilAppView::animate(double deltaT)
{
    for (const auto& animationCallBack: m_animationCallbacks)
        animationCallBack(deltaT);
}

filament::View* FilAppView::getFilamentView()
{
    return m_filamentView;
}

filament::Camera* FilAppView::getCamera()
{
    return m_camera;
}

FilAppView::CameraManipulator* FilAppView::getCameraManipulator()
{
    return m_cameraManipulator.get();
}

void FilAppView::configureCameraProjection()
{
    CORE_PRECONDITION_DEBUG_ASSERT(m_viewConfig.near < m_viewConfig.far,
                                   "Invalid near and far plane.");
    const float_t aspect =
        (float_t)m_filamentViewport.width / (float_t)m_filamentViewport.height;

    switch (m_viewConfig.cameraProjection)
    {
    case ViewConfig::CameraProjection::ORTHOGRAPHIC:
        m_camera->setProjection(
            toFilamentProjection(m_viewConfig.cameraProjection),
            -aspect * m_viewConfig.orthogonalCameraZoom,
            aspect * m_viewConfig.orthogonalCameraZoom,
            -m_viewConfig.orthogonalCameraZoom,
            m_viewConfig.orthogonalCameraZoom,
            m_viewConfig.near,
            m_viewConfig.far);
        break;
    case ViewConfig::CameraProjection::PERSPECTIVE:
        m_camera->setProjection(
            m_viewConfig.fieldOfViewInDegree,
            aspect,
            m_viewConfig.near,
            m_viewConfig.far,
            toFilamentFovDirection(m_viewConfig.fovDirection,
                                   FilamentCameraTag()));
        break;
    }
}

RenderableId FilAppView::addRenderable(TriangleRenderable&& triangleRenderable)
{
    auto renderable =
        std::make_unique<TriangleRenderable>(std::move(triangleRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::TRIANGLES));

    m_triangleRenderables.emplace(id, std::move(renderable));

    return id;
}

RenderableId FilAppView::addRenderable(PointRenderable&& pointRenderable)
{
    auto renderable =
        std::make_unique<PointRenderable>(std::move(pointRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::POINTS));

    m_pointRenderables.emplace(id, std::move(renderable));

    return id;
}

RenderableId FilAppView::addRenderable(LineRenderable&& lineRenderable)
{
    auto renderable =
        std::make_unique<LineRenderable>(std::move(lineRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::LINES));

    m_lineRenderables.emplace(id, std::move(renderable));
    return id;
}

std::vector<RenderableId> FilAppView::getRenderableIdentifiers() const
{
    std::vector<RenderableId> result;
    for (const auto& filAppRenderable: m_filAppRenderables)
        result.emplace_back(filAppRenderable.renderableEntity.getId());
    return result;
}

void FilAppView::removeRenderable(RenderableId id)
{
    eraseRenderable(id);
    auto iter =
        std::remove_if(m_filAppRenderables.begin(),
                       m_filAppRenderables.end(),
                       [id = id, scene = m_scene](const FilAppRenderable& item)
                       {
                           if (item.renderableEntity.getId() == id.getId())
                           {
                               scene->remove(item.renderableEntity);
                               item.destroy();
                               return true;
                           }
                           return false;
                       });
    m_filAppRenderables.erase(iter, m_filAppRenderables.end());
}

void FilAppView::updatePosition(RenderableId renderableId, const Vec3& position)
{
    FilAppRenderable* renderable = findFilAppRenderable(renderableId);
    CORE_POSTCONDITION_DEBUG_ASSERT(renderable, "FilAppRenderable not found.");
    if (!renderable)
        return;

    filament::math::float3 filPos = vec3ToFloat3(position);
    auto& tcm = m_engine->getTransformManager();
    auto instance = tcm.getInstance(renderable->renderableEntity);
    auto trafo = tcm.getTransform(instance);
    filament::math::float4& matTranslation = trafo[3];
    matTranslation = filament::math::float4{filPos, 1};
    tcm.setTransform(instance, trafo);
}

void FilAppView::clearRenderables()
{
    clearFilAppRenderables();
}

void FilAppView::setUsePostprocessing(bool usePostProcessing)
{
    m_filamentView->setPostProcessingEnabled(usePostProcessing);
}

void FilAppView::addRotationAnimation(RenderableId renderableIdentifier,
                                      const Vec3& rotationAxis)
{
    m_animationCallbacks.emplace_back(
        [renderableIdentifier, engine = m_engine](double deltaT)
        {
            auto& tcm = engine->getTransformManager();
            tcm.setTransform(
                tcm.getInstance(utils::Entity::import(
                    static_cast<int>(renderableIdentifier.getId()))),
                filament::math::mat4f::rotation(
                    deltaT * 0.4,
                    filament::math::float3{0, 1, 0}));
        });
}

Viewport FilAppView::getViewport() const
{
    return {m_filamentViewport.left,
            m_filamentViewport.bottom,
            m_filamentViewport.width,
            m_filamentViewport.height};
}

void FilAppView::updateViewPort(const Viewport& viewport)
{
    m_viewConfig.viewport = viewport;
    m_filamentViewport = toFilamentViewport(viewport);
    m_filamentView->setViewport(m_filamentViewport);
    configureCameraProjection();

    if (m_cameraManipulator)
        m_cameraManipulator->setViewport(static_cast<int>(viewport.width),
                                         static_cast<int>(viewport.height));
}

void FilAppView::setCamera(filament::Camera* camera)
{
    m_filamentView->setCamera(camera);
}

void FilAppView::resize(const Viewport& viewport)
{
    updateViewPort(viewport);
}

void FilAppView::event(const MouseDownEvent& mouseDownEvent)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabBegin(static_cast<int>(mouseDownEvent.pos.x),
                                       static_cast<int>(mouseDownEvent.pos.y),
                                       mouseDownEvent.button == 3);
    for (auto listener: InputEventDispatcher::m_listener)
        listener->event(mouseDownEvent);
}

void FilAppView::event(const MouseUpEvent& mouseUpEvent)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabEnd();
    for (auto listener: InputEventDispatcher::m_listener)
        listener->event(mouseUpEvent);

    PickRayEvent pickRayEvent = getPickRayMoveEvent(mouseUpEvent.pos.x,
                                                    mouseUpEvent.pos.y,
                                                    mouseUpEvent.time);
    for (RayPickEventListener* listener: RayPickEventDispatcher::m_listener)
        listener->event(pickRayEvent);
}

void FilAppView::event(const MouseMoveEvent& mouseMoveEvent)
{
    const int x = static_cast<int>(mouseMoveEvent.pos.x);
    const int y = static_cast<int>(mouseMoveEvent.pos.y);
    if (m_cameraManipulator)
        m_cameraManipulator->grabUpdate(x, y);
    for (auto listener: InputEventDispatcher::m_listener)
        listener->event(mouseMoveEvent);

    PickRayEvent pickRayEvent = getPickRayMoveEvent(mouseMoveEvent.pos.x,
                                                    mouseMoveEvent.pos.y,
                                                    mouseMoveEvent.time);
    for (RayPickEventListener* listener: RayPickEventDispatcher::m_listener)
        listener->event(PickRayMoveEvent(pickRayEvent.origin,
                                         pickRayEvent.direction,
                                         pickRayEvent.time));
}

void FilAppView::event(const MouseWheelEvent& mouseWheelEvent)
{
    if (m_cameraManipulator)
    {
        if (m_viewConfig.cameraProjection ==
            ViewConfig::CameraProjection::ORTHOGRAPHIC)
        {
            m_viewConfig.orthogonalCameraZoom +=
                mouseWheelEvent.x * m_viewConfig.scrollMultiplierOrthographic;
            configureCameraProjection();
        }
        else
        {
            float_t scrollValue =
                mouseWheelEvent.x * m_viewConfig.scrollMultiplierPerspective;
            m_cameraManipulator->scroll(0, 0, scrollValue);
            filament::math::float3 eye;
            filament::math::float3 target;
            filament::math::float3 up;
            m_cameraManipulator->getLookAt(&eye, &target, &up);
            m_camera->lookAt(eye, target, up);
        }
    }

    for (auto listener: InputEventDispatcher::m_listener)
        listener->event(mouseWheelEvent);
}
void FilAppView::event(const KeyDownEvent& keyDownEvent)
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(keyDownEvent.sdlScancode, key))
            m_cameraManipulator->keyDown(key);
    }
    for (auto listener: InputEventDispatcher::m_listener)
        listener->event(keyDownEvent);
}

void FilAppView::event(const KeyUpEvent& keyUpEvent)
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(keyUpEvent.sdlScancode, key))
        {
            m_cameraManipulator->keyDown(key);
        }
    }
    for (auto listener: InputEventDispatcher::m_listener)
        listener->event(keyUpEvent);
}

bool FilAppView::manipulatorKeyFromKeycode(
    SDL_Scancode scancode,
    filament::camutils::Manipulator<float_t>::Key& key)
{
    switch (scancode)
    {
    case SDL_SCANCODE_W: key = CameraManipulator::Key::FORWARD; return true;
    case SDL_SCANCODE_A: key = CameraManipulator::Key::LEFT; return true;
    case SDL_SCANCODE_S: key = CameraManipulator::Key::BACKWARD; return true;
    case SDL_SCANCODE_D: key = CameraManipulator::Key::RIGHT; return true;
    case SDL_SCANCODE_E: key = CameraManipulator::Key::UP; return true;
    case SDL_SCANCODE_Q: key = CameraManipulator::Key::DOWN; return true;
    default: return false;
    }
}

RenderableId FilAppView::addRenderable(const FilAppRenderable& filAppRenderable)
{
    m_filAppRenderables.emplace_back(filAppRenderable);
    auto entity = m_filAppRenderables.back().renderableEntity;
    m_scene->addEntity(entity);

    // Setting the global to filament coordinate system transformation for all
    // renderables.
    auto& tcm = m_engine->getTransformManager();
    auto globalInstance = tcm.getInstance(m_globalTrafoComponent);
    auto renderableInstance = tcm.getInstance(entity);
    tcm.setParent(renderableInstance, globalInstance);

    return RenderableId(m_filAppRenderables.back().renderableEntity.getId());
}

void FilAppView::clearFilAppRenderables()
{
    for (auto& renderable: m_filAppRenderables)
    {
        m_scene->remove(renderable.renderableEntity);
        renderable.destroy();
    }
    m_filAppRenderables.clear();
}
} // namespace FilApp
