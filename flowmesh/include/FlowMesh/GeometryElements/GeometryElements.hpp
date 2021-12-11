#ifndef FILAPP_GEOMETRYELEMENTS_HPP
#define FILAPP_GEOMETRYELEMENTS_HPP

#include "FlowMeshCone.hpp"
#include "FlowMeshCylinder.hpp"
#include "FlowMeshSegments.hpp"
#include "FlowMeshSphere.hpp"
#include "FlowMesh/TypeId.hpp"
#include <map>
#include <vector>

namespace FlowMesh
{
class GeometryElements {
    std::map<TypeId, FlowMeshSegments> m_segments;
    std::map<TypeId, FlowMeshSphere> m_spheres;
    std::map<TypeId, FlowMeshCone> m_cones;
    std::map<TypeId, FlowMeshCylinder> m_cylinder;

  public:
    bool add(const FlowMeshSegments& segments);
    bool add(const FlowMeshSphere& sphere);
    bool add(const FlowMeshCone& cone);
    bool add(const FlowMeshCylinder& cylinder);

    void remove(const TypeId& typeId);

    [[nodiscard]] std::vector<TypeId> getTypeIdsFromMaps() const;

  private:
    template <typename V>
    void calcTypeIds(std::vector<TypeId>& typeIds,
                     const std::map<TypeId, V>& map) const
    {
        for (const auto& pair: map)
            typeIds.push_back(pair.first);
    }

    template <typename V>
    void removeElement(std::map<TypeId, V>& map, const TypeId& typeId)
    {
        auto iter = map.find(typeId);
        if (iter != map.end())
            map.erase(iter);
    }
};
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTS_HPP
