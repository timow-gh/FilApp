#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppCameraView.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <Graphics/InputEvents/KeyEvent.hpp>
#include <Graphics/InputEvents/MouseButtonEvent.hpp>
#include <Graphics/InputEvents/MouseMoveEvent.hpp>
#include <Graphics/InputEvents/MouseWheelEvent.hpp>
#include <camutils/Bookmark.h>
#include <filament/Options.h>
#include <math/mat4.h>
#include <math/mathfwd.h>
#include <math/vec3.h>
#include <utility>

#ifndef NDEBUG
#define DEBUG_CHECK_CAMERA_MANIP() CORE_PRECONDITION_DEBUG_ASSERT(m_cameraManipulator, "Camera manipulator not set.");
#else
#define DEBUG_CHECK_CAMERA_MANIP()
#endif

using namespace Graphics;

namespace FilApp
{
FilAppCameraView::FilAppCameraView(const Graphics::ViewConfig& viewConfig, FilAppScene& filAppScene, filament::Renderer* renderer)
    : m_name(viewConfig.name)
    , m_renderer(renderer)
    , m_engine(renderer->getEngine())
    , m_filAppScene(filAppScene)
    , m_viewConfig(viewConfig)
{
  m_filamentView = m_engine->createView();
  m_filamentView->setName(m_name.c_str());

  if (viewConfig.useFXAA)
  {
    m_filamentView->setAntiAliasing(filament::AntiAliasing::FXAA);
  }

  m_filamentView->setScene(m_filAppScene.get().getFilamentScene());

  utils::EntityManager& entityManager = utils::EntityManager::get();
  m_cameraEntity = entityManager.create();
  m_camera = m_engine->createCamera(m_cameraEntity);

  const filament::math::float3 eye = toFilamentCS(viewConfig.eye);
  const filament::math::float3 center = toFilamentCS(viewConfig.center);
  const filament::math::float3 up = toFilamentCS(viewConfig.up);
  m_camera->lookAt(eye, center, up);
  m_filamentView->setCamera(m_camera);

  filament::camutils::Mode cameraMode = toFilamentCameraMode(viewConfig.cameraMode);
  if (cameraMode == filament::camutils::Mode::ORBIT)
    m_cameraManipulator =
        std::unique_ptr<CameraManipulator>(CameraManipulator::Builder()
                                               .fovDegrees(static_cast<float>(m_viewConfig.fieldOfViewInDegree))
                                               .fovDirection(toFilamentFovDirection(m_viewConfig.fovDirection, FilamentCamUtilsTag()))
                                               .farPlane(static_cast<float>(m_viewConfig.far))
                                               .orbitHomePosition(eye[0], eye[1], eye[2])
                                               .targetPosition(center[0], center[1], center[2])
                                               .upVector(up[0], up[1], up[2])
                                               .zoomSpeed(0.01f)
                                               .build(toFilamentCameraMode(m_viewConfig.cameraMode)));
  else
    CORE_POSTCONDITION_ASSERT(false, "Camera not implemented.");

  m_cameraHomeBookMark = m_cameraManipulator->getCurrentBookmark();

  setViewport(m_viewConfig.viewport);
}

FilAppCameraView::~FilAppCameraView()
{
  utils::EntityManager& entityManager = utils::EntityManager::get();
  entityManager.destroy(m_cameraEntity);
  m_engine->destroyCameraComponent(m_cameraEntity);
  m_engine->destroy(m_filamentView);
}

void FilAppCameraView::animate(double_t deltaT)
{
  for (const auto& animationCallBack: m_animationCallbacks)
    animationCallBack(deltaT);
}
void FilAppCameraView::render([[maybe_unused]] double_t timeStepInSeconds)
{
  CORE_PRECONDITION_DEBUG_ASSERT(m_renderer, "Renderer not set.");
  m_renderer->render(m_filamentView);
}
void FilAppCameraView::setFilAppScene(FilAppScene& filAppScene)
{
  m_filAppScene = filAppScene;
  m_filamentView->setScene(m_filAppScene.get().getFilamentScene());
}

filament::View* FilAppCameraView::getFilamentView()
{
  return m_filamentView;
}

filament::Camera* FilAppCameraView::getCamera()
{
  return m_camera;
}

FilAppCameraView::CameraManipulator* FilAppCameraView::getCameraManipulator()
{
  return m_cameraManipulator.get();
}

void FilAppCameraView::configureCameraProjection()
{
  CORE_PRECONDITION_DEBUG_ASSERT(m_viewConfig.near < m_viewConfig.far, "Invalid near and far plane.");
  const double_t aspect = static_cast<double_t>(m_filamentViewport.width) / static_cast<double_t>(m_filamentViewport.height);

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
    m_camera->setProjection(m_viewConfig.fieldOfViewInDegree,
                            aspect,
                            m_viewConfig.near,
                            m_viewConfig.far,
                            toFilamentFovDirection(m_viewConfig.fovDirection, FilamentCameraTag()));
    break;
  }
}

