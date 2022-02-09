#include "FlowMesh/Interactors/SnapGeometries.hpp"
#include <Core/Math/Eps.hpp>
#include <Core/Utils/Assert.hpp>
#include <Geometry/Distance/DistanceRay.hpp>
#include <algorithm>
#include <limits>

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

void SnapGeometries::add(const LinAl::Vec3dVector& snapPoints)
{
    for (const LinAl::Vec3d& vec: snapPoints)
        add(vec);
}

void SnapGeometries::remove(const LinAl::Vec3d& snapPoint)
{
    auto eraseIter = std::remove(m_snapPoints.begin(), m_snapPoints.end(), snapPoint);
    m_snapPoints.erase(eraseIter, m_snapPoints.end());
}

void SnapGeometries::add(const Geometry::Segment3d& segment)
{
    for (const LinAl::Vec3d& vec: {segment.getSource(), segment.getTarget()})
        add(vec);
}

void SnapGeometries::add(const Geometry::Sphere<double_t>& sphere)
{
    LinAl::Vec3d origin = sphere.getOrigin();
    double_t radius = sphere.getRadius();
    for (const LinAl::Vec3d& vec: {origin + LinAl::Vec3d{1.0 * radius, 0.0, 0.0},
                                   origin + LinAl::Vec3d{0.0, 1.0 * radius, 0.0},
                                   origin + LinAl::Vec3d{0.0, 0.0, 1.0 * radius},
                                   origin + LinAl::Vec3d{-1.0 * radius, 0.0, 0.0},
                                   origin + LinAl::Vec3d{0.0, -1.0 * radius, 0.0},
                                   origin + LinAl::Vec3d{0.0, 0.0, -1.0 * radius}})
        add(vec);
}

std::optional<LinAl::Vec3d> SnapGeometries::calcSnapPoint(const Geometry::Ray3d& placementRay) const
{
    CORE_PRECONDITION_DEBUG_ASSERT(!Core::isZero(LinAl::norm2Squared(placementRay.getDirection())),
                                   "Direction with zero length is not allowed.");

    LinAl::Vec3dVector snapPoints;
    findSnapPoints(snapPoints, placementRay);
    if (snapPoints.empty())
        findSnapPlane(snapPoints, placementRay);
    return findClosestSnapPoint(snapPoints, placementRay);
}

void SnapGeometries::findSnapPoints(LinAl::Vec3dVector& snapPoints,
                                    const Geometry::Ray3d& placementRay) const
{
    for (const LinAl::Vec3d& vec: m_snapPoints)
        if (placementRay.distance(vec) < m_snapDistance)
            snapPoints.push_back(vec);
}

void SnapGeometries::findSnapPlane(LinAl::Vec3dVector& snapPoints,
                                   const Geometry::Ray3d& placementRay) const
{
    if (std::optional<LinAl::Vec3d> result = m_snapPlane.intersection(placementRay))
        snapPoints.push_back(result.value());
}

std::optional<LinAl::Vec3d>
SnapGeometries::findClosestSnapPoint(const LinAl::Vec3dVector& snapPoints,
                                     const Geometry::Ray3d& placementRay) const
{
    if (snapPoints.empty())
        return {};

    LinAl::Vec3d result;
    LinAl::Vec3d origin = placementRay.getOrigin();
    double_t dist{std::numeric_limits<double_t>::max()};
    for (const LinAl::Vec3d& vec: snapPoints)
    {
        double_t currentDist = LinAl::norm2Squared(LinAl::Vec3d{origin - vec});
        if (currentDist < dist)
        {
            result = vec;
            dist = currentDist;
        }
    }
    return result;
}

} // namespace FlowMesh