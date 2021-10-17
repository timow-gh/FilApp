#ifndef FILAPP_FLOWMESHPOINT_HPP
#define FILAPP_FLOWMESHPOINT_HPP

#include <CrossGuid/Guid.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{
class FlowMeshPoint
{
    Geometry::Sphere<double_t> m_sphere;
    xg::Guid m_guid;

  public:
    FlowMeshPoint();
    FlowMeshPoint(Geometry::Sphere<double_t> sphere, const xg::Guid& guid);

    [[nodiscard]] const Geometry::Sphere<double_t>& getSphere() const;
    void setSphere(const Geometry::Sphere<double_t>& sphere);

    [[nodiscard]] const xg::Guid& getGuid() const;

    friend bool operator==(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs);
    friend bool operator!=(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs);

    friend bool operator<(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs);
    friend bool operator>(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs);
    friend bool operator<=(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs);
    friend bool operator>=(const FlowMeshPoint& lhs, const FlowMeshPoint& rhs);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHPOINT_HPP
