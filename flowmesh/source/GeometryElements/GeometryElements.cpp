#include "FlowMesh/GeometryElements/GeometryElements.hpp"

namespace FlowMesh
{
bool GeometryElements::add(const FlowMeshSegments& segments)
{
    auto res = m_segments.emplace(segments.getFGuid(), segments);
    return res.second;
}
bool GeometryElements::add(const FlowMeshSphere& sphere)
{
    auto res = m_spheres.emplace(sphere.getFGuid(), sphere);
    return res.second;
}
bool GeometryElements::add(const FlowMeshCone& cone)
{
    auto res = m_cones.emplace(cone.getFGuid(), cone);
    return res.second;
}
bool GeometryElements::add(const FlowMeshCylinder& cylinder)
{
    auto res = m_cylinder.emplace(cylinder.getFGuid(), cylinder);
    return res.second;
}
void GeometryElements::remove(const FGuid& fGuid)
{
    removeElement(m_segments, fGuid);
    removeElement(m_spheres, fGuid);
}
std::vector<FGuid> GeometryElements::getFGuidsFromMaps() const
{
    std::vector<FGuid> result;
    std::size_t resultSize = m_segments.size() + m_spheres.size();
    result.reserve(resultSize);

    calcAllGuids(result, m_segments);
    calcAllGuids(result, m_spheres);

    return result;
}
} // namespace FlowMesh