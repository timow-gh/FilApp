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
    : m_engine(renderer.getEngine()), m_name(viewConfig.name)
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

    filament::camutils::Mode cameraMode = calcCameraMode(viewConfig.cameraMode);
    if (cameraMode == filament::camutils::Mode::ORBIT)
        m_cameraManipulator = std::unique_ptr<CameraManipulator>(
            CameraManipulator::Builder()
                .orbitHomePosition(eye[0], eye[1], eye[2])
                .targetPosition(center[0], center[1], center[2])
                .upVector(up[0], up[1], up[2])
                .zoomSpeed(1.0)
                .build(cameraMode));
    else if (cameraMode == filament::camutils::Mode::FREE_FLIGHT)
        m_cameraManipulator = std::unique_ptr<CameraManipulator>(
            CameraManipulator::Builder()
                .flightStartPosition(eye[0], eye[1], eye[2])
                .flightMoveDamping(15.0)
                .build(cameraMode));
    else
        CORE_POSTCONDITION_ASSERT(false, "Camera not implemented.");

    m_renderableCreator = FilAppRenderableCreator::create(m_engine);

    m_globalTrafoComponent = utils::EntityManager::get().create();
    auto& tcm = m_engine->getTransformManager();
    tcm.create(m_globalTrafoComponent);
    auto globalInstance = tcm.getInstance(m_globalTrafoComponent);
    tcm.setTransform(globalInstance, filCSToGlobalCS4());

    setViewport(viewConfig.viewport);
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

void FilAppView::configureOrthogonalProjection(float_t near,
                                               float_t far,
                                               float_t zoom)
{
    CORE_PRECONDITION_DEBUG_ASSERT(near < far, "Invalid near and far plane.");
    const float_t aspect =
        (float_t)m_viewport.width / (float_t)m_viewport.height;
    m_camera->setProjection(filament::Camera::Projection::ORTHO,
                            -aspect * zoom,
                            aspect * zoom,
                            -zoom,
                            zoom,
                            near,
                            far);
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

RenderableId FilAppView::addRenderable(LineRenderable&& lineREnderable)
{
    auto renderable =
        std::make_unique<LineRenderable>(std::move(lineREnderable));

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

    auto& tcm = m_engine->getTransformManager();
    tcm.setTransform(
        tcm.getInstance(renderable->renderableEntity),
        filament::math::mat4f::translation(
            filament::math::float3{position[0], position[1], position[2]}));
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
    return {m_viewport.left,
            m_viewport.bottom,
            m_viewport.width,
            m_viewport.height};
}

void FilAppView::setViewport(const Viewport& viewport)
{
    m_viewport = calcViewport(viewport);
    m_filamentView->setViewport(m_viewport);
    configureOrthogonalProjection(m_near, m_far, m_orthogonalCameraZoom);
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
    setViewport(viewport);
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
        m_cameraManipulator->scroll(0, 0, mouseWheelEvent.x);
        m_orthogonalCameraZoom -= mouseWheelEvent.x * 1.5;
        configureOrthogonalProjection(m_near, m_far, m_orthogonalCameraZoom);
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
