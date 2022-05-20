#ifndef MESHLER_MCYLINDER_HPP
#define MESHLER_MCYLINDER_HPP

#include <Meshler/MGuid.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Geometry/Cylinder.hpp>
#include <Geometry/Segment.hpp>

namespace FlowMesh
{

class MCylinder : public GeometryElementBase<MCylinder> {
    Geometry::Cylinder<double_t> m_cylinder;

  public:
    MCylinder();
    MCylinder(const Geometry::Cylinder<double_t>& cylinder, const FGuid& fGuid,
              MGeometryConfigBase baseConfig);

    [[nodiscard]] const Geometry::Cylinder<double_t>& getGeometryElement() const;
};

} // namespace FlowMesh

#endif // MESHLER_MCYLINDER_HPP
