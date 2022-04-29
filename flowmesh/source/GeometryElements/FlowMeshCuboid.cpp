#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

FlowMeshCuboid::FlowMeshCuboid()
    : GeometryElementBase<FlowMeshCuboid>(FGuid())
    , m_cuboid(Geometry::Cuboid<double_t>(LinAl::ZERO_VEC3D, LinAl::Vec3d{1, 1, 1}))
{
}

FlowMeshCuboid::FlowMeshCuboid(const Geometry::Cuboid<double_t>& cuboid, const FGuid& fGuid)
    : GeometryElementBase<FlowMeshCuboid>(fGuid), m_cuboid(cuboid)
{
}

const Geometry::Cuboid<double_t>& FlowMeshCuboid::getGeometryElement() const
{
    return m_cuboid;
}

} // namespace FlowMesh
