#include "FlowMesh/FlowMeshPresenter.hpp"
#include <FilApp/Renderables/Vertex.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>

namespace FlowMesh
{
FilApp::TriangleRenderable FlowMeshPresenter::createTriangleRenderable(
    const FlowMeshSphere& flowMeshSphere)
{
    // TODO Color
    constexpr uint32_t COLOR = 0xff00aaffu;

    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        buildSphereMesh(flowMeshSphere.getSphere());

    std::vector<FilApp::Vertex> vertices;
    for (const auto& vec: sphereMesh->getVertexPoints())
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(vec[0]),
                                           static_cast<float_t>(vec[1]),
                                           static_cast<float_t>(vec[2])},
                                          COLOR});
    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, uint16_t>(
                sphereMesh->getFacets())};
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
    m_mainView->addRenderable(createTriangleRenderable(flowMeshSphere));
}
void FlowMeshPresenter::add(const FlowMeshSegments& flowMeshSegments)
{
    m_mainView->addRenderable(createLineRenderables(flowMeshSegments));
}
} // namespace FlowMesh