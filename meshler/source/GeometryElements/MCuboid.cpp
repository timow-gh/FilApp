#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>

namespace Meshler
{

MCuboid::MCuboid()
    : GeometryElementBase<MCuboid>(FGuid(), MGeometryConfigBase{})
    , m_cuboid(Geometry::Cuboid<double_t>(LinAl::ZERO_VEC3D, LinAl::Vec3d{1, 1, 1}))
{
}

MCuboid::MCuboid(const Geometry::Cuboid<double_t>& cuboid, const FGuid& fGuid, MGeometryConfigBase baseConfig)
    : GeometryElementBase<MCuboid>(fGuid, baseConfig)
    , m_cuboid(cuboid)
{
}

const Geometry::Cuboid<double_t>& MCuboid::getGeometryElement() const
{
  return m_cuboid;
}

} // namespace Meshler
