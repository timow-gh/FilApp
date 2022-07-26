#include <Geometry/HalfedgeMesh/HalfedgeIndices.hpp>
#include <Geometry/HalfedgeMesh/HalfedgeMesh.hpp>
#include <Geometry/HalfedgeMeshBuilder/ConeMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CuboidMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/CylinderMeshBuilder.hpp>
#include <Geometry/HalfedgeMeshBuilder/SphereMeshBuilder.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/View.hpp>
#include <Meshler/GeometryElements/MCone.hpp>
#include <Meshler/GeometryElements/MCuboid.hpp>
#include <Meshler/GeometryElements/MCylinder.hpp>
#include <Meshler/GeometryElements/MGrid.hpp>
#include <Meshler/GeometryElements/MSegments.hpp>
#include <Meshler/GeometryElements/MSphere.hpp>
#include <Meshler/PresenterConfig.hpp>
#include <Meshler/PresenterUtils.hpp>
#include <Meshler/RenderableBuilder.hpp>

namespace Meshler
{
void RenderableBuilder::add(const MSphere& sphere)
{
    m_spheres.push_back(sphere);
}
void RenderableBuilder::add(const MCone& cone)
{
    m_cones.push_back(cone);
}
void RenderableBuilder::add(const MCylinder& cylinder)
{
    m_cylinders.push_back(cylinder);
}
void RenderableBuilder::add(const MSegments& segments)
{
    m_segments.push_back(segments);
}
void RenderableBuilder::add(const MCuboid& cuboid)
{
    m_cuboids.push_back(cuboid);
}
void RenderableBuilder::add(const MGrid& grid)
{
    m_grids.push_back(grid);
}
void RenderableBuilder::setPresenterConfig(const PresenterConfig& presenterConfig)
{
    m_presenterConfig = presenterConfig;
}
Core::TVector<Graphics::RenderableId> RenderableBuilder::build()
{
    for (const auto& geomElem: m_spheres)
        build(geomElem);
    for (const auto& geomElem: m_cones)
        build(geomElem);
    for (const auto& geomElem: m_cylinders)
        build(geomElem);
    for (const auto& geomElem: m_segments)
        build(geomElem);
    for (const auto& geomElem: m_cuboids)
        build(geomElem);
    for (const auto& geomElem: m_grids)
        build(geomElem);

    return m_renderableIds;
}
template <typename TRenderable>
void RenderableBuilder::addRenderable(TRenderable&& renderable)
{
    auto& view = m_view.get();
    auto triangleRenderableId = view.addRenderable(std::forward<TRenderable>(renderable));
    m_renderableIds.push_back(triangleRenderableId);
}
void RenderableBuilder::build(const MSphere& sphere)
{
    auto presenterConfig = m_presenterConfig.get();

    std::unique_ptr<Geometry::HalfedgeMesh<double_t>> sphereMesh =
        Geometry::SphereMeshBuilder<double_t>()
            .setPolarCount(presenterConfig.spherePolarCount)
            .setAzimuthCount(presenterConfig.sphereAzimuthCount)
            .setSphere(sphere.getGeometryElement())
            .build();

    addRenderable(Graphics::LineRenderable::create(segmentGraphicsVertices(*sphereMesh)));
    addRenderable(createTriangleRenderable(*sphereMesh));
}
void RenderableBuilder::build(const MCone& cone)
{
    auto presenterConfig = m_presenterConfig.get();

    auto coneMesh = Geometry::ConeMeshBuilder<double_t>()
                        .setCone((cone.getGeometryElement()))
                        .setAzimuthCount(presenterConfig.coneAzimuthCount)
                        .build();

    addRenderable(Graphics::LineRenderable::create(segmentGraphicsVertices(*coneMesh)));
    addRenderable(createTriangleRenderable(*coneMesh));
}
void RenderableBuilder::build(const MCylinder& cylinder)
{
    auto presenterConfig = m_presenterConfig.get();

    auto cylinderMesh = Geometry::CylinderMeshBuilder<double_t>()
                            .setCylinder(cylinder.getGeometryElement())
                            .setAzimuthCount(presenterConfig.cylinderAzimuthCount)
                            .build();

    addRenderable(Graphics::LineRenderable::create(segmentGraphicsVertices(*cylinderMesh)));
    addRenderable(createTriangleRenderable(*cylinderMesh));
}
void RenderableBuilder::build(const MSegments& segments)
{
    addRenderable(Graphics::LineRenderable::create(buildSegmentVertices(segments.getSegments())));
}
void RenderableBuilder::build(const MCuboid& cuboid)
{
    auto presenterConfig = m_presenterConfig.get();

    auto cuboidMesh =
        Geometry::CuboidMeshBuilder<double_t>().setCuboid(cuboid.getGeometryElement()).build();

    addRenderable(Graphics::LineRenderable::create(segmentGraphicsVertices(*cuboidMesh)));
    addRenderable(createTriangleRenderable(*cuboidMesh));
}
void RenderableBuilder::build(const MGrid& grid)
{
    addRenderable(Graphics::LineRenderable::create(buildSegmentVertices(grid.getSegments())));
}
Core::TVector<Graphics::Vertex>
RenderableBuilder::buildSegmentVertices(const Core::TVector<Geometry::Segment3d>& segments) const
{
    auto& presenterConfig = m_presenterConfig.get();
    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& segment: segments)
    {
        vertices.push_back(vecToVertex(segment.getSource(), presenterConfig.lineColor));
        vertices.push_back(vecToVertex(segment.getTarget(), presenterConfig.lineColor));
    }
    return vertices;
}
Core::TVector<Graphics::Vertex>
RenderableBuilder::segmentGraphicsVertices(const Geometry::HalfedgeMesh<double_t>& heMesh) const
{
    auto& presenterConfig = m_presenterConfig.get();

    const auto segIndices = Geometry::calcMeshSegmentIndices(heMesh);
    Core::TVector<Graphics::Vertex> result;
    result.reserve(segIndices.size());

    using VertexIndex_t = Geometry::HalfedgeMesh<double_t>::VertexIndex_t;
    for (const auto& segmentIndices: segIndices)
    {
        result.push_back(vecToVertex(
            heMesh.getVertex(VertexIndex_t(static_cast<std::size_t>(segmentIndices.source)))
                .getVector(),
            presenterConfig.lineColor));
        result.push_back(vecToVertex(
            heMesh.getVertex(VertexIndex_t(static_cast<std::size_t>(segmentIndices.target)))
                .getVector(),
            presenterConfig.lineColor));
    }
    return result;
}
Graphics::LineRenderable
RenderableBuilder::createLineRenderables(const Core::TVector<Geometry::Segment3d>& segments) const
{
    std::uint32_t lineColor = m_presenterConfig.get().lineColor;
    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& segment: segments)
    {
        vertices.push_back(vecToVertex(segment.getSource(), lineColor));
        vertices.push_back(vecToVertex(segment.getTarget(), lineColor));
    }

    return Graphics::LineRenderable::create(std::move(vertices));
}
Graphics::TriangleRenderable RenderableBuilder::createTriangleRenderable(
    const Geometry::HalfedgeMesh<double_t>& halfedgeMesh) const
{
    std::uint32_t faceColor = m_presenterConfig.get().faceColor;

    Core::TVector<Graphics::Vertex> vertices;
    for (const auto& vec: halfedgeMesh.meshPoints.getPoints())
        vertices.push_back(vecToVertex(vec, faceColor));

    return {std::move(vertices),
            Geometry::calcTriangleIndices<double_t, std::size_t, uint16_t>(halfedgeMesh.facets)};
}
} // namespace Meshler