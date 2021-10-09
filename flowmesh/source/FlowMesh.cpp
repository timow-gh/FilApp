#include <FilApp/Renderables/Vertex.hpp>
#include <FlowMesh/FlowMesh.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>

namespace FlowMesh
{

FilApp::TriangleRenderable
createTriangleRenderable(const FlowMeshSphere& flowMeshSphere)
{
    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        buildSphereMesh<double_t>(flowMeshSphere.getSphere());

    std::vector<FilApp::Vertex> vertices;
    uint32_t color = 0xff0000ffu;
    for (const auto& vec: sphereMesh->getVertexPoints())
        vertices.push_back(FilApp::Vertex{{static_cast<float_t>(vec[0]),
                                           static_cast<float_t>(vec[1]),
                                           static_cast<float_t>(vec[2])},
                                          color});
    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, uint16_t>(
                sphereMesh->getFacets())};
}

} // namespace FlowMesh
