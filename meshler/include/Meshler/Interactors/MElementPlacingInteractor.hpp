#ifndef MESHLER_MELEMENTPLACINGINTERACTOR_HPP
#define MESHLER_MELEMENTPLACINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <Meshler/MGuid.hpp>
#include <Meshler/MModel.hpp>
#include <Meshler/GeometryElements/MGeometryTraits.hpp>
#include <Meshler/Interactors/SnapGeometries.hpp>
#include <Meshler/MModelEventListener.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <Graphics/GraphicsController.hpp>
#include <Graphics/InputEvents/InputEventListener.hpp>
#include <Graphics/InputEvents/PickRayEvent.hpp>
#include <Graphics/InputEvents/PickRayMoveEvent.hpp>
#include <Graphics/InputEvents/RayPickEventDispatcher.hpp>
#include <Graphics/InputEvents/RayPickEventListener.hpp>
#include <optional>

namespace FlowMesh
{

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
class MElementPlacingInteractor
    : public Graphics::GraphicsController
    , public MModelEventListener {
    MModel* m_model{nullptr};
    SnapGeometries m_snapGeometries;
    std::optional<FGuid> m_geometryGuid;
    TGeomConfig<T> m_geomConfig;

  public:
    MElementPlacingInteractor(MModel& model, const TGeomConfig<T>& m_geomConfig);

    ~MElementPlacingInteractor() override { m_model->removeListener(this); }

  private:
    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

    void onEvent(const Graphics::PickRayEvent& pickRayEvent) override;
    void onEvent(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;

    void onRemoveRayPickEventListener() override;

    void onModelPostAddEvent() override;
};

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
MElementPlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::MElementPlacingInteractor(
    MModel& model,
    const TGeomConfig<T>& geomConfig)
    : m_model(&model), m_snapGeometries(model.calcModelSnapGeometries()), m_geomConfig(geomConfig)
{
    m_model->registerListener(this);
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
std::optional<LinAl::Vec3d>
MElementPlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::calcIntersection(
    const Graphics::PickRayEvent& pickRayEvent) const
{
    const Graphics::Vec3& pickOrigin = pickRayEvent.origin;
    const Graphics::Vec3& pickDirection = pickRayEvent.direction;
    const Geometry::Ray3<double_t> ray{
        LinAl::Vec3d{pickOrigin[0], pickOrigin[1], pickOrigin[2]},
        LinAl::Vec3d{pickDirection[0], pickDirection[1], pickDirection[2]}};
    return m_snapGeometries.calcSnapPoint(ray);
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::onEvent(
    const Graphics::PickRayEvent& pickRayEvent)
{
    auto intersection = calcIntersection(pickRayEvent);
    if (!intersection)
        return;

    m_model->setPosition(*m_geometryGuid, *intersection);
    auto* geomElem = m_model->get<TFlowMeshGeometry>(*m_geometryGuid);
    geomElem->setIsSnapGeometry(true);
    m_geometryGuid.reset();

    m_snapGeometries = m_model->calcModelSnapGeometries();

    m_geomConfig.baseConfig.isSnapGeometry = false;
    TFlowMeshGeometry nextFlowMeshGeometry =
        MGeometryTraits<TFlowMeshGeometry, TGeomConfig, T>::create(m_geomConfig);
    m_model->add(nextFlowMeshGeometry);
    m_geometryGuid = nextFlowMeshGeometry.getFGuid();
    m_model->setPosition(*m_geometryGuid, *intersection);
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::onEvent(
    const Graphics::PickRayMoveEvent& pickRayMoveEvent)
{
    auto intersection = calcIntersection(pickRayMoveEvent);
    if (!intersection)
        return;

    if (!m_geometryGuid)
    {
        m_geomConfig.baseConfig.isSnapGeometry = false;
        auto geomElem = MGeometryTraits<TFlowMeshGeometry, TGeomConfig, T>::create(m_geomConfig);
        m_geometryGuid = geomElem.getFGuid();
        m_model->add(geomElem);
    }

    m_model->setPosition(*m_geometryGuid, *intersection);
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::onRemoveRayPickEventListener()
{
    if (m_geometryGuid)
        m_model->remove(*m_geometryGuid);
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
void MElementPlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::onModelPostAddEvent()
{
    m_snapGeometries = m_model->calcModelSnapGeometries();
}

} // namespace FlowMesh

#endif // MESHLER_MELEMENTPLACINGINTERACTOR_HPP
