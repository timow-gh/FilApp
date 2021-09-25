#include "FilApp/FilAppView.hpp"
#include "SDL_timer.h"
#include <filament/TransformManager.h>

namespace FilApp
{
FilAppView::FilAppView(filament::Renderer& renderer,
                       const std::string& name,
                       const filament::Viewport& viewport,
                       filament::math::float4 skyBoxDefaultColor,
                       filament::camutils::Mode cameraMode)
    : m_engine(renderer.getEngine()), m_name(name)
{
    m_filamentView = m_engine->createView();
    m_filamentView->setName(m_name.c_str());

    m_scene = m_engine->createScene();
    m_filamentView->setScene(m_scene);

    m_skybox =
        filament::Skybox::Builder().color(skyBoxDefaultColor).build(*m_engine);
    m_scene->setSkybox(m_skybox);

    utils::EntityManager& entityManager = utils::EntityManager::get();
    m_cameraEntity = entityManager.create();
    m_camera = m_engine->createCamera(m_cameraEntity);
    m_camera->setExposure(16.0f, 1 / 125.0f, 100.0f);
    m_camera->lookAt({5, 5, 5}, {0, 0, 0}, {0, 0, 1});
    //    m_camera->lookAt({0, 0, 0}, {0, 0, -4});

    m_filamentView->setCamera(m_camera);

    // TODO Working orbit camera
    if (cameraMode == filament::camutils::Mode::ORBIT)
        m_cameraManipulator =
            std::unique_ptr<CameraManipulator>(CameraManipulator::Builder()
                                                   .orbitHomePosition(5, 5, 5)
                                                   .targetPosition(0, 0, 0)
                                                   .upVector(0, 1, 0)
                                                   .build(cameraMode));
    else if (cameraMode == filament::camutils::Mode::FREE_FLIGHT)
        m_cameraManipulator =
            std::unique_ptr<CameraManipulator>(CameraManipulator::Builder()
                                                   .flightStartPosition(5, 5, 5)
                                                   .flightMoveDamping(15.0)
                                                   .build(cameraMode));
    else
        assert(false &&
               "Camera manipulator not "
               "implemented.");

    setViewport(viewport);
}
FilAppView::~FilAppView()
{
    utils::EntityManager& entityManager = utils::EntityManager::get();
    entityManager.destroy(m_cameraEntity);
    m_engine->destroyCameraComponent(m_cameraEntity);
    m_engine->destroy(m_skybox);
    m_engine->destroy(m_filamentView);
    clearFilAppRenderables();
    m_engine->destroy(m_scene);
}
void FilAppView::setViewport(const filament::Viewport& viewport)
{
    m_viewport = viewport;
    m_filamentView->setViewport(m_viewport);
    configureCameraProjection();
    if (m_cameraManipulator)
        m_cameraManipulator->setViewport(viewport.width, viewport.height);
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
bool FilAppView::manipulatorKeyFromKeycode(
    SDL_Scancode scancode,
    filament::camutils::Manipulator<float_t>::Key& key) const
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
void FilAppView::configureCameraProjection()
{
    constexpr float ZOOM = 1.5f;
    const float aspect = (float)m_viewport.width / (float)m_viewport.height;
    m_camera->setProjection(filament::Camera::Projection::ORTHO,
                            -aspect * ZOOM,
                            aspect * ZOOM,
                            -ZOOM,
                            ZOOM,
                            0.1,
                            100);
}
RenderableIdentifier FilAppView::addRenderable(TriangleRenderable&& renderable)
{
    m_triangleRenderables.emplace_back(
        std::make_unique<TriangleRenderable>(std::move(renderable)));

    return addRenderable(
        createBakedColorRenderable(m_triangleRenderables.back().get(),
                                   filament::Box{{0, 0, 0}, {10, 10, 10}},
                                   m_engine));
}
RenderableIdentifier FilAppView::addRenderable(PointRenderable&& renderable)
{
    //    return addRenderable(
    //        createBakedColorRenderable(std::move(renderable),
    //                                   filament::Box{{0, 0, 0}, {10, 10, 10}},
    //                                   m_engine));
    return RenderableIdentifier();
}
std::vector<RenderableIdentifier> FilAppView::getRenderableIdentifiers() const
{
    assert(false);
    // TODO Implement
    return std::vector<RenderableIdentifier>();
}
void FilAppView::removeRenderable(RenderableIdentifier renderableIdentifier)
{
    assert(false);
    // TODO Implement
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
            tcm.setTransform(
                tcm.getInstance(utils::Entity::import(renderableIdentifier)),
                filament::math::mat4f::rotation(
                    deltaT,
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
        m_cameraManipulator->grabBegin(mouseDownEvent.pos.x,
                                       mouseDownEvent.pos.y,
                                       mouseDownEvent.button == 3);
}
void FilAppView::mouseUp(const MouseUpEvent& mouseUpEvent) const
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabEnd();
}
void FilAppView::mouseMoved(const MouseMovedEvent& mouseMovedEvent) const
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabUpdate(mouseMovedEvent.pos.x,
                                        mouseMovedEvent.pos.y);
}
void FilAppView::mouseWheel(const MouseWheelEvent& mouseWheelEvent) const
{
    if (m_cameraManipulator)
        m_cameraManipulator->scroll(0, 0, mouseWheelEvent.x);
}
void FilAppView::keyDown(const KeyDownEvent& keyDownEvent) const
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(keyDownEvent.sdlScancode, key))
            m_cameraManipulator->keyDown(key);
    }
}
void FilAppView::keyUp(const KeyUpEvent& keyUpEvent) const
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(keyUpEvent.sdlScancode, key))
        {
            m_cameraManipulator->keyDown(key);
        }
    }
}
RenderableIdentifier
FilAppView::addRenderable(FilAppRenderable&& filAppRenderable)
{
    m_renderables.emplace_back(std::move(filAppRenderable));
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
