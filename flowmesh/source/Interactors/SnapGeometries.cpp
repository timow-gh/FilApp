#include "FlowMesh/Interactors/SnapGeometries.hpp"
#include <Core/Math/Eps.hpp>
#include <Core/Utils/Assert.hpp>
#include <Geometry/Distance/DistanceRay.hpp>
#include <algorithm>

namespace FlowMesh
{
SnapGeometries::SnapGeometries(const Geometry::Plane<double_t>& snapPlane) : m_snapPlane(snapPlane)
{
    CORE_PRECONDITION_DEBUG_ASSERT(!Core::isZero(LinAl::norm2Squared(m_snapPlane.getNormal())),
                                   "Direction with zero length is not allowed.");
}

void SnapGeometries::add(const LinAl::Vec3d& snapPoint)
{
    m_snapPoints.push_back(snapPoint);
}

void SnapGeometries::remove(const LinAl::Vec3d& snapPoint)
{
    auto eraseIter = std::remove(m_snapPoints.begin(), m_snapPoints.end(), snapPoint);
    m_snapPoints.erase(eraseIter, m_snapPoints.end());
}

void SnapGeometries::add(const LinAl::Vec3dVector& snapPoints)
{
    for (const LinAl::Vec3d& vec: snapPoints)
        add(vec);
}

LinAl::Vec3d SnapGeometries::calcSnapPoint(const Geometry::Ray3d& placementRay) const
{
    CORE_PRECONDITION_DEBUG_ASSERT(!Core::isZero(LinAl::norm2Squared(placementRay.getDirection())),
                                   "Direction with zero length is not allowed.");

    LinAl::Vec3d snapPoint;
    if (findSnapPoint(snapPoint, placementRay))
    {
        return snapPoint;
    }
    else if (findSnapPlane(snapPoint, placementRay))
    {
        return snapPoint;
    }
    else
    {
        CORE_POSTCONDITION_ASSERT(false, "No snapPoint found.");
        return LinAl::Vec3d{};
    }
}

bool SnapGeometries::findSnapPoint(LinAl::Vec3d& snapPoint, Geometry::Ray3d placementRay) const
{
    if (m_snapPoints.empty())
        return false;

    for (const LinAl::Vec3d& vec: m_snapPoints)
    {
        double_t dist = placementRay.distance(vec);
        if (dist < m_snapDistance)
        {
            snapPoint = vec;
            return true;
        }
    }

    return false;
}

bool SnapGeometries::findSnapPlane(LinAl::Vec3d& snapPoint, Geometry::Ray3d placementRay) const
{
    if (std::optional<LinAl::Vec3d> result = m_snapPlane.intersection(placementRay))
    {
        snapPoint = result.value();
        return true;
    }

    return false;
}

LinAl::Vec3dVector getSnapPoints(const Geometry::Segment3d& segment)
{
    return {segment.getSource(), segment.getTarget()};
}

LinAl::Vec3dVector getSnapPoints(const Geometry::Sphere<double_t>& sphere)
{
    LinAl::Vec3d origin = sphere.getOrigin();
    double_t radius = sphere.getRadius();
    return {origin + LinAl::Vec3d{1.0 * radius, 0.0, 0.0},
            origin + LinAl::Vec3d{0.0, 1.0 * radius, 0.0},
            origin + LinAl::Vec3d{0.0, 0.0, 1.0 * radius},
            origin + LinAl::Vec3d{-1.0 * radius, 0.0, 0.0},
            origin + LinAl::Vec3d{0.0, -1.0 * radius, 0.0},
            origin + LinAl::Vec3d{0.0, 0.0, -1.0 * radius}};
}

} // namespace FlowMesh