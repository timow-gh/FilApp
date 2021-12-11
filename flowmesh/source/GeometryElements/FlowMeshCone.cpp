#include "FlowMesh/GeometryElements/FlowMeshCone.hpp"
#include "_deps/geometry-src/src/include/Geometry/Segment.hpp"
#include "_deps/linal-src/src/include/LinAl/LinearAlgebra.hpp"

using namespace Geometry;
using namespace LinAl;

namespace FlowMesh
{
FlowMeshCone::FlowMeshCone()
    : FGuidBase<FlowMeshCone>(FGuid())
    , m_cone(Cone<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
{
}
FlowMeshCone::FlowMeshCone(const Cone<double_t>& cone, const FGuid& fGuid)
    : FGuidBase<FlowMeshCone>(fGuid), m_cone(cone)
{
}
const Cone<double_t>& FlowMeshCone::getCone() const
{
    return m_cone;
}

} // namespace FlowMesh
