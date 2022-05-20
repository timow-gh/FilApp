#ifndef MESHLER_GEOMETRYELEMENTS_HPP
#define MESHLER_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Meshler/MGuid.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>

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
    Core::TMap<FGuid, MSegments> m_segments;
    Core::TMap<FGuid, MSphere> m_spheres;
    Core::TMap<FGuid, MCone> m_cones;
    Core::TMap<FGuid, MCylinder> m_cylinder;
    Core::TMap<FGuid, MCuboid> m_cuboid;
    Core::TMap<FGuid, MGrid> m_grid;

  public:
    bool add(const MSegments& segments);
    bool add(const MSphere& sphere);
    bool add(const MCone& cone);
    bool add(const MCylinder& cylinder);
    bool add(const MCuboid& cuboid);
    bool add(const MGrid& grid);

    bool remove(const FGuid& fGuid);

    template <typename TGeometryElement>
    TGeometryElement* get(const FGuid& guid);

    template <>
    MSegments* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_segments);
    }

    template <>
    MSphere* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_spheres);
    }

    template <>
    MCone* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cones);
    }

    template <>
    MCylinder* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cylinder);
    }

    template <>
    MCuboid* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cuboid);
    }

    template <>
    MGrid* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_grid);
    }

    bool setPosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    CORE_NODISCARD Core::TVector<FGuid> getFGuidsFromMaps() const;

    CORE_NODISCARD const Core::TMap<FGuid, MSegments>& getSegmentMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MSphere>& getSphereMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MCone>& getConeMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MCylinder>& getCylinderMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MCuboid>& getCuboidMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MGrid>& getGridMap() const;
};
} // namespace FlowMesh

#endif // MESHLER_GEOMETRYELEMENTS_HPP
