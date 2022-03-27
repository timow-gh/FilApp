#include <Core/Math/Eps.hpp>
#include <Core/Utils/Assert.hpp>
#include <FlowMesh/Interactors/SnapGeometries.hpp>
#include <Geometry/Distance/DistanceRay.hpp>
#include <Geometry/GeometryAssert.hpp>
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

void SnapGeometries::add(const Geometry::Circle3d& circle)
{
    double_t radius = circle.getRadius();
    LinAl::HMatrixd transformation = circle.calcTransformation();
    for (const LinAl::HVecd& vec: {LinAl::HVecd{radius, 0.0, 0.0, 1.0},
                                   LinAl::HVecd{0.0, radius, 0.0, 1.0},
                                   LinAl::HVecd{-1.0 * radius, 0.0, 0.0, 1.0},
                                   LinAl::HVecd{0.0, -1.0 * radius, 0.0, 1.0}})
        add(LinAl::hVecToVec3(LinAl::HVecd{transformation * vec}));
}

void SnapGeometries::add(const Geometry::Sphere<double_t>& sphere,
                         const LinAl::HMatrixd& transformation)
{
    double_t radius = sphere.getRadius();
    add(Geometry::transformation(Geometry::Circle3d{sphere.getOrigin(), radius, LinAl::Z_VEC3D},
                                 transformation));
    for (const LinAl::HVecd& hVec:
         {LinAl::HVecd{0.0, 0.0, 1.0 * radius, 1.0}, LinAl::HVecd{0.0, 0.0, -1.0 * radius, 1.0}})
    {
        LinAl::HVecd transformedVec = transformation * hVec;
        transformedVec += LinAl::vec3ToHVec(sphere.getOrigin());
        add(LinAl::hVecToVec3(transformedVec));
    }
}

void SnapGeometries::add(const Geometry::Cylinder<double_t>& cylinder)
{
    const Geometry::Segment3d& seg = cylinder.getSegment();
    double_t radius = cylinder.getRadius();
    LinAl::Vec3d segDir = cylinder.getSegment().direction();

    add(seg);
    add(Geometry::Circle3d{seg.getSource(), radius, segDir});
    add(Geometry::Circle3d{seg.getTarget(), radius, segDir});
}

void SnapGeometries::add(const Geometry::Cone<double_t>& cone)
{
    const Geometry::Segment3d& seg = cone.getSegment();
    add(seg);
    add(Geometry::Circle3d{seg.getSource(), cone.getRadius(), seg.direction()});
}

std::optional<LinAl::Vec3d> SnapGeometries::calcSnapPoint(const Geometry::Ray3d& placementRay) const
{
    GEOMETRY_PRECONDITION_RAY_DIRECTION_DEBUG_ASSERT(placementRay);

    LinAl::Vec3dVector snapPoints;
    findSnapPoints(snapPoints, placementRay);
    if (snapPoints.empty())
        findSnapPlane(snapPoints, placementRay);
    return findClosestSnapPoint(snapPoints, placementRay);
}

void SnapGeometries::findSnapPoints(LinAl::Vec3dVector& snapPoints,
                                    const Geometry::Ray3d& placementRay) const
{
    GEOMETRY_PRECONDITION_RAY_DIRECTION_DEBUG_ASSERT(placementRay);

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