#ifndef FILAPP_PLACINGINTERACTOR_HPP
#define FILAPP_PLACINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/SnapGeometries.hpp>
#include <FlowMesh/Model.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/PickRayEvent.hpp>
#include <GraphicsInterface/InputEvents/PickRayMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>
#include <optional>

namespace FlowMesh
{

class PlacingInteractor
    : public Interactor
    , public Graphics::RayPickEventListener {
    Model* m_model;
    SnapGeometries m_snapGeometries;
    std::optional<FGuid> m_sphereGuid;

  public:
    explicit PlacingInteractor(Model* model);
    ~PlacingInteractor() override;

  private:
    CORE_NODISCARD static FlowMeshSphere createSphere(const LinAl::Vec3d& origin);

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

    void event(const Graphics::PickRayEvent& pickRayEvent) override;
    void event(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;
};

} // namespace FlowMesh

#endif // FILAPP_PLACINGINTERACTOR_HPP
