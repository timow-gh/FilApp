#include "FlowMesh/FlowMeshModel.hpp"
#include "FlowMesh/FlowMeshPresenter.hpp"

namespace FlowMesh
{
bool GeometryElementsMap::add(const FlowMeshSegments& segments)
{
    auto res = m_segments.emplace(segments.getTypeId(), segments);
    return res.second;
}
bool GeometryElementsMap::add(const FlowMeshSphere& sphere)
{
    auto res = m_spheres.emplace(sphere.getTypeId(), sphere);
    return res.second;
}
bool GeometryElementsMap::add(const FlowMeshCone& cone)
{
    auto res = m_cones.emplace(cone.getTypeId(), cone);
    return res.second;
}
bool GeometryElementsMap::add(const FlowMeshCylinder& cylinder)
{
    auto res = m_cylinder.emplace(cylinder.getTypeId(), cylinder);
    return res.second;
}
void GeometryElementsMap::remove(const TypeId& typeId)
{
    removeElement(m_segments, typeId);
    removeElement(m_spheres, typeId);
}
std::vector<TypeId> GeometryElementsMap::calcTypeIds() const
{
    std::vector<TypeId> result;
    std::size_t resultSize = m_segments.size() + m_spheres.size();
    result.reserve(resultSize);

    calcTypeIds(result, m_segments);
    calcTypeIds(result, m_spheres);

    return result;
}

void FlowMeshModel::setFlowMeshPresenter(FlowMeshPresenter* flowMeshPresenter)
{
    m_flowMeshPresenter = flowMeshPresenter;
}
std::vector<TypeId> FlowMeshModel::calcTypeIds() const
{
    return m_geometryElements.calcTypeIds();
}
void FlowMeshModel::addSegments(const FlowMeshSegments& flowMeshSegments)
{
    if (m_geometryElements.add(flowMeshSegments))
        m_flowMeshPresenter->add(flowMeshSegments);
}
void FlowMeshModel::addSphere(const FlowMeshSphere& sphere)
{
    if (m_geometryElements.add(sphere))
        m_flowMeshPresenter->add(sphere);
}
void FlowMeshModel::addCone(const FlowMeshCone& flowMeshCone)
{
    if (m_geometryElements.add(flowMeshCone))
        m_flowMeshPresenter->add(flowMeshCone);
}
void FlowMeshModel::addCylinder(const FlowMeshCylinder& cylinder)
{
    if (m_geometryElements.add(cylinder))
        m_flowMeshPresenter->add(cylinder);
}
void FlowMeshModel::remove(const TypeId& typeId)
{
    m_geometryElements.remove(typeId);
    m_flowMeshPresenter->remove(typeId);
}
} // namespace FlowMesh
