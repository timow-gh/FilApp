#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilAppView.hpp>
#include <FilApp/FilamentCoordinateSystem.hpp>
#include <camutils/Bookmark.h>
#include <filament/Options.h>
#include <filament/TransformManager.h>
#include <math/mat4.h>
#include <math/mathfwd.h>
#include <math/vec3.h>
#include <utility>

#ifndef NDEBUG
#define DEBUG_CHECK_CAMERA_MANIP()                                                                 \
    CORE_PRECONDITION_DEBUG_ASSERT(m_cameraManipulator, "Camera manipulator not set.");
#else
#define DEBUG_CHECK_CAMERA_MANIP()
#endif

namespace Graphics
{
FilAppView::FilAppView(const ViewConfig& viewConfig, filament::Renderer& renderer)
    : m_engine(renderer.getEngine()), m_name(viewConfig.name), m_viewConfig(viewConfig)
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

    auto colorVec = Vec4{viewConfig.skyBoxColor.getRed(),
                         viewConfig.skyBoxColor.getGreen(),
                         viewConfig.skyBoxColor.getBlue(),
                         viewConfig.skyBoxColor.getAlpha()};
    m_skybox = filament::Skybox::Builder().color(vec4ToFloat4(colorVec)).build(*m_engine);
    m_scene->setSkybox(m_skybox);

    utils::EntityManager& entityManager = utils::EntityManager::get();
    m_cameraEntity = entityManager.create();
    m_camera = m_engine->createCamera(m_cameraEntity);

    const filament::math::float3 eye = toFilamentCS(viewConfig.eye);
    const filament::math::float3 center = toFilamentCS(viewConfig.center);
    const filament::math::float3 up = toFilamentCS(viewConfig.up);
    m_camera->lookAt(eye, center, up);
    m_filamentView->setCamera(m_camera);

