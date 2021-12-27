#ifndef FILAPP_PLACINGINTERACTOR_HPP
#define FILAPP_PLACINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/FlowMeshModel.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/PickRayEvent.hpp>
#include <GraphicsInterface/InputEvents/PickRayMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>
#include <optional>

namespace FlowMesh
{
class PlacingInteractor : public Interactor {
    FlowMesh::FlowMeshModel* m_model;
    std::optional<FGuid> m_sphereGuid;

  public:
    explicit PlacingInteractor(FlowMeshModel* model) CORE_NOEXCEPT;
    void ~PlacingInteractor() CORE_NOEXCEPT;

  private:
    CORE_NODISCARD FlowMeshSphere
    createSphere(const LinAl::Vec3d& origin) const;

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

    void event(const Graphics::PickRayEvent& pickRayEvent) override;
    void event(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_PLACINGINTERACTOR_HPP
