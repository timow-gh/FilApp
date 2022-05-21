#ifndef MESHLER_MCUBOID_HPP
#define MESHLER_MCUBOID_HPP

#include <Meshler/MGuid.hpp>
#include <Meshler/GeometryElements/MGeometryConfigBase.hpp>
#include <Meshler/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Cuboid.hpp>

namespace Meshler
{

class MCuboid : public GeometryElementBase<MCuboid> {
    Geometry::Cuboid<double_t> m_cuboid;

  public:
    MCuboid();
    MCuboid(const Geometry::Cuboid<double_t>& cuboid,
                   const FGuid& fGuid,
            MGeometryConfigBase baseConfig);

    CORE_NODISCARD const Geometry::Cuboid<double_t>& getGeometryElement() const;
};

} // namespace Meshler

#endif // MESHLER_MCUBOID_HPP
