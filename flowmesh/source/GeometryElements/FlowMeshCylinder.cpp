#include "FlowMesh/GeometryElements/FlowMeshCylinder.hpp"

using namespace Geometry;
using namespace LinAl;

namespace FlowMesh
{

FlowMeshCylinder::FlowMeshCylinder()
    : GeometryElementBase<FlowMeshCylinder>(FGuid(), FlowMeshGeometryConfigBase{})
    , m_cylinder(Cylinder<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
{
}

FlowMeshCylinder::FlowMeshCylinder(const Cylinder<double_t>& cylinder,
                                   const FGuid& fGuid,
                                   FlowMeshGeometryConfigBase baseConfig)
    : GeometryElementBase<FlowMeshCylinder>(fGuid, baseConfig), m_cylinder(cylinder)
{
}

const Cylinder<double_t>& FlowMeshCylinder::getGeometryElement() const
{
    return m_cylinder;
}

} // namespace FlowMesh
