#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>

namespace FlowMesh
{

FlowMeshSphere::FlowMeshSphere()
    : GeometryElementBase<FlowMeshSphere>(FGuid(), FlowMeshGeometryConfigBase{})
    , m_sphere(Geometry::Sphere<double_t>(LinAl::ZERO_VEC3D, 1.0))
{
}

FlowMeshSphere::FlowMeshSphere(Geometry::Sphere<double_t> sphere,
                               const FGuid& guid,
                               FlowMeshGeometryConfigBase baseConfig)
    : GeometryElementBase<FlowMeshSphere>(guid, baseConfig), m_sphere(std::move(sphere))
{
}

const Geometry::Sphere<double_t>& FlowMeshSphere::getGeometryElement() const
{
    return m_sphere;
}

void FlowMeshSphere::setGeometryElement(const Geometry::Sphere<double_t>& sphere)
{
    m_sphere = sphere;
}

} // namespace FlowMesh