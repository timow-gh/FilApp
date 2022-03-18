#ifndef FILAPP_FLOWMESHSPHERE_HPP
#define FILAPP_FLOWMESHSPHERE_HPP

#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{
class FlowMeshSphere : public GeometryElementBase<FlowMeshSphere> {
    Geometry::Sphere<double_t> m_sphere;

  public:
    FlowMeshSphere();
    FlowMeshSphere(Geometry::Sphere<double_t> sphere, const FGuid& guid);

    CORE_NODISCARD const Geometry::Sphere<double_t>& getGeometryElement() const;
    void setGeometryElement(const Geometry::Sphere<double_t>& sphere);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHSPHERE_HPP
