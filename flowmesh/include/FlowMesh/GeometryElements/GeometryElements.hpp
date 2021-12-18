#ifndef FILAPP_GEOMETRYELEMENTS_HPP
#define FILAPP_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <vector>

namespace FlowMesh
{
class GeometryElements {
    Core::TMap<FGuid, FlowMeshSegments> m_segments;
    Core::TMap<FGuid, FlowMeshSphere> m_spheres;
    Core::TMap<FGuid, FlowMeshCone> m_cones;
    Core::TMap<FGuid, FlowMeshCylinder> m_cylinder;

  public:
    bool add(const FlowMeshSegments& segments);
    bool add(const FlowMeshSphere& sphere);
    bool add(const FlowMeshCone& cone);
    bool add(const FlowMeshCylinder& cylinder);

    void remove(const FGuid& fGuid);

    [[nodiscard]] std::vector<FGuid> getFGuidsFromMaps() const;
};
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTS_HPP
