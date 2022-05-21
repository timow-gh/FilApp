#include <Core/Math/Eps.hpp>
#include <Core/Utils/Assert.hpp>
#include <Geometry/Distance/DistanceRay.hpp>
#include <Geometry/GeometryAssert.hpp>
#include <Geometry/Intersection/IntersectionSphere.hpp>
#include <Geometry/Transformation/TransformSphere.hpp>
#include <Meshler/Interactors/SnapGeometries.hpp>
#include <algorithm>
#include <limits>

namespace Meshler
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

void SnapGeometries::add(const Geometry::Sphere<double_t>& sphere)
{
    m_snapSpheres.push_back(sphere);

    double_t radius = sphere.getRadius();
    LinAl::Vec3d origin = sphere.getOrigin();
    add(Geometry::Circle3d{origin, radius, LinAl::Z_VEC3D});
    for (const LinAl::Vec3d& vec:
         {LinAl::Vec3d{0.0, 0.0, 1.0 * radius}, LinAl::Vec3d{0.0, 0.0, -1.0 * radius}})
        add(origin + vec);
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

void SnapGeometries::add(const Geometry::Cuboid<double_t>& cuboid)
{
    for (const LinAl::Vec3d& cuboidVertex: Geometry::calcCuboidVertices(cuboid))
        add(cuboidVertex);
}

void SnapGeometries::remove(const LinAl::Vec3d& snapPoint)
{
    auto eraseIter = std::remove(m_snapPoints.begin(), m_snapPoints.end(), snapPoint);
    m_snapPoints.erase(eraseIter, m_snapPoints.end());
}

std::optional<LinAl::Vec3d> SnapGeometries::calcSnapPoint(const Geometry::Ray3d& placementRay) const
{
    GEOMETRY_PRECONDITION_RAY_DIRECTION_DEBUG_ASSERT(placementRay);

    LinAl::Vec3dVector snapPoints;
    if (!findSnapPoints(snapPoints, placementRay))
        addSphereSurfaceSnapPoint(snapPoints, placementRay);

    if (snapPoints.empty())
        findSnapPlane(snapPoints, placementRay);
    return findClosestSnapPoint(snapPoints, placementRay);
}

bool SnapGeometries::findSnapPoints(LinAl::Vec3dVector& snapPoints,
                                    const Geometry::Ray3d& placementRay) const
{
    GEOMETRY_PRECONDITION_RAY_DIRECTION_DEBUG_ASSERT(placementRay);
    std::size_t size = snapPoints.size();
    for (const LinAl::Vec3d& vec: m_snapPoints)
        if (placementRay.distance(vec) < m_snapDistance)
            snapPoints.push_back(vec);

    if (snapPoints.empty())
        return false;
    return snapPoints.size() == size;
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

void SnapGeometries::addSphereSurfaceSnapPoint(LinAl::Vec3dVector& snapPoints,
                                               const Geometry::Ray3d& placementRay) const
{
    for (const Geometry::Sphere<double_t>& sphere: m_snapSpheres)
    {
        Geometry::SphereIntersection<double_t> intersection =
            Geometry::calcIntersection(sphere, placementRay);
        if (intersection.first)
            snapPoints.push_back(*intersection.first);
        if (intersection.second)
            snapPoints.push_back(*intersection.second);
    }
}

void SnapGeometries::add(const MSphere& meshlerSphere)
{
    const auto& sphere = meshlerSphere.getGeometryElement();
    const auto& trafo = meshlerSphere.getTransformation();

    auto transformedSphere = Geometry::transformation(sphere, trafo);
    m_snapSpheres.push_back(transformedSphere);

    double_t radius = transformedSphere.getRadius();
    const auto& transformedOrigin = transformedSphere.getOrigin();
    LinAl::Vec3d transformedZVec = Geometry::transformation(LinAl::Z_VEC3D, trafo);
    add(Geometry::Circle3d{transformedOrigin, radius, transformedZVec});
    add(LinAl::Vec3d{transformedZVec * radius});
    add(LinAl::Vec3d{-transformedZVec * radius});
}

} // namespace Meshler