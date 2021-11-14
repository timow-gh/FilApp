#ifndef FILAPP_FLOWMESHMODEL_HPP
#define FILAPP_FLOWMESHMODEL_HPP

#include <Core/Types/TSet.hpp>
#include <Core/Types/TVector.hpp>
#include <FlowMesh/FlowMeshCone.hpp>
#include <FlowMesh/FlowMeshCylinder.hpp>
#include <FlowMesh/FlowMeshPresenter.hpp>
#include <FlowMesh/FlowMeshSegments.hpp>
#include <FlowMesh/FlowMeshSphere.hpp>
#include <FlowMesh/TypeId.hpp>
#include <Geometry/Segment.hpp>
#include <map>

namespace FlowMesh
{
class GeometryElementsMap
{
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

    [[nodiscard]] std::vector<TypeId> calcTypeIds() const;

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

class FlowMeshModel
{
    GeometryElementsMap m_geometryElements;
    FlowMeshPresenter* m_flowMeshPresenter{nullptr};

  public:
    void setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter);

    [[nodiscard]] std::vector<TypeId> calcTypeIds() const;

    void addSphere(const FlowMeshSphere& sphere);
    void addCone(const FlowMeshCone& flowMeshCone);
    void addCylinder(const FlowMeshCylinder& cylinder);
    void addSegments(const FlowMeshSegments& flowMeshSegments);

    void remove(const TypeId& typeId);
};
} // namespace FlowMesh

#endif // FILAPP_FLOWMESHMODEL_HPP
