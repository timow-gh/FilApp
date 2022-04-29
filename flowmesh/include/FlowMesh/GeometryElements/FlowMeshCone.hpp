#ifndef FILAPP_FLOWMESHCONE_HPP
#define FILAPP_FLOWMESHCONE_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/GeometryElementBase.hpp>
#include <Geometry/Cone.hpp>

namespace FlowMesh
{

class FlowMeshCone : public GeometryElementBase<FlowMeshCone> {
    Geometry::Cone<double_t> m_cone;

  public:
    FlowMeshCone();
    FlowMeshCone(const Geometry::Cone<double_t>& cone, const FGuid& fGuid);

    [[nodiscard]] const Geometry::Cone<double_t>& getGeometryElement() const;
};

} // namespace FlowMesh

#endif // FILAPP_FLOWMESHCONE_HPP
