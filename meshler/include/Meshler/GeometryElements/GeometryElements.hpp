#ifndef MESHLER_GEOMETRYELEMENTS_HPP
#define MESHLER_GEOMETRYELEMENTS_HPP

#include <Core/Types/TMap.hpp>
#include <Core/Utils/Compiler.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/GeometryElements/SnapGeometries.hpp>
#include <Meshler/MGuid.hpp>

namespace Meshler
{

namespace details
{
template <typename TMeshlerGeometry,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
TMeshlerGeometry* getImpl(const FGuid& guid, Map<FGuid, TMeshlerGeometry>& map)
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

    SnapGeometries m_snapGeometries;

  public:
    bool add(MSegments&& segments);
    bool add(MSphere&& sphere);
    bool add(MCone&& cone);
    bool add(MCylinder&& cylinder);
    bool add(MCuboid&& cuboid);
    bool add(MGrid&& grid);

    bool remove(const FGuid& fGuid);

    template <typename TGeometryElement>
    CORE_NODISCARD TGeometryElement* get(const FGuid& guid);

    template <>
    CORE_NODISCARD MSegments* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_segments);
    }

    template <>
    CORE_NODISCARD MSphere* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_spheres);
    }

    template <>
    CORE_NODISCARD MCone* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cones);
    }

    template <>
    CORE_NODISCARD MCylinder* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cylinder);
    }

    template <>
    CORE_NODISCARD MCuboid* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_cuboid);
    }

    template <>
    CORE_NODISCARD MGrid* get(const FGuid& guid)
    {
        return details::getImpl(guid, m_grid);
    }

    CORE_NODISCARD SnapGeometries& getSnapGeometries() { return m_snapGeometries; }

    bool setPosition(const FGuid& fGuid, const LinAl::Vec3d& position);

    CORE_NODISCARD Core::TVector<FGuid> getFGuidsFromMaps() const;

    CORE_NODISCARD const Core::TMap<FGuid, MSegments>& getSegmentMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MSphere>& getSphereMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MCone>& getConeMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MCylinder>& getCylinderMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MCuboid>& getCuboidMap() const;
    CORE_NODISCARD const Core::TMap<FGuid, MGrid>& getGridMap() const;
};
} // namespace Meshler

#endif // MESHLER_GEOMETRYELEMENTS_HPP
