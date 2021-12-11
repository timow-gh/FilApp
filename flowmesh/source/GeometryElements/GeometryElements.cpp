#include "FlowMesh/GeometryElements/GeometryElements.hpp"

namespace FlowMesh
{
bool GeometryElements::add(const FlowMeshSegments& segments)
{
    auto res = m_segments.emplace(segments.getTypeId(), segments);
    return res.second;
}
bool GeometryElements::add(const FlowMeshSphere& sphere)
{
    auto res = m_spheres.emplace(sphere.getTypeId(), sphere);
    return res.second;
}
bool GeometryElements::add(const FlowMeshCone& cone)
{
    auto res = m_cones.emplace(cone.getTypeId(), cone);
    return res.second;
}
bool GeometryElements::add(const FlowMeshCylinder& cylinder)
{
    auto res = m_cylinder.emplace(cylinder.getTypeId(), cylinder);
    return res.second;
}
void GeometryElements::remove(const TypeId& typeId)
{
    removeElement(m_segments, typeId);
    removeElement(m_spheres, typeId);
}
std::vector<TypeId> GeometryElements::getTypeIdsFromMaps() const
{
    std::vector<TypeId> result;
    std::size_t resultSize = m_segments.size() + m_spheres.size();
    result.reserve(resultSize);

    calcTypeIds(result, m_segments);
    calcTypeIds(result, m_spheres);

    return result;
}
} // namespace FlowMesh