#ifndef MESHLER_SNAPGEOMETRIES_HPP
#define MESHLER_SNAPGEOMETRIES_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Geometry/Circle.hpp>
#include <Geometry/Cone.hpp>
#include <Geometry/Cuboid.hpp>
#include <Geometry/Cylinder.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <Geometry/Segment.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>

namespace Meshler
{

class SnapGeometries {
    Geometry::Plane<double_t> m_snapPlane;
    LinAl::Vec3dVector m_snapPoints;
    Core::TVector<Geometry::Sphere<double_t>> m_snapSpheres;
    double_t m_snapDistance{0.3};

  public:
    explicit SnapGeometries(const Geometry::Plane<double_t>& snapPlane);

    void add(const LinAl::Vec3d& snapPoint);
    void add(const LinAl::Vec3dVector& snapPoints);
    void add(const Geometry::Segment3d& segment);
    void add(const Geometry::Circle3d& circle);
    void add(const Geometry::Sphere<double_t>& sphere);
    void add(const Geometry::Cylinder<double_t>& cylinder);
    void add(const Geometry::Cone<double_t>& cone);
    void add(const Geometry::Cuboid<double_t>& cuboid);

    void add(const MSphere& meshlerSphere);

    void remove(const LinAl::Vec3d& snapPoint);

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcSnapPoint(const Geometry::Ray3d& placementRay) const;

  private:
    bool findSnapPoints(LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay) const;
    void findSnapPlane(LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay) const;

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    findClosestSnapPoint(const LinAl::Vec3dVector& snapPoints,
                         const Geometry::Ray3d& placementRay) const;

    void addSphereSurfaceSnapPoint(LinAl::Vec3dVector& m_snapPoints,
                                   const Geometry::Ray3d& placementRay) const;
};

} // namespace Meshler

#endif // MESHLER_SNAPGEOMETRIES_HPP
