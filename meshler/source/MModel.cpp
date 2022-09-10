#include <Geometry/Transformation/TransformCone.hpp>
#include <Geometry/Transformation/TransformCuboid.hpp>
#include <Geometry/Transformation/TransformCylinder.hpp>
#include <Geometry/Transformation/TransformSegment.hpp>
#include <Geometry/Transformation/TransformSphere.hpp>
#include <Geometry/Transformation/TransformVec.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/GeometryElements/SnapGeometries.hpp>
#include <Meshler/MModel.hpp>
#include <Meshler/MPresenter.hpp>

namespace Meshler
{
MModel::MModel(MModelEventListener* modelEventListener)
{
    m_modelEventDispatcher.registerListener(modelEventListener);
}
void MModel::registerListener(MModelEventListener* modelEventListener)
{
    m_modelEventDispatcher.registerListener(modelEventListener);
}
void MModel::removeListener(MModelEventListener* modelEventListener)
{
    m_modelEventDispatcher.removeListener(modelEventListener);
}
void MModel::clearListeners()
{
    m_modelEventDispatcher.clearListeners();
}
void MModel::update(const FGuid& guid)
{
    // clang-format off
    if (auto elem = get<MCone>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<MCuboid>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<MCylinder>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<MGrid>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<MSegments>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    if (auto elem = get<MSphere>(guid)) m_modelEventDispatcher.dispatchUpdate(*elem);
    // clang-format on
    calcModelSnapGeometries();
}
void MModel::remove(FGuid fGuid)
{
    m_geometryElements.remove(fGuid);
    m_modelEventDispatcher.dispatchRemove(fGuid);
}
void MModel::setPosition(const FGuid& fGuid, LinAl::Vec3d& position)
{
    if (m_geometryElements.setPosition(fGuid, position))
        m_modelEventDispatcher.dispatchPositionChanged(PositionEvent{fGuid, position});
}

template <typename TGeomElemMap>
static void addTransFormedGeometryToSnapElements(SnapGeometries& snapGeometries,
                                                 const TGeomElemMap& geomElemMap)
{
    for (const auto& pair: geomElemMap)
    {
        if (pair.second.getIsSnapGeometry())
            snapGeometries.add(Geometry::transformation(pair.second.getGeometryElement(),
                                                        pair.second.getTransformation()));
    }
}

void MModel::calcModelSnapGeometries()
{
    SnapGeometries& result = m_geometryElements.getSnapGeometries();

    result = SnapGeometries{Geometry::Plane<double_t>{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D}};

    for (const auto& pair: m_geometryElements.getSegmentMap())
        if (pair.second.getIsSnapGeometry())
            for (const Geometry::Segment3d& segment: pair.second.getSegments())
                result.add(Geometry::transformation(segment, pair.second.getTransformation()));

    addTransFormedGeometryToSnapElements(result, m_geometryElements.getSphereMap());
    addTransFormedGeometryToSnapElements(result, m_geometryElements.getCylinderMap());
    addTransFormedGeometryToSnapElements(result, m_geometryElements.getConeMap());
    addTransFormedGeometryToSnapElements(result, m_geometryElements.getCuboidMap());

    for (const auto& pair: m_geometryElements.getGridMap())
    {
        if (!pair.second.getIsSnapGeometry())
            continue;

        auto trafo = pair.second.getTransformation();

        for (const Geometry::Segment3d& segment: pair.second.calcGridSegments())
            result.add(Geometry::transformation(segment, trafo));

        for (const LinAl::Vec3d& vec: pair.second.calcIntersectionPoints())
            result.add(Geometry::transformation(vec, trafo));
    }
}
} // namespace Meshler
