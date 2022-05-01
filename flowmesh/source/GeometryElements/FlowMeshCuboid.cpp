#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <LinAl/LinearAlgebra.hpp>

namespace FlowMesh
{

FlowMeshCuboid::FlowMeshCuboid()
    : GeometryElementBase<FlowMeshCuboid>(FGuid(), FlowMeshGeometryConfigBase{})
    , m_cuboid(Geometry::Cuboid<double_t>(LinAl::ZERO_VEC3D, LinAl::Vec3d{1, 1, 1}))
{
}

FlowMeshCuboid::FlowMeshCuboid(const Geometry::Cuboid<double_t>& cuboid,
                               const FGuid& fGuid,
                               FlowMeshGeometryConfigBase baseConfig)
    : GeometryElementBase<FlowMeshCuboid>(fGuid, baseConfig), m_cuboid(cuboid)
{
}

const Geometry::Cuboid<double_t>& FlowMeshCuboid::getGeometryElement() const
{
    return m_cuboid;
}

} // namespace FlowMesh
