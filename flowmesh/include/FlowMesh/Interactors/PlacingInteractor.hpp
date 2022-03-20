#ifndef FILAPP_PLACINGINTERACTOR_HPP
#define FILAPP_PLACINGINTERACTOR_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Assert.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGeometryTraits.hpp>
#include <FlowMesh/Interactors/Interactor.hpp>
#include <FlowMesh/Interactors/SnapGeometries.hpp>
#include <FlowMesh/Model.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <GraphicsInterface/InputEvents/InputEventListener.hpp>
#include <GraphicsInterface/InputEvents/PickRayEvent.hpp>
#include <GraphicsInterface/InputEvents/PickRayMoveEvent.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventDispatcher.hpp>
#include <GraphicsInterface/InputEvents/RayPickEventListener.hpp>
#include <optional>

namespace FlowMesh
{

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
class PlacingInteractor
    : public Interactor
    , public Graphics::RayPickEventListener {
    Model* m_model{nullptr};
    SnapGeometries m_snapGeometries;
    std::optional<FGuid> m_geometryGuid;
    TGeomConfig<T> m_geomConfig;
    Graphics::RayPickEventDispatcher* m_rayPickEventDispatcher{nullptr};

  public:
    PlacingInteractor(Model* model,
                      SnapGeometries snapGeometries,
                      const TGeomConfig<T>& m_geomConfig,
                      Graphics::RayPickEventDispatcher* rayPickEventDispatcher);

    void initListeners() override;

    PlacingInteractor(const PlacingInteractor& rhs) = delete;
    PlacingInteractor& operator=(const PlacingInteractor& rhs) = delete;
    PlacingInteractor(PlacingInteractor&& rhs) noexcept = default;
    PlacingInteractor& operator=(PlacingInteractor&& rhs) = default;

    ~PlacingInteractor() override
    {
        if (m_geometryGuid)
            m_model->remove(*m_geometryGuid);
        if (m_rayPickEventDispatcher)
            m_rayPickEventDispatcher->removeListener(this);
    }

  private:
    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcIntersection(const Graphics::PickRayEvent& pickRayEvent) const;

    void event(const Graphics::PickRayEvent& pickRayEvent) override;
    void event(const Graphics::PickRayMoveEvent& pickRayMoveEvent) override;
};

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
PlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::PlacingInteractor(
    Model* model,
    SnapGeometries snapGeometries,
    const TGeomConfig<T>& geomConfig,
    Graphics::RayPickEventDispatcher* rayPickEventDispatcher)
    : m_model(model)
    , m_snapGeometries(std::move(snapGeometries))
    , m_geomConfig(geomConfig)
    , m_rayPickEventDispatcher(rayPickEventDispatcher)
{
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
void PlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::initListeners()
{
    m_rayPickEventDispatcher->registerListener(
        dynamic_cast<PlacingInteractor<TFlowMeshGeometry, double_t, TGeomConfig>*>(this));
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
std::optional<LinAl::Vec3d> PlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::calcIntersection(
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
void PlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::event(
    const Graphics::PickRayEvent& pickRayEvent)
{
    auto intersection = calcIntersection(pickRayEvent);
    if (!intersection)
        return;

    m_model->setPosition(*m_geometryGuid, *intersection);
    m_geometryGuid.reset();

    m_snapGeometries = m_model->calcModelSnapGeometries();

    TFlowMeshGeometry nextFlowMeshGeometry =
        FlowMeshGeometryTraits<TFlowMeshGeometry, TGeomConfig<T>>::create(m_geomConfig);
    m_model->add(nextFlowMeshGeometry);
    m_geometryGuid = nextFlowMeshGeometry.getFGuid();
    m_model->setPosition(*m_geometryGuid, *intersection);
}

template <typename TFlowMeshGeometry, typename T, template <typename> typename TGeomConfig>
void PlacingInteractor<TFlowMeshGeometry, T, TGeomConfig>::event(
    const Graphics::PickRayMoveEvent& pickRayMoveEvent)
{
    auto intersection = calcIntersection(pickRayMoveEvent);
    if (!intersection)
        return;

    if (!m_geometryGuid)
    {
        auto geomElem =
            FlowMeshGeometryTraits<TFlowMeshGeometry, TGeomConfig<T>>::create(m_geomConfig);
        m_geometryGuid = geomElem.getFGuid();
        m_model->add(geomElem);
    }

    m_model->setPosition(*m_geometryGuid, *intersection);
}

} // namespace FlowMesh

#endif // FILAPP_PLACINGINTERACTOR_HPP
