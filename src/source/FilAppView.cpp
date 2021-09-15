#include "FilApp/FilAppView.hpp"
#include "SDL_timer.h"

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
void FilAppView::setCameraManipulator(
    FilAppView::CameraManipulator* cameraManipulator)
{
    m_cameraManipulator.reset();
    m_cameraManipulator = std::unique_ptr<CameraManipulator>(cameraManipulator);
}
void FilAppView::mouseDown(int button, ssize_t x, ssize_t y)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabBegin(x, y, button == 3);
}
void FilAppView::mouseUp(ssize_t x, ssize_t y)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabEnd();
}
void FilAppView::mouseMoved(ssize_t x, ssize_t y)
{
    if (m_cameraManipulator)
        m_cameraManipulator->grabUpdate(x, y);
}
void FilAppView::mouseWheel(ssize_t x)
{
    if (m_cameraManipulator)
        m_cameraManipulator->scroll(0, 0, x);
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
const filament::Viewport& FilAppView::getViewport()
{
    return m_viewport;
}
void FilAppView::keyDown(SDL_Scancode scancode)
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(scancode, key))
            m_cameraManipulator->keyDown(key);
    }
}
void FilAppView::keyUp(SDL_Scancode scancode)
{
    if (m_cameraManipulator)
    {
        CameraManipulator::Key key;
        if (manipulatorKeyFromKeycode(scancode, key))
        {
            m_cameraManipulator->keyDown(key);
        }
    }
}
void FilAppView::resize(const filament::Viewport& viewport)
{
    setViewport(viewport);
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
IView::RenderableIdentifier
FilAppView::addRenderable(Renderable&& renderable)
{
    m_renderables.push_back(
        createBakedColorRenderable(std::move(renderable),
                                   filament::Box{{0, 0, 0}, {10, 10, 10}},
                                   m_engine));
    m_scene->addEntity(m_renderables.back().renderableEntity);
    return m_renderables.back().renderableEntity.getId();
}
std::vector<IView::RenderableIdentifier>
FilAppView::getRenderableIdentifiers() const
{
    // TODO Implement
    return std::vector<RenderableIdentifier>();
}
void FilAppView::removeRenderable(
    IView::RenderableIdentifier renderableIdentifier)
{
    // TODO Implement
}
void FilAppView::clearRenderables()
{
    clearFilAppRenderables();
}
void FilAppView::mouseDown(const MouseDownEvent& mouseDownEvent)
{
    // TODO Implement
}
void FilAppView::mouseUp(const MouseUpEvent& mouseUpEvent) const
{
    // TODO Implement
}
void FilAppView::mouseMoved(const MouseMovedEvent& mouseMovedEvent) const
{
    // TODO Implement
}
void FilAppView::mouseWheel(const MouseWheelEvent& mouseWheelEvent) const
{
    // TODO Implement
}
void FilAppView::keyDown(const KeyDownEvent& keyDownEvent) const
{
    // TODO Implement
}
void FilAppView::keyUp(const KeyUpEvent& keyUpEvent) const
{
    // TODO Implement
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
