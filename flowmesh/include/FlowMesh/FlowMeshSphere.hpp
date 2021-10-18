#ifndef FILAPP_FLOWMESHSPHERE_HPP
#define FILAPP_FLOWMESHSPHERE_HPP

#include <CrossGuid/Guid.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{
class FlowMeshSphere
{
    Geometry::Sphere<double_t> m_sphere;
    xg::Guid m_guid;

  public:
    FlowMeshSphere();
    FlowMeshSphere(Geometry::Sphere<double_t> sphere, const xg::Guid& guid);

    [[nodiscard]] const Geometry::Sphere<double_t>& getSphere() const;
    void setSphere(const Geometry::Sphere<double_t>& sphere);

    [[nodiscard]] const xg::Guid& getGuid() const;

    friend bool operator==(const FlowMeshSphere& lhs,
                           const FlowMeshSphere& rhs);
    friend bool operator!=(const FlowMeshSphere& lhs,
                           const FlowMeshSphere& rhs);

    friend bool operator<(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs);
    friend bool operator>(const FlowMeshSphere& lhs, const FlowMeshSphere& rhs);
    friend bool operator<=(const FlowMeshSphere& lhs,
                           const FlowMeshSphere& rhs);
    friend bool operator>=(const FlowMeshSphere& lhs,
                           const FlowMeshSphere& rhs);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHSPHERE_HPP
