#ifndef FILAPP_GEOMETRYELEMENTS_HPP
#define FILAPP_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCuboid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshGrid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>

namespace FlowMesh
{

namespace details
{
template <typename TFlowMeshGeometry,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
TFlowMeshGeometry* getImpl(const FGuid& guid, Map<FGuid, TFlowMeshGeometry>& map)
{
    auto iter = map.find(guid);
    if (iter != map.end())
        return &iter->second;
    return nullptr;
}
} // namespace details

class GeometryElements {
    Core::TMap<FGuid, FlowMeshSegments> m_segments;
    Core::TMap<FGuid, FlowMeshSphere> m_spheres;
    Core::TMap<FGuid, FlowMeshCone> m_cones;
    Core::TMap<FGuid, FlowMeshCylinder> m_cylinder;
    Core::TMap<FGuid, FlowMeshCuboid> m_cuboid;
    Core::TMap<FGuid, FlowMeshGrid> m_grid;

  public:
    bool add(const FlowMeshSegments& segments);
    bool add(const FlowMeshSphere& sphere);
    bool add(const FlowMeshCone& cone);
    bool add(const FlowMeshCylinder& cylinder);
    bool add(const FlowMeshCuboid& cuboid);
    bool add(const FlowMeshGrid& grid);

    bool remove(const FGuid& fGuid);

    template <typename TGeometryElement>
    TGeometryElement* get(const FGuid& guid);

    template <>
    FlowMeshSegments* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_segments);
    }

    template <>
    FlowMeshSphere* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_spheres);
    }

    template <>
    FlowMeshCone* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cones);
    }

    template <>
    FlowMeshCylinder* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cylinder);
    }

    template <>
    FlowMeshCuboid* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cuboid);
    }

    template <>
    FlowMeshGrid* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_grid);
    }

    bool setPosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    CORE_NODISCARD Core::TVector<FGuid> getFGuidsFromMaps() const;

    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshSegments>& getSegmentMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshSphere>& getSphereMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshCone>& getConeMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshCylinder>& getCylinderMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshCuboid>& getCuboidMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, FlowMeshGrid>& getGridMap() const;
};
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTS_HPP
