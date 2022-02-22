#ifndef FILAPP_SNAPGEOMETRIES_HPP
#define FILAPP_SNAPGEOMETRIES_HPP

#include <Core/Types/TVector.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Geometry/Cone.hpp>
#include <Geometry/Plane.hpp>
#include <Geometry/Ray.hpp>
#include <Geometry/Segment.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

class SnapGeometries {
    Geometry::Plane<double_t> m_snapPlane;
    LinAl::Vec3dVector m_snapPoints;
    double_t m_snapDistance{0.1};

  public:
    explicit SnapGeometries(const Geometry::Plane<double_t>& snapPlane);

    void add(const LinAl::Vec3d& snapPoint);
    void add(const LinAl::Vec3dVector& snapPoints);
    void remove(const LinAl::Vec3d& snapPoint);

    void add(const Geometry::Segment3d& segment);
    void add(const Geometry::Sphere<double_t>& sphere);

    CORE_NODISCARD std::optional<LinAl::Vec3d>
    calcSnapPoint(const Geometry::Ray3d& placementRay) const;

  private:
    void findSnapPoints(LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay) const;
    void findSnapPlane(LinAl::Vec3dVector& snapPoints, const Geometry::Ray3d& placementRay) const;
    CORE_NODISCARD std::optional<LinAl::Vec3d>
    findClosestSnapPoint(const LinAl::Vec3dVector& snapPoints,
                         const Geometry::Ray3d& placementRay) const;
};

} // namespace FlowMesh

#endif // FILAPP_SNAPGEOMETRIES_HPP
