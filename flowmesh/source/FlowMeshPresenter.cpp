#include "FlowMesh/FlowMeshPresenter.hpp"
#include <FilApp/Renderables/Vertex.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
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
void FlowMeshPresenter::add(const FlowMeshSphere& flowMeshSphere)
{
    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        Geometry::SphereMeshBuilder<double_t>()
            .setPolarCount(10)
            .setAzimuthCount(20)
            .setSphere(flowMeshSphere.getSphere())
            .build();

    const auto& segIndices = Geometry::calcSegmentIndices(*sphereMesh);
    std::vector<FilApp::Vertex> vertices;
    vertices.reserve(segIndices.size());
    for (const auto& segmentIndices: segIndices)
    {
        auto sPoint = sphereMesh->getVertex(segmentIndices.source).getPoint();
        auto tPoint = sphereMesh->getVertex(segmentIndices.target).getPoint();
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(sPoint[0]),
                                           static_cast<float_t>(sPoint[1]),
                                           static_cast<float_t>(sPoint[2])},
                                          0xff000000u});
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(tPoint[0]),
                                           static_cast<float_t>(tPoint[1]),
                                           static_cast<float_t>(tPoint[2])},
                                          0xff000000u});
    }
    m_mainView->addRenderable(FilApp::LineRenderable::create(vertices));

    m_mainView->addRenderable(createTriangleRenderable(*sphereMesh));
}
void FlowMeshPresenter::add(const FlowMeshSegments& flowMeshSegments)
{
    m_mainView->addRenderable(createLineRenderables(flowMeshSegments));
}
} // namespace FlowMesh