#ifndef FILAPP_FLOWMESHSPHERE_HPP
#define FILAPP_FLOWMESHSPHERE_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{
class FlowMeshSphere {
    Geometry::Sphere<double_t> m_sphere;
    FGuid m_fGuid;

  public:
    FlowMeshSphere();
    FlowMeshSphere(Geometry::Sphere<double_t> sphere, const FGuid& guid);

    [[nodiscard]] const Geometry::Sphere<double_t>& getSphere() const;
    void setSphere(const Geometry::Sphere<double_t>& sphere);

    [[nodiscard]] const FGuid& getFGuid() const;

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
