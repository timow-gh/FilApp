#ifndef FILAPP_GEOMETRYELEMENTS_HPP
#define FILAPP_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
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

    bool remove(const FGuid& fGuid);
    bool setPosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    CORE_NODISCARD std::vector<FGuid> getFGuidsFromMaps() const;
};
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTS_HPP
