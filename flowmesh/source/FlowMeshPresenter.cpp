#include "FlowMesh/FlowMeshPresenter.hpp"
#include <FilApp/Renderables/Vertex.hpp>
#include <FlowMesh/FlowMeshCylinder.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
#include <Geometry/HalfedgeMeshBuilder/ConeMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CylinderMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>

namespace FlowMesh
{
FilApp::TriangleRenderable FlowMeshPresenter::createTriangleRenderable(
    const Geometry::HalfedgeMesh<double_t>& halfedgeMesh)
{
    // TODO Color
    constexpr uint32_t COLOR = 0xff00aaffu;

    std::vector<FilApp::Vertex> vertices;
    for (const auto& vec: halfedgeMesh.getVertexPoints())
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(vec[0]),
                                           static_cast<float_t>(vec[1]),
                                           static_cast<float_t>(vec[2])},
                                          COLOR});

    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, uint16_t>(
                halfedgeMesh.getFacets())};
}
FilApp::LineRenderable FlowMeshPresenter::createLineRenderables(
    const FlowMeshSegments& flowMeshSegments)
{
    // TODO Color
    constexpr uint32_t COLOR = 0xff00aaffu;

    Core::TVector<FilApp::Vertex> vertices;
    for (const auto& segment: flowMeshSegments.getSegments())
    {
        auto& source = segment.getSource();
        auto& target = segment.getTarget();
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(source[0]),
                                           static_cast<float_t>(source[1]),
                                           static_cast<float_t>(source[2])},
                                          COLOR});
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(target[0]),
                                           static_cast<float_t>(target[1]),
                                           static_cast<float_t>(target[2])},
                                          COLOR});
    }

    return FilApp::LineRenderable::create(vertices);
}

static void
segmentFilAppVertices(const Geometry::HalfedgeMesh<double_t>& heMesh,
                      const std::vector<Geometry::SegmentIndices>& segIndices,
                      std::vector<FilApp::Vertex>& vertices)
{
    for (const auto& segmentIndices: segIndices)
    {
        auto sPoint = heMesh.getVertex(segmentIndices.source).getPoint();
        auto tPoint = heMesh.getVertex(segmentIndices.target).getPoint();
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(sPoint[0]),
                                           static_cast<float_t>(sPoint[1]),
                                           static_cast<float_t>(sPoint[2])},
                                          0xff000000u});
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(tPoint[0]),
                                           static_cast<float_t>(tPoint[1]),
                                           static_cast<float_t>(tPoint[2])},
                                          0xff000000u});
    }
}

void FlowMeshPresenter::add(const FlowMeshSphere& flowMeshSphere)
{
    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        Geometry::SphereMeshBuilder<double_t>()
            .setPolarCount(10)
            .setAzimuthCount(20)
            .setSphere(flowMeshSphere.getSphere())
            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*sphereMesh);
    std::vector<FilApp::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*sphereMesh, segIndices, filAppVertices);

    auto verticesId = m_mainView->addRenderable(
        FilApp::LineRenderable::create(filAppVertices));
    auto sphereId =
        m_mainView->addRenderable(createTriangleRenderable(*sphereMesh));

    m_typeIdRenderableMapping.emplace(
        flowMeshSphere.getTypeId(),
        std::vector<FilApp::RenderableIdentifier>{verticesId, sphereId});
}
void FlowMeshPresenter::add(const FlowMeshCone& flowMeshCone)
{
    auto coneMesh = Geometry::ConeMeshBuilder<double_t>()
                        .setCone((flowMeshCone.getCone()))
                        .setAzimuthCount(10)
                        .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*coneMesh);
    std::vector<FilApp::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*coneMesh, segIndices, filAppVertices);

    auto verticesId = m_mainView->addRenderable(
        FilApp::LineRenderable::create(filAppVertices));
    auto coneId =
        m_mainView->addRenderable(createTriangleRenderable(*coneMesh));

    m_typeIdRenderableMapping.emplace(
        flowMeshCone.getTypeId(),
        std::vector<FilApp::RenderableIdentifier>{verticesId, coneId});
}
void FlowMeshPresenter::add(const FlowMeshCylinder& flowMeshCylinder)
{
    auto cylinderMesh = Geometry::CylinderMeshBuilder<double_t>()
                            .setCylinder(flowMeshCylinder.getCylinder())
                            .setAzimuthCount(10)
                            .build();

    const auto& segIndices = Geometry::calcMeshSegmentIndices(*cylinderMesh);
    std::vector<FilApp::Vertex> filAppVertices;
    filAppVertices.reserve(segIndices.size());
    segmentFilAppVertices(*cylinderMesh, segIndices, filAppVertices);

    auto verticesId = m_mainView->addRenderable(
        FilApp::LineRenderable::create(filAppVertices));
    auto coneId =
        m_mainView->addRenderable(createTriangleRenderable(*cylinderMesh));

    m_typeIdRenderableMapping.emplace(
        flowMeshCylinder.getTypeId(),
        std::vector<FilApp::RenderableIdentifier>{verticesId, coneId});
}
void FlowMeshPresenter::add(const FlowMeshSegments& flowMeshSegments)
{
    auto segmentsId =
        m_mainView->addRenderable(createLineRenderables(flowMeshSegments));
    m_typeIdRenderableMapping.emplace(
        flowMeshSegments.getTypeId(),
        std::vector<FilApp::RenderableIdentifier>{segmentsId});
}
void FlowMeshPresenter::remove(const TypeId& typeId)
{
    auto iter = m_typeIdRenderableMapping.find(typeId);
    if (iter != m_typeIdRenderableMapping.end())
        for (const FilApp::RenderableIdentifier id: iter->second)
            m_mainView->removeRenderable(id);
}
void FlowMeshPresenter::setIdleAnimation(const FilApp::Vec3& rotationAxis)
{
    for (const auto id: m_mainView->getRenderableIdentifiers())
        m_mainView->addRotationAnimation(id, rotationAxis);
}

} // namespace FlowMesh