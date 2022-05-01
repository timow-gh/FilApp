#include "FlowMesh/GeometryElements/GeometryElements.hpp"

namespace FlowMesh
{

template <typename TGeometryElement,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
bool addImpl(const TGeometryElement& geometryElement, Map<FGuid, TGeometryElement>& map)
{
    auto iter = map.emplace(geometryElement.getFGuid(), geometryElement);
    return iter.second;
}

template <typename TGeometryElement,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
bool removeElement(Map<FGuid, TGeometryElement>& map, const FGuid& fGuid)
{
    auto iter = map.find(fGuid);
    if (iter != map.end())
    {
        map.erase(iter);
        return true;
    }
    return false;
}

template <typename TGeometryElement,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
void aggregateGuids(std::vector<FGuid>& guids, const Map<FGuid, TGeometryElement>& map)
{
    for (const auto& pair: map)
        guids.push_back(pair.first);
}

template <typename TGeometryElement,
          template <typename K,
                    typename V,
                    typename Comparator = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
bool updatePosition(const LinAl::Vec3d& position,
                    const FGuid& fGuid,
                    Map<FGuid, TGeometryElement>& map)
{
    auto iter = map.find(fGuid);
    if (iter == map.cend())
        return false;
    iter->second.setPosition(position);
    return true;
}

bool GeometryElements::add(const FlowMeshSegments& segments)
{
    return addImpl(segments, m_segments);
}

bool GeometryElements::add(const FlowMeshSphere& sphere)
{
    return addImpl(sphere, m_spheres);
}

bool GeometryElements::add(const FlowMeshCone& cone)
{
    return addImpl(cone, m_cones);
}

bool GeometryElements::add(const FlowMeshCylinder& cylinder)
{
    return addImpl(cylinder, m_cylinder);
}

bool GeometryElements::add(const FlowMeshCuboid& cuboid)
{
    return addImpl(cuboid, m_cuboid);
}

bool GeometryElements::add(const FlowMeshGrid& grid)
{
    return addImpl(grid, m_grid);
}

bool GeometryElements::remove(const FGuid& fGuid)
{
    bool removedSegment = removeElement(m_segments, fGuid);
    bool removedSphere = removeElement(m_spheres, fGuid);
    bool removedCone = removeElement(m_cones, fGuid);
    bool removedCylinder = removeElement(m_cylinder, fGuid);
    bool removedCuboid = removeElement(m_cylinder, fGuid);
    bool removedGrid = removeElement(m_grid, fGuid);

    return removedSegment || removedSphere || removedCone || removedCylinder || removedCuboid ||
           removedGrid;
}

bool GeometryElements::setPosition(const FGuid& fGuid, const LinAl::Vec3d& position)
{
    bool updatedSeg = updatePosition(position, fGuid, m_segments);
    bool updatedSphere = updatePosition(position, fGuid, m_spheres);
    bool updatedCone = updatePosition(position, fGuid, m_cones);
    bool updatedCylinder = updatePosition(position, fGuid, m_cylinder);
    bool updatedCuboid = updatePosition(position, fGuid, m_cuboid);
    bool updatedGrid = updatePosition(position, fGuid, m_grid);

    return updatedSeg || updatedSphere || updatedCone || updatedCylinder || updatedCuboid ||
           updatedGrid;
}

std::vector<FGuid> GeometryElements::getFGuidsFromMaps() const
{
    std::vector<FGuid> guids;
    std::size_t resultSize = m_segments.size() + m_spheres.size();
    guids.reserve(resultSize);

    aggregateGuids(guids, m_segments);
    aggregateGuids(guids, m_spheres);
    aggregateGuids(guids, m_cones);
    aggregateGuids(guids, m_cylinder);
    aggregateGuids(guids, m_cuboid);
    aggregateGuids(guids, m_grid);

    return guids;
}

const Core::TMap<FlowMesh::FGuid, FlowMesh::FlowMeshSegments>&
GeometryElements::getSegmentMap() const
{
    return m_segments;
}

const Core::TMap<FlowMesh::FGuid, FlowMesh::FlowMeshSphere>& GeometryElements::getSphereMap() const
{
    return m_spheres;
}

const Core::TMap<FlowMesh::FGuid, FlowMesh::FlowMeshCone>& GeometryElements::getConeMap() const
{
    return m_cones;
}

const Core::TMap<FlowMesh::FGuid, FlowMesh::FlowMeshCylinder>&
GeometryElements::getCylinderMap() const
{
    return m_cylinder;
}

const Core::TMap<FGuid, FlowMeshCuboid>& GeometryElements::getCuboidMap() const
{
    return m_cuboid;
}

const Core::TMap<FGuid, FlowMeshGrid>& GeometryElements::getGridMap() const
{
    return m_grid;
}

} // namespace FlowMesh