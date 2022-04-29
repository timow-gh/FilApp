#ifndef FILAPP_FLOWMESHCUBOID_HPP
#define FILAPP_FLOWMESHCUBOID_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Cuboid.hpp>

namespace FlowMesh
{

class FlowMeshCuboid : public GeometryElementBase<FlowMeshCuboid> {
    Geometry::Cuboid<double_t> m_cuboid;

  public:
    FlowMeshCuboid();
    FlowMeshCuboid(const Geometry::Cuboid<double_t>& cuboid, const FGuid& fGuid);

    [[nodiscard]] const Geometry::Cuboid<double_t>& getGeometryElement() const;
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCUBOID_HPP
