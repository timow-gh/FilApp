#include "FlowMesh/Model.hpp"
#include "FlowMesh/Presenter.hpp"

namespace FlowMesh
{
Model::Model(Presenter* presenter)
{
    m_flowMeshPresenter = presenter;
}

std::vector<FGuid> Model::calcFGuids() const
{
    return m_geometryElements.getFGuidsFromMaps();
}

void Model::remove(const FGuid& fGuid)
{
    m_geometryElements.remove(fGuid);
    m_flowMeshPresenter->remove(fGuid);
}

void Model::setPosition(const FGuid& fGuid, LinAl::Vec3d& position)
{
    if (m_geometryElements.setPosition(fGuid, position))
        m_flowMeshPresenter->updatePosition(fGuid, position);
}

SnapGeometries Model::calcModelSnapGeometries() const
{
    SnapGeometries result{Geometry::Plane<double_t>{LinAl::ZERO_VEC3D, LinAl::Z_VEC3D}};

    for (const auto& pair: m_geometryElements.getSegmentMap())
        for (const Geometry::Segment3d& segment: pair.second.getSegments())
            result.add(segment);

    for (const auto& pair: m_geometryElements.getSphereMap())
    {
        auto& flowMeshGeom = pair.second;
        result.add(flowMeshGeom.getGeometryElement(), pair.second.getPosition());
    }

    return result;
}

} // namespace FlowMesh
