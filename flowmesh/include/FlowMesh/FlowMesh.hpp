#ifndef FILAPP_FLOWMESH_HPP
#define FILAPP_FLOWMESH_HPP

#include <FilApp/Renderables/TriangleRenderable.hpp>
#include <Geometry/Sphere.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <utility>

namespace FlowMesh
{
class FlowMeshSphere
{
    Geometry::Sphere<double_t> m_sphere;

  public:
    explicit FlowMeshSphere(Geometry::Sphere<double_t> sphere)
        : m_sphere(std::move(sphere))
    {
    }

    [[nodiscard]] const Geometry::Sphere<double_t>& getSphere() const
    {
        return m_sphere;
    }
    void setSphere(const Geometry::Sphere<double_t>& sphere)
    {
        m_sphere = sphere;
    }
};

FilApp::TriangleRenderable
createTriangleRenderable(const FlowMeshSphere& flowMeshSphere);

} // namespace FlowMesh

#endif // FILAPP_FLOWMESH_HPP
