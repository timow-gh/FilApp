#include "FilApp/FilAppView.hpp"
#include <filament/TransformManager.h>
#include <iomanip>
#include <iostream>
#include <utility>

namespace FilApp
{
FilAppView::FilAppView(filament::Renderer& renderer,
                       std::string name,
                       const filament::Viewport& viewport,
                       filament::math::float4 skyBoxDefaultColor,
                       filament::camutils::Mode cameraMode)
    : m_engine(renderer.getEngine()), m_name(std::move(name))
{
    m_filamentView = m_engine->createView();
    m_filamentView->setName(m_name.c_str());

    m_filamentView->setAntiAliasing(filament::AntiAliasing::FXAA);
    m_filamentView->setSampleCount(8);

    m_scene = m_engine->createScene();
    m_filamentView->setScene(m_scene);

    m_skybox =
        filament::Skybox::Builder().color(skyBoxDefaultColor).build(*m_engine);
    m_scene->setSkybox(m_skybox);

    utils::EntityManager& entityManager = utils::EntityManager::get();
    m_cameraEntity = entityManager.create();
    m_camera = m_engine->createCamera(m_cameraEntity);
    m_camera->setExposure(16.0f, 1 / 125.0f, 100.0f);
    m_camera->lookAt({15, 15, 15}, {0, 0, 0}, {0, 0, 1});

    m_filamentView->setCamera(m_camera);

    // TODO Working orbit camera
    if (cameraMode == filament::camutils::Mode::ORBIT)
        m_cameraManipulator = std::unique_ptr<CameraManipulator>(
            CameraManipulator::Builder()
                .orbitHomePosition(15, 15, 15)
                .targetPosition(0, 0, 0)
                .upVector(0, 1, 0)
                .zoomSpeed(1.0)
                .build(cameraMode));
    else if (cameraMode == filament::camutils::Mode::FREE_FLIGHT)
        m_cameraManipulator = std::unique_ptr<CameraManipulator>(
            CameraManipulator::Builder()
                .flightStartPosition(15, 15, 15)
                .flightMoveDamping(15.0)
                .build(cameraMode));
    else
        assert(false &&
               "Camera manipulator not "
               "implemented.");

    m_renderableCreator = FilAppRenderableCreator::create(m_engine);

    setViewport(viewport);
}
FilAppView::~FilAppView()
{
    utils::EntityManager& entityManager = utils::EntityManager::get();
    clearFilAppRenderables();
    entityManager.destroy(m_cameraEntity);
    m_engine->destroyCameraComponent(m_cameraEntity);
    //    m_renderableCreator.destroyMaterials();
    m_engine->destroy(m_skybox);
    m_engine->destroy(m_filamentView);
    m_engine->destroy(m_scene);
}
void FilAppView::setViewport(const filament::Viewport& viewport)
{
    m_viewport = viewport;
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
Viewport FilAppView::getViewport() const
{
    return {m_viewport.left,
            m_viewport.bottom,
            m_viewport.width,
            m_viewport.height};
}
void FilAppView::configureOrthogonalProjection(float_t near,
                                               float_t far,
                                               float zoom)
{
    //    constexpr float ZOOM = 3.0f;
    const float aspect = (float)m_viewport.width / (float)m_viewport.height;
    m_camera->setProjection(filament::Camera::Projection::ORTHO,
                            -aspect * zoom,
                            aspect * zoom,
                            -zoom,
                            zoom,
                            near,
                            far);
}
RenderableIdentifier
FilAppView::addRenderable(TriangleRenderable&& triangleRenderable)
{
    auto renderable =
        std::make_unique<TriangleRenderable>(std::move(triangleRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::TRIANGLES,
        filament::Box{{0, 0, 0}, {10, 10, 10}}));

    m_triangleRenderables.emplace(id, std::move(renderable));

    return id;
}
RenderableIdentifier
FilAppView::addRenderable(PointRenderable&& pointRenderable)
{
    auto renderable =
        std::make_unique<PointRenderable>(std::move(pointRenderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable.get(),
        filament::Box{{0, 0, 0}, {10, 10, 10}}));

    m_pointRenderables.emplace(id, std::move(renderable));

    return id;
}
RenderableIdentifier FilAppView::addRenderable(LineRenderable&& lineREnderable)
{
    auto renderable =
        std::make_unique<LineRenderable>(std::move(lineREnderable));

    auto id = addRenderable(m_renderableCreator.createBakedColorRenderable(
        renderable->getVertices(),
        renderable->getIndices(),
        filament::RenderableManager::PrimitiveType::LINES,
        filament::Box{{0, 0, 0}, {10, 10, 10}}));

    m_lineRenderables.emplace(id, std::move(renderable));
    return id;
}
std::vector<RenderableIdentifier> FilAppView::getRenderableIdentifiers() const
{
    std::vector<RenderableIdentifier> result;
    for (const auto& filAppRenderable: m_renderables)
        result.push_back(filAppRenderable.renderableEntity.getId());
    return result;
}
void FilAppView::removeRenderable(RenderableIdentifier id)
{
    eraseFromMap(m_pointRenderables, id);
    eraseFromMap(m_lineRenderables, id);
    eraseFromMap(m_triangleRenderables, id);
    auto iter =
        std::remove_if(m_renderables.begin(),
                       m_renderables.end(),
                       [id = id, scene = m_scene](const FilAppRenderable& item)
                       {
                           if (item.renderableEntity.getId() == id)
                           {
                               scene->remove(item.renderableEntity);
                               item.destroy();
                               return true;
                           }
                           return false;
                       });
    m_renderables.erase(iter, m_renderables.end());
}
void FilAppView::clearRenderables()
{
    clearFilAppRenderables();
}
void FilAppView::setUsePostprocessing(bool usePostProcessing)
{
    m_filamentView->setPostProcessingEnabled(usePostProcessing);
}
void FilAppView::addRotationAnimation(RenderableIdentifier renderableIdentifier,
                                      const Vec3& rotationAxis)
{
    m_animationCallbacks.emplace_back(
        [renderableIdentifier,
         engine = m_engine,
         filamentView = m_filamentView](double deltaT)
        {
            auto& tcm = engine->getTransformManager();
            tcm.setTransform(tcm.getInstance(utils::Entity::import(
                                 static_cast<int>(renderableIdentifier))),
                             filament::math::mat4f::rotation(
                                 deltaT * 0.4,
                                 filament::math::float3{0, 1, 0}));
        });
}
void FilAppView::animate(double deltaT)
{
    for (const auto& animationCallBack: m_animationCallbacks)
        animationCallBack(deltaT);
}
void FilAppView::resize(const Viewport& viewport)
{
    setViewport(filament::Viewport(viewport.left,
                                   viewport.bottom,
                                   viewport.width,
                                   viewport.height));
}
void FilAppView::mouseDown(const MouseDownEvent& mouseDownEvent)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabBegin(static_cast<int>(mouseDownEvent.pos.x),
                                       static_cast<int>(mouseDownEvent.pos.y),
                                       mouseDownEvent.button == 3);
    for (auto listener: m_inputEventListener)
        listener->mouseDown(mouseDownEvent);
}
void FilAppView::mouseUp(const MouseUpEvent& mouseUpEvent)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabEnd();
    for (auto listener: m_inputEventListener)
        listener->mouseUp(mouseUpEvent);
}
void FilAppView::mouseMoved(const MouseMovedEvent& mouseMovedEvent)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabUpdate(
            static_cast<int>(mouseMovedEvent.pos.x),
            static_cast<int>(mouseMovedEvent.pos.y));
    for (auto listener: m_inputEventListener)
        listener->mouseMoved(mouseMovedEvent);
}
void FilAppView::mouseWheel(const MouseWheelEvent& mouseWheelEvent)
{
    if (m_cameraManipulator)
    {
        m_cameraManipulator->scroll(0, 0, mouseWheelEvent.x);
        m_orthogonalCameraZoom -= mouseWheelEvent.x * 0.1f;
        configureOrthogonalProjection(m_near, m_far, m_orthogonalCameraZoom);
    }

    for (auto listener: m_inputEventListener)
        listener->mouseWheel(mouseWheelEvent);
}
void FilAppView::keyDown(const KeyDownEvent& keyDownEvent)
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(keyDownEvent.sdlScancode, key))
            m_cameraManipulator->keyDown(key);
    }
    for (auto listener: m_inputEventListener)
        listener->keyDown(keyDownEvent);
}
void FilAppView::keyUp(const KeyUpEvent& keyUpEvent)
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(keyUpEvent.sdlScancode, key))
        {
            m_cameraManipulator->keyDown(key);
        }
    }
    for (auto listener: m_inputEventListener)
        listener->keyUp(keyUpEvent);
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
RenderableIdentifier
FilAppView::addRenderable(const FilAppRenderable& filAppRenderable)
{
    m_renderables.emplace_back(filAppRenderable);
    m_scene->addEntity(m_renderables.back().renderableEntity);
    return m_renderables.back().renderableEntity.getId();
}
void FilAppView::clearFilAppRenderables()
{
    for (auto& renderable: m_renderables)
    {
        m_scene->remove(renderable.renderableEntity);
        renderable.destroy();
    }
    m_renderables.clear();
}
} // namespace FilApp