    filament::camutils::Mode cameraMode = toFilamentCameraMode(viewConfig.cameraMode);
    const Viewport& vport = viewConfig.viewport;
    if (cameraMode == filament::camutils::Mode::ORBIT)
        m_cameraManipulator = std::unique_ptr<CameraManipulator>(
            CameraManipulator::Builder()
                // TODO Settings
                .fovDegrees(m_viewConfig.fieldOfViewInDegree)
                .fovDirection(
                    toFilamentFovDirection(m_viewConfig.fovDirection, FilamentCamUtilsTag()))
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

InputEventDispatcher& FilAppView::getInputEventDispatcher()
{
    return m_inputEventDispatcher;
}

RayPickEventDispatcher& FilAppView::getRayPickEventDispatcher()
{
    return m_rayPickEventDispatcher;
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

void FilAppView::animate(double_t deltaT)
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
    const float_t aspect = (float_t)m_filamentViewport.width / (float_t)m_filamentViewport.height;

    switch (m_viewConfig.cameraProjection)
    {
    case ViewConfig::CameraProjection::ORTHOGRAPHIC:
        m_camera->setProjection(toFilamentProjection(m_viewConfig.cameraProjection),
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
            toFilamentFovDirection(m_viewConfig.fovDirection, FilamentCameraTag()));
        break;
    }
}

RenderableId FilAppView::addRenderable(TriangleRenderable&& triangleRenderable)
{
    auto renderable = std::make_unique<TriangleRenderable>(std::move(triangleRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::TRIANGLES));

    m_triangleRenderables.emplace(id, std::move(renderable));

    return id;
}

RenderableId FilAppView::addRenderable(PointRenderable&& pointRenderable)
{
    auto renderable = std::make_unique<PointRenderable>(std::move(pointRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::POINTS));

    m_pointRenderables.emplace(id, std::move(renderable));

    return id;
}

RenderableId FilAppView::addRenderable(LineRenderable&& lineRenderable)
{
    auto renderable = std::make_unique<LineRenderable>(std::move(lineRenderable));

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
    auto iter = std::remove_if(m_filAppRenderables.begin(),
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

void FilAppView::addRotationAnimation(RenderableId renderableIdentifier, const Vec3& rotationAxis)
{
    m_animationCallbacks.emplace_back(
        [renderableIdentifier, engine = m_engine](double_t deltaT)
        {
            auto& tcm = engine->getTransformManager();
            tcm.setTransform(
                tcm.getInstance(
                    utils::Entity::import(static_cast<int>(renderableIdentifier.getId()))),
                filament::math::mat4f::rotation(deltaT * 0.4, filament::math::float3{0, 1, 0}));
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
    CORE_PRECONDITION_DEBUG_ASSERT(m_filamentView, "Filament view not set.");
    DEBUG_CHECK_CAMERA_MANIP();

    m_viewConfig.viewport = viewport;
    m_filamentViewport = toFilamentViewport(viewport);
    m_filamentView->setViewport(m_filamentViewport);
    configureCameraProjection();
    m_cameraManipulator->setViewport(static_cast<int>(viewport.width),
                                     static_cast<int>(viewport.height));
}

void FilAppView::setCamera(filament::Camera* camera)
{
    CORE_PRECONDITION_DEBUG_ASSERT(camera, "Camera not set.");
    CORE_PRECONDITION_DEBUG_ASSERT(m_filamentView, "Filament view not set.");
    m_filamentView->setCamera(camera);
}

void FilAppView::resize(const Viewport& viewport)
{
    updateViewPort(viewport);
}

void FilAppView::event(const MouseButtonEvent& mouseButtonEvent)
{
    DEBUG_CHECK_CAMERA_MANIP();
    switch (mouseButtonEvent.type)
    {
    case MouseButtonEvent::Type::PUSH:
    {
        if (mouseButtonEvent.buttonIndex == 2 || mouseButtonEvent.buttonIndex == 3)
        {
            m_cameraManipulator->grabBegin(static_cast<int>(mouseButtonEvent.x),
                                           static_cast<int>(mouseButtonEvent.y),
                                           mouseButtonEvent.buttonIndex == 2);
        }
        break;
    }
    case MouseButtonEvent::Type::REPEAT: break;
    case MouseButtonEvent::Type::RELEASE:
    {
        if (mouseButtonEvent.buttonIndex == 1)
            m_rayPickEventDispatcher.dispatch(getPickRayMoveEvent(mouseButtonEvent.x,
                                                                  mouseButtonEvent.y,
                                                                  mouseButtonEvent.deltaT));
        m_cameraManipulator->grabEnd();
        break;
    }
    }

    m_inputEventDispatcher.dispatch(mouseButtonEvent);
}

void FilAppView::event(const MouseMoveEvent& mouseMoveEvent)
{
    const int x = static_cast<int>(mouseMoveEvent.x);
    const int y = static_cast<int>(mouseMoveEvent.y);
    if (m_cameraManipulator)
        m_cameraManipulator->grabUpdate(x, y);

    m_inputEventDispatcher.dispatch(mouseMoveEvent);

    PickRayEvent pickRayEvent =
        getPickRayMoveEvent(mouseMoveEvent.x, mouseMoveEvent.y, mouseMoveEvent.deltaT);
    m_rayPickEventDispatcher.dispatch(
        PickRayMoveEvent(pickRayEvent.origin, pickRayEvent.direction, pickRayEvent.time));
}

void FilAppView::event(const MouseWheelEvent& mouseWheelEvent)
{
    DEBUG_CHECK_CAMERA_MANIP();

    if (m_viewConfig.cameraProjection == ViewConfig::CameraProjection::ORTHOGRAPHIC)
    {
        m_viewConfig.orthogonalCameraZoom +=
            mouseWheelEvent.x * m_viewConfig.scrollMultiplierOrthographic;
        configureCameraProjection();
    }
    else
    {
        float_t scrollValue = mouseWheelEvent.x * m_viewConfig.scrollMultiplierPerspective;
        m_cameraManipulator->scroll(0, 0, scrollValue);
        filament::math::float3 eye;
        filament::math::float3 target;
        filament::math::float3 up;
        m_cameraManipulator->getLookAt(&eye, &target, &up);
        m_camera->lookAt(eye, target, up);
    }

    m_inputEventDispatcher.dispatch(mouseWheelEvent);
}

void FilAppView::event(const KeyEvent& keyEvent)
{
    DEBUG_CHECK_CAMERA_MANIP();
    CameraManipulator::Key key;
    if (manipulatorKeyFromKeycode(keyEvent.keyScancode, key))
        m_cameraManipulator->keyDown(key);
    m_inputEventDispatcher.dispatch(keyEvent);
}

bool FilAppView::manipulatorKeyFromKeycode(Graphics::KeyScancode scancode,
                                           filament::camutils::Manipulator<float_t>::Key& key)
{
    switch (scancode)
    {
    case Graphics::KeyScancode::SCANCODE_W: key = CameraManipulator::Key::FORWARD; return true;
    case Graphics::KeyScancode::SCANCODE_A: key = CameraManipulator::Key::LEFT; return true;
    case Graphics::KeyScancode::SCANCODE_S: key = CameraManipulator::Key::BACKWARD; return true;
    case Graphics::KeyScancode::SCANCODE_D: key = CameraManipulator::Key::RIGHT; return true;
    case Graphics::KeyScancode::SCANCODE_E: key = CameraManipulator::Key::UP; return true;
    case Graphics::KeyScancode::SCANCODE_Q: key = CameraManipulator::Key::DOWN; return true;
    default: return false;
    }
}

RenderableId FilAppView::addRenderable(const FilAppRenderable& filAppRenderable)
{
    m_filAppRenderables.emplace_back(filAppRenderable);
    auto entity = m_filAppRenderables.back().renderableEntity;
    m_scene->addEntity(entity);

    // Setting the global to filament coordinate system transformation for
    // all renderables.
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

void FilAppView::eraseRenderable(RenderableId id)
{
    eraseFromMap(m_pointRenderables, id);
    eraseFromMap(m_lineRenderables, id);
    eraseFromMap(m_triangleRenderables, id);
}

FilAppRenderable* FilAppView::findFilAppRenderable(RenderableId id)

{
    if (!std::is_sorted(m_filAppRenderables.begin(), m_filAppRenderables.end()))
        std::sort(m_filAppRenderables.begin(), m_filAppRenderables.end());

    utils::Entity entity = utils::Entity::import(id.getId());
    auto iter = std::lower_bound(m_filAppRenderables.begin(),
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

PickRayEvent FilAppView::getPickRayMoveEvent(std::size_t x, std::size_t y, double_t time) const
{
    const float_t width = static_cast<float_t>(m_viewConfig.viewport.width);
    const float_t height = static_cast<float_t>(m_viewConfig.viewport.height);

    // Viewport coordinates to normalized device coordinates
    const float_t u = 2.0f * (0.5f + x) / width - 1.0f;
    const float_t v = 2.0f * (0.5f + y) / height - 1.0f;

    const filament::math::float3 cameraForward = m_camera->getForwardVector();
    const filament::math::float3 right = normalize(cross(cameraForward, m_camera->getUpVector()));
    const filament::math::float3 upward = cross(right, cameraForward);
    const float_t aspect = width / height;
    const float_t fov =
        static_cast<float_t>(m_viewConfig.fieldOfViewInDegree) * filament::math::f::PI / 180.0f;

    filament::math::float3 origin = m_camera->getPosition();
    filament::math::float3 direction = cameraForward;
    if (m_viewConfig.cameraProjection == ViewConfig::CameraProjection::PERSPECTIVE)
    {
        const float_t tangent = std::tan(fov / 2.0f);
        if (toFilamentFovDirection(m_viewConfig.fovDirection, FilamentCameraTag()) ==
            filament::Camera::Fov::VERTICAL)
        {
            direction += right * tangent * u * aspect;
            direction += upward * tangent * v;
        }
        else
        {
            direction += right * tangent * u;
            direction += upward * tangent * v / aspect;
        }
    }
    else
        CORE_POSTCONDITION_DEBUG_ASSERT(false,
                                        "Picking for this camera projetion not implemented.");

    direction = normalize(direction);
    return PickRayEvent{toGlobalCS(origin), toGlobalCS(direction), time};
}
} // namespace Graphics
