#ifndef GRAPHICS_VIEW_HPP
#define GRAPHICS_VIEW_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Graphics/InputEvents/InputEventDispatcher.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/Viewport.hpp>

namespace Graphics
{

class InputEventDispatcher;
class RayPickEventDispatcher;
class TriangleRenderable;
class PointRenderable;
class LineRenderable;
class RenderableId;
struct Vec3;
class Gui;

class View : public InputEventListener {
public:
  View(const View& view) = delete;

  ~View() override;

  CORE_NODISCARD virtual InputEventDispatcher& getInputEventDispatcher() = 0;
  CORE_NODISCARD virtual RayPickEventDispatcher& getRayPickEventDispatcher() = 0;

  // clang-format off
  virtual auto addRenderable(TriangleRenderable&& renderable) -> RenderableId = 0;
  virtual auto addRenderable(PointRenderable&& renderable) -> RenderableId = 0;
  virtual auto addRenderable(LineRenderable&& renderable) -> RenderableId = 0;
  CORE_NODISCARD virtual auto getRenderableIdentifiers() const -> Core::TVector<RenderableId> = 0;
  virtual void removeRenderable(RenderableId renderableId) = 0;
  virtual void updatePosition(RenderableId renderableId, const Vec3& position) = 0;
  virtual void clearRenderables() = 0;
  // clang-format on

  // Animation prototype
  virtual void addRotationAnimation(RenderableId renderableIdentifier, const Vec3& rotationAxis) = 0;
  virtual void animate(double deltaT) = 0;

  CORE_NODISCARD virtual Viewport getViewport() const = 0;
  virtual void setViewport(const Viewport& viewport) = 0;

  void virtual render(double_t timeStepInSeconds) = 0;

protected:
  View() = default;
};
} // namespace Graphics

#endif // GRAPHICS_VIEW_HPP
