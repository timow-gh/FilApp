#ifndef FILAPP_GEOMETRYELEMENTS_HPP
#define FILAPP_GEOMETRYELEMENTS_HPP

#include <FlowMesh/FlowMeshGuid.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCone.hpp>
#include <FlowMesh/GeometryElements/FlowMeshCylinder.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSegments.hpp>
#include <FlowMesh/GeometryElements/FlowMeshSphere.hpp>
#include <map>
#include <vector>

namespace FlowMesh
{
class GeometryElements {
    std::map<FGuid, FlowMeshSegments> m_segments;
    std::map<FGuid, FlowMeshSphere> m_spheres;
    std::map<FGuid, FlowMeshCone> m_cones;
    std::map<FGuid, FlowMeshCylinder> m_cylinder;

  public:
    bool add(const FlowMeshSegments& segments);
    bool add(const FlowMeshSphere& sphere);
    bool add(const FlowMeshCone& cone);
    bool add(const FlowMeshCylinder& cylinder);

    void remove(const FGuid& fGuid);

    [[nodiscard]] std::vector<FGuid> getFGuidsFromMaps() const;

  private:
    template <typename V>
    void calcAllGuids(std::vector<FGuid>& fGuids,
                      const std::map<FGuid, V>& map) const
    {
        for (const auto& pair: map)
            fGuids.push_back(pair.first);
    }

    template <typename V>
    void removeElement(std::map<FGuid, V>& map, const FGuid& fGuid)
    {
        auto iter = map.find(fGuid);
        if (iter != map.end())
            map.erase(iter);
    }
};
} // namespace FlowMesh

#endif // FILAPP_GEOMETRYELEMENTS_HPP
