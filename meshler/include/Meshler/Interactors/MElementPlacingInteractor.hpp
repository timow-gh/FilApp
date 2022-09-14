#ifndef MESHLER_MELEMENTPLACINGINTERACTOR_HPP
#define MESHLER_MELEMENTPLACINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <Graphics/GraphicsController.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/InputEvents/PickRayEvent.hpp>
#include <Graphics/InputEvents/PickRayMoveEvent.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventListener.hpp>
#include <Meshler/GeometryElements/MGeometryTraits.hpp>
#include <Meshler/GeometryElements/SnapGeometries.hpp>
#include <Meshler/LinAlConversion.hpp>
#include <Meshler/MGuid.hpp>
#include <Meshler/MModel.hpp>
#include <Meshler/MModelEventListener.hpp>
#include <optional>

namespace Meshler
{

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
class MElementPlacingInteractor
    : public Graphics::GraphicsController
    , public MModelEventListener {
  MModel* m_model{nullptr};
  SnapGeometries m_snapGeometries;
  std::optional<FGuid> m_geometryGuid;
  TGeomConfig<T> m_geomConfig;

public:
  MElementPlacingInteractor(MModel& model, const TGeomConfig<T>& geomConfig);

  ~MElementPlacingInteractor() override { m_model->removeListener(this); }

private:
  CORE_NODISCARD std::optional<LinAl::Vec3d> calcIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

  using Graphics::GraphicsController::InputEventListener::onEvent;
  void onEvent(const Graphics::PickRayEvent& pickRayEvent) override;
  void onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;

  void onRemoveRayPickEventListener() override;

  void onModelPostAddEvent() override;
};

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
MElementPlacingInteractor<TMeshlerGeometry, T, TGeomConfig>::MElementPlacingInteractor(MModel& model, const TGeomConfig<T>& geomConfig)
    : m_model(&model)
    , m_geomConfig(geomConfig)
{
  m_model->registerListener(this);
  m_geomConfig.baseConfig.isSnapGeometry = false;
  auto geomElem = MGeometryTraits<TMeshlerGeometry, TGeomConfig, T>::create(m_geomConfig);
  m_geometryGuid = geomElem.getFGuid();
  m_model->add(std::move(geomElem));
  m_snapGeometries.add(m_model->getGeometryElements());
}

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
std::optional<LinAl::Vec3d>
MElementPlacingInteractor<TMeshlerGeometry, T, TGeomConfig>::calcIntersection(const Graphics::PickRayEvent& pickRayEvent) const
{
  return m_snapGeometries.calcSnapPoint(
      Geometry::Ray3<double_t>{vec3ToLinAlVec3<double_t>(pickRayEvent.origin), vec3ToLinAlVec3<double_t>(pickRayEvent.direction)});
}

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TMeshlerGeometry, T, TGeomConfig>::onEvent(const Graphics::PickRayEvent& pickRayEvent)
{
  auto intersection = calcIntersection(pickRayEvent);
  if (!intersection)
    return;

  m_model->updatePosition(*m_geometryGuid, *intersection);
  auto* geomElem = m_model->find<TMeshlerGeometry>(*m_geometryGuid);
  geomElem->setIsSnapGeometry(true);
  m_geometryGuid.reset();

  m_geomConfig.baseConfig.isSnapGeometry = false;
  TMeshlerGeometry nextMeshlerGeometry = MGeometryTraits<TMeshlerGeometry, TGeomConfig, T>::create(m_geomConfig);
  m_geometryGuid = nextMeshlerGeometry.getFGuid();
  m_model->add(std::move(nextMeshlerGeometry));
  m_model->updatePosition(*m_geometryGuid, *intersection);
}

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TMeshlerGeometry, T, TGeomConfig>::onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent)
{
  auto intersection = calcIntersection(pickRayMoveEvent);
  if (!intersection)
    return;

  m_model->updatePosition(*m_geometryGuid, *intersection);
}

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TMeshlerGeometry, T, TGeomConfig>::onRemoveRayPickEventListener()
{
  if (m_geometryGuid)
    m_model->remove(*m_geometryGuid);
}

template <typename TMeshlerGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TMeshlerGeometry, T, TGeomConfig>::onModelPostAddEvent()
{
  m_snapGeometries = SnapGeometries();
  m_snapGeometries.add(m_model->getGeometryElements());
}

} // namespace Meshler

#endif // MESHLER_MELEMENTPLACINGINTERACTOR_HPP
