#include <Geometry/Segment.hpp>
#include <LinAl/LinearAlgebra.hpp>
#include <Meshler/GeometryElements/MCone.hpp>

using namespace Geometry;
using namespace LinAl;

namespace Meshler
{

MCone::MCone()
    : GeometryElementBase<MCone>(FGuid(), MGeometryConfigBase{})
    , m_cone(Cone<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
{
}

MCone::MCone(const Cone<double_t>& cone, const FGuid& fGuid, MGeometryConfigBase baseConfig)
    : GeometryElementBase<MCone>(fGuid, baseConfig), m_cone(cone)
{
}

const Cone<double_t>& MCone::getGeometryElement() const
{
    return m_cone;
}

} // namespace Meshler
