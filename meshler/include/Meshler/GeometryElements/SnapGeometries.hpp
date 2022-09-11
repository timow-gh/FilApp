#ifndef MESHLER_SNAPGEOMETRIES_HPP
#define MESHLER_SNAPGEOMETRIES_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Geometry/Fwd/FwdCircle.hpp>
#include <Geometry/Fwd/FwdCone.hpp>
#include <Geometry/Fwd/FwdCuboid.hpp>
#include <Geometry/Fwd/FwdCylinder.hpp>
#include <Geometry/Fwd/FwdRay.hpp>
#include <Geometry/Fwd/FwdSegment.hpp>
#include <Geometry/Fwd/FwdSphere.hpp>
#include <Geometry/Plane.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <optional>

namespace Meshler
{
class MSphere;
class GeometryElements;

class SnapGeometries {
    Geometry::Plane<double_t> m_snapPlane;
    LinAl::Vec3dVector m_snapPoints;
    Core::TVector<Geometry::Sphere<double_t>> m_snapSpheres;
    double_t m_snapDistance{0.3};

  public:
    SnapGeometries();
    explicit SnapGeometries(const Geometry::Plane<double_t>& snapPlane);

    void add(const LinAl::Vec3d& snapPoint);
    void add(const LinAl::Vec3dVector& snapPoints);
    void add(const Geometry::Segment3d& segment);
    void add(const Geometry::Circle3d& circle);
    void add(const Geometry::Sphere<double_t>& sphere);
    void add(const Geometry::Cylinder<double_t>& cylinder);
    void add(const Geometry::Cone<double_t>& cone);
    void add(const Geometry::Cuboid<double_t>& cuboid);

    void add(const MSphere& sphere);
    void add(const GeometryElements& geometryElements);

    void remove(const LinAl::Vec3d& snapPoint);

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcSnapPoint(const Geometry::Ray3d& placementRay) const;

  private:
    bool findSnapPoints(LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay) const;
    void findSnapPlane(LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay) const;

    CORE_NODISCARD static std::optional<LinAl::Vec3d>
    findClosestSnapPoint(const LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay);

    void addSphereSurfaceSnapPoint(LinAl::Vec3dVector& m_snapPoints,
                                   const Geometry::Ray3d& placementRay) const;
};

} // namespace Meshler

#endif // MESHLER_SNAPGEOMETRIES_HPP
