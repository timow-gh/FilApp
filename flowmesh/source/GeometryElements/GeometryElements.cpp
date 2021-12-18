#include "FlowMesh/GeometryElements/GeometryElements.hpp"

namespace FlowMesh
{
template <typename TGeometryElement,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
bool addImpl(const TGeometryElement& geometryElement,
             Map<FGuid, TGeometryElement>& map)
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
void removeElement(Map<FGuid, TGeometryElement>& map, const FGuid& fGuid)
{
    auto iter = map.find(fGuid);
    if (iter != map.end())
        map.erase(iter);
}

template <typename TGeometyElement,
          template <typename K,
                    typename V,
                    typename Compare = std::less<K>,
                    typename Alloc = std::allocator<std::pair<const K, V>>>
          class Map>
void aggregateGuids(std::vector<FGuid>& guids,
                    const Map<FGuid, TGeometyElement>& map)
{
    for (const auto& pair: map)
        guids.push_back(pair.first);
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

void GeometryElements::remove(const FGuid& fGuid)
{
    removeElement(m_segments, fGuid);
    removeElement(m_spheres, fGuid);
    removeElement(m_cones, fGuid);
    removeElement(m_cylinder, fGuid);
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

    return guids;
}
} // namespace FlowMesh