RayPickEventDispatcher& FilAppCameraView::getRayPickEventDispatcher()
{
  return m_rayPickEventDispatcher;
}

RenderableId FilAppCameraView::addRenderable(TriangleRenderable&& triangleRenderable)
{
  return m_filAppScene.get().add(std::move(triangleRenderable));
}

RenderableId FilAppCameraView::addRenderable(PointRenderable&& pointRenderable)
{
  return m_filAppScene.get().add(std::move(pointRenderable));
}

RenderableId FilAppCameraView::addRenderable(LineRenderable&& lineRenderable)
{
  return m_filAppScene.get().add(std::move(lineRenderable));
}

Core::TVector<RenderableId> FilAppCameraView::getRenderableIdentifiers() const
{
  return m_filAppScene.get().getRenderableIdentifiers();
}

void FilAppCameraView::removeRenderable(RenderableId id)
{
  // Synchronize the GPU with the CPU
  m_engine->flushAndWait();
  m_filAppScene.get().remove(id);
}

void FilAppCameraView::updatePosition(RenderableId renderableId, const Vec3& position)
{
  FilAppRenderable* renderable = m_filAppScene.get().findFilAppRenderable(renderableId);
  CORE_POSTCONDITION_DEBUG_ASSERT(renderable, "FilAppRenderable not found.");
  if (!renderable)
    return;
  renderable->updatePosition(vec3ToFloat3(position));
}

void FilAppCameraView::clearRenderables()
{
  m_engine->flushAndWait();
  m_filAppScene.get().clear();
}

void FilAppCameraView::addRotationAnimation(RenderableId renderableIdentifier, const Vec3& rotationAxis)
{
  m_animationCallbacks.emplace_back(
      [renderableIdentifier, engine = m_engine, rotationAxis](double_t deltaT)
      {
        auto& tcm = engine->getTransformManager();
        tcm.setTransform(tcm.getInstance(utils::Entity::import(static_cast<int>(renderableIdentifier.getId()))),
                         filament::math::mat4f::rotation(deltaT * 0.4, vec3ToFloat3(rotationAxis)));
      });
}

Viewport FilAppCameraView::getViewport() const
{
  return {static_cast<uint32_t>(m_filamentViewport.left),
          static_cast<uint32_t>(m_filamentViewport.bottom),
          m_filamentViewport.width,
          m_filamentViewport.height};
}

void FilAppCameraView::setCamera(filament::Camera* camera)
{
  CORE_PRECONDITION_DEBUG_ASSERT(camera, "Camera not set.");
  CORE_PRECONDITION_DEBUG_ASSERT(m_filamentView, "Filament view not set.");
  m_filamentView->setCamera(camera);
}

void FilAppCameraView::setViewport(const Viewport& viewport)
{
  CORE_PRECONDITION_DEBUG_ASSERT(m_filamentView, "Filament view not set.");
  DEBUG_CHECK_CAMERA_MANIP()

  m_viewConfig.viewport = viewport;
  m_filamentViewport = toFilamentViewport(viewport);
  m_filamentView->setViewport(m_filamentViewport);
  configureCameraProjection();
  m_filamentView->setCamera(m_camera);
  m_cameraManipulator->setViewport(static_cast<int>(viewport.width), static_cast<int>(viewport.height));
}

void FilAppCameraView::onEvent(const MouseButtonEvent& mouseButtonEvent)
{
  DEBUG_CHECK_CAMERA_MANIP()
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

    if (mouseButtonEvent.buttonIndex == 1)
      m_rayPickEventDispatcher.dispatch(getPickRayMoveEvent(mouseButtonEvent.x, mouseButtonEvent.y, mouseButtonEvent.deltaT));
    break;
  }
  case MouseButtonEvent::Type::REPEAT: CORE_PRECONDITION_DEBUG_ASSERT(false, "MouseButtonEvent::Type::REPEAT not implemented."); return;
  case MouseButtonEvent::Type::RELEASE:
  {
    m_cameraManipulator->grabEnd();
    break;
  }
  }
}

void FilAppCameraView::onEvent(const MouseMoveEvent& mouseMoveEvent)
{
  const int x = static_cast<int>(mouseMoveEvent.x);
  const int y = static_cast<int>(mouseMoveEvent.y);
  if (m_cameraManipulator)
  {
    m_cameraManipulator->grabUpdate(x, y);
    updateFilamentCamera();
  }

  PickRayEvent pickRayEvent = getPickRayMoveEvent(mouseMoveEvent.x, mouseMoveEvent.y, mouseMoveEvent.deltaT);
  m_rayPickEventDispatcher.dispatch(PickRayMoveEvent(pickRayEvent.origin, pickRayEvent.direction, pickRayEvent.time));
}

void FilAppCameraView::onEvent(const MouseWheelEvent& mouseWheelEvent)
{
  DEBUG_CHECK_CAMERA_MANIP()

  if (m_viewConfig.cameraProjection == ViewConfig::CameraProjection::ORTHOGRAPHIC)
  {
    m_viewConfig.orthogonalCameraZoom += static_cast<double_t>(mouseWheelEvent.x * m_viewConfig.scrollMultiplierOrthographic);
    configureCameraProjection();
  }
  else
  {
    float_t scrollValue = mouseWheelEvent.x * m_viewConfig.scrollMultiplierPerspective;
    m_cameraManipulator->scroll(0, 0, scrollValue);
    updateFilamentCamera();
  }
}

void FilAppCameraView::onEvent(const KeyEvent& keyEvent)
{
  DEBUG_CHECK_CAMERA_MANIP()
  CameraManipulator::Key key;
  if (manipulatorKeyFromKeycode(keyEvent.keyScancode, key))
    m_cameraManipulator->keyDown(key);

  if (keyEvent.keyScancode == Graphics::KeyScancode::SCANCODE_HOME || keyEvent.keyScancode == Graphics::KeyScancode::SCANCODE_H)
  {
    m_cameraManipulator->jumpToBookmark(m_cameraHomeBookMark);
  }
}

bool FilAppCameraView::manipulatorKeyFromKeycode(Graphics::KeyScancode scancode, filament::camutils::Manipulator<float_t>::Key& key)
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

PickRayEvent FilAppCameraView::getPickRayMoveEvent(std::size_t x, std::size_t y, double_t time) const
{
  const auto width = static_cast<float_t>(m_viewConfig.viewport.width);
  const auto height = static_cast<float_t>(m_viewConfig.viewport.height);

  // Viewport coordinates to normalized device coordinates
  const float_t u = 2.0f * (0.5f + static_cast<float>(x)) / width - 1.0f;
  const float_t v = 2.0f * (0.5f + static_cast<float>(y)) / height - 1.0f;

  const filament::math::float3 cameraForward = m_camera->getForwardVector();
  const filament::math::float3 right = normalize(cross(cameraForward, m_camera->getUpVector()));
  const filament::math::float3 upward = cross(right, cameraForward);
  const float_t aspect = width / height;
  const float_t fov = static_cast<float_t>(m_viewConfig.fieldOfViewInDegree) * filament::math::f::PI / 180.0f;

  filament::math::float3 origin = m_camera->getPosition();
  filament::math::float3 direction = cameraForward;
  if (m_viewConfig.cameraProjection == ViewConfig::CameraProjection::PERSPECTIVE)
  {
    const float_t tangent = std::tan(fov / 2.0f);
    if (toFilamentFovDirection(m_viewConfig.fovDirection, FilamentCameraTag()) == filament::Camera::Fov::VERTICAL)
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
    CORE_POSTCONDITION_DEBUG_ASSERT(false, "Picking for this camera projection not implemented.");

  direction = normalize(direction);
  return PickRayEvent{toGlobalCS(origin), toGlobalCS(direction), time};
}
void FilAppCameraView::updateFilamentCamera() const
{
  filament::math::float3 eye;
  filament::math::float3 target;
  filament::math::float3 up;
  m_cameraManipulator->getLookAt(&eye, &target, &up);
  m_camera->lookAt(eye, target, up);
}

} // namespace FilApp
