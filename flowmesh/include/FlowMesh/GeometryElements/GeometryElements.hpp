#ifndef FILAPP_GEOMETRYELEMENTS_HPP
#define FILAPP_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>

namespace FlowMesh
{
template <typename TFlowMeshGeometry,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
bool getImpl(FGuid guid, Map<FGuid, TFlowMeshGeometry>& map, TFlowMeshGeometry& result)
{
    auto iter = map.find(guid);
    if (iter != map.end())
    {
        result = iter->second;
        return true;
    }
    return false;
}

class GeometryElements {
    Core::TMap<FGuid, FlowMeshSegments> m_segments;
    Core::TMap<FGuid, FlowMeshSphere> m_spheres;
    Core::TMap<FGuid, FlowMeshCone> m_cones;
    Core::TMap<FGuid, FlowMeshCylinder> m_cylinder;
    Core::TMap<FGuid, FlowMeshCuboid> m_cuboid;

  public:
    bool add(const FlowMeshSegments& segments);
    bool add(const FlowMeshSphere& sphere);
    bool add(const FlowMeshCone& cone);
    bool add(const FlowMeshCylinder& cylinder);
    bool add(const FlowMeshCuboid& cuboid);

    template <typename TFlowMeshGeometry,
              typename = std::is_same<TFlowMeshGeometry, FlowMeshSphere>>
    bool get(FGuid guid, TFlowMeshGeometry& result)
    {
        if (getImpl(guid, m_spheres, result))
            return true;
        return false;
    }

    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshSegments>& getSegmentMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshSphere>& getSphereMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshCone>& getConeMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshCylinder>& getCylinderMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshCuboid>& getCuboidMap() const;

    bool remove(const FGuid& fGuid);
    bool setPosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    CORE_NODISCARD Core::TVector<FGuid> getFGuidsFromMaps() const;

  private:
};
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTS_HPP
