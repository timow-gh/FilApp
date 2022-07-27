#ifndef MESHLER_MGRIDINTERACTOR_HPP
#define MESHLER_MGRIDINTERACTOR_HPP

#include <Geometry/Plane.hpp>
#include <Graphics/InputEvents/RayPickEventListener.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>

namespace Meshler
{

class MModel;

class MGridInteractor : public Graphics::RayPickEventListener {
    MModel* m_model{nullptr};
    double_t m_updateDistance{6.0};
    double_t m_diffUpdateDistance{2.0};
    Geometry::Plane<double_t> m_plane;
    MGrid m_minimalGrid{};
    LinAl::Vec3d m_pevGridIntersectionPoint{0, 0, 0};
    FGuid m_activeGridGuid;

  public:
    MGridInteractor(MModel& model, Geometry::Plane<double_t> plane, const FGuid& fGuid);

  private:
    CORE_NODISCARD std::optional<LinAl::Vec3d>
    rayIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

    void onEvent(const Graphics::PickRayEvent& pickRayEvent) override;
    void onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;
};

} // namespace Meshler

#endif // MESHLER_MGRIDINTERACTOR_HPP
