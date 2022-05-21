#include <Meshler/GeometryElements/MCylinder.hpp>

using namespace Geometry;
using namespace LinAl;

namespace Meshler
{

MCylinder::MCylinder()
    : GeometryElementBase<MCylinder>(FGuid(), MGeometryConfigBase{})
    , m_cylinder(Cylinder<double_t>(Segment3d{ZERO_VEC3D, Z_VEC3D}, 1.0))
{
}

MCylinder::MCylinder(const Cylinder<double_t>& cylinder,
                     const FGuid& fGuid,
                     MGeometryConfigBase baseConfig)
    : GeometryElementBase<MCylinder>(fGuid, baseConfig), m_cylinder(cylinder)
{
}

const Cylinder<double_t>& MCylinder::getGeometryElement() const
{
    return m_cylinder;
}

} // namespace Meshler
