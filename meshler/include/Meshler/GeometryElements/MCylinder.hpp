#ifndef MESHLER_MCYLINDER_HPP
#define MESHLER_MCYLINDER_HPP

#include <Geometry/Cylinder.hpp>
#include <Geometry/Segment.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{

class MCylinder : public GeometryElementBase<MCylinder> {
  Geometry::Cylinder<double_t> m_cylinder;

public:
  MCylinder();
  MCylinder(const Geometry::Cylinder<double_t>& cylinder, const FGuid& fGuid, MGeometryConfigBase baseConfig);

  CORE_NODISCARD const Geometry::Cylinder<double_t>& getGeometryElement() const;
};

} // namespace Meshler

#endif // MESHLER_MCYLINDER_HPP
