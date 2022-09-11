#ifndef MESHLER_MGRIDINTERACTOR_HPP
#define MESHLER_MGRIDINTERACTOR_HPP

#include <Geometry/Plane.hpp>
#include <Graphics/InputEvents/RayPickEventListener.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <functional>
#include <optional>

namespace Meshler
{

class MModel;

class MGridInteractor final : public Graphics::RayPickEventListener {
  double_t m_diffUpdateDistance{2.0};
  double_t m_updateTimeDelta{0.05};
  double_t m_lastUpdateTime{0};
  double_t m_updateDistMultiplier{4.0};
  std::reference_wrapper<MModel> m_model;
  MGrid m_gridCopy;
  FGuid m_activeGridGuid;
  Geometry::Plane<double_t> m_activeGridPlane;
  LinAl::Vec3d m_pevGridIntersectionPoint{0, 0, 0};

public:
  MGridInteractor(MModel& model, FGuid defaultGridGuid);

private:
  CORE_NODISCARD std::optional<LinAl::Vec3d> rayIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

  void onEvent(const Graphics::PickRayEvent& pickRayEvent) override;
  void onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;

  CORE_NODISCARD bool updatedLengths(LinAl::Vec3d intersectionVec, double_t& xMin, double_t& yMin, double_t& xMax, double_t& yMax);
};

} // namespace Meshler

#endif // MESHLER_MGRIDINTERACTOR_HPP
