#ifndef FILAPP_FLOWMESHSPHERE_HPP
#define FILAPP_FLOWMESHSPHERE_HPP

#include "FlowMesh/TypeId.hpp"
#include "_deps/geometry-src/src/include/Geometry/Sphere.hpp"
#include "_deps/linal-src/src/include/LinAl/LinearAlgebra.hpp"

namespace FlowMesh
{
class FlowMeshSphere
{
    Geometry::Sphere<double_t> m_sphere;
    TypeId m_typeId;

  public:
    FlowMeshSphere();
    FlowMeshSphere(Geometry::Sphere<double_t> sphere, const TypeId& guid);

    [[nodiscard]] const Geometry::Sphere<double_t>& getSphere() const;
    void setSphere(const Geometry::Sphere<double_t>& sphere);

    [[nodiscard]] const TypeId& getTypeId() const;

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